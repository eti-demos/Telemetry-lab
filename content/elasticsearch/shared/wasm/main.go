// Copyright 2020-2021 Tetrate
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package main

import (
    "strconv"
    "fmt"
	"github.com/tetratelabs/proxy-wasm-go-sdk/proxywasm"
	"github.com/tetratelabs/proxy-wasm-go-sdk/proxywasm/types"
    "github.com/google/uuid"
)


const tickMilliseconds uint32 = 1000

func main() {
	proxywasm.SetVMContext(&vmContext{})
}

type vmContext struct {
	// Embed the default VM context here,
	// so that we don't need to reimplement all the methods.
	types.DefaultVMContext
}

// Override types.DefaultVMContext.
func (*vmContext) NewPluginContext(contextID uint32) types.PluginContext {
	proxywasm.LogWarnf("New plugin Contxt is created")
	return &pluginContext{}
}

type pluginContext struct {
	// Embed the default plugin context here,
	// so that we don't need to reimplement all the methods.
	types.DefaultPluginContext
}


func (*pluginContext) NewHttpContext(uint32) types.HttpContext { 
    _apiLogId := uuid.New()
	// proxywasm.LogWarnf("New HTTP Contxt is created")
    return &httpContext{
        Telemetry: Telemetry{
			apiLogId: _apiLogId,
        },
    } 
}

type httpContext struct{
    types.DefaultHttpContext
    Telemetry
}

type Telemetry struct {
    apiLogId uuid.UUID      `json:"apilogid, omitempty"`
    Depth       int         `json:"depth, omitempty"`
    RequestID   string      `json:"requestID,omitempty"`
}

func (ctx *httpContext) OnHttpRequestHeaders(numHeaders int, endOfStream bool) types.Action {
    // spanID, err :=proxywasm.GetHttpRequestHeader("Number")
    // traceID, err :=proxywasm.GetHttpRequestHeader("Number")

    err:= proxywasm.RemoveHttpRequestHeader("Api-Log-Id")
    if err!=nil {
		proxywasm.LogCriticalf("failed to remove Api-Log-Id headers: %v", err)
    }
    proxywasm.AddHttpRequestHeader("Api-Log-Id", ctx.apiLogId.String()) 


    depth, err:= proxywasm.GetHttpRequestHeader("Depth")

    if err!=nil {
		proxywasm.LogCriticalf("failed to get Depth headers: %v", err)
        proxywasm.AddHttpRequestHeader("Depth", "0") 
        
    }else {
        depth, err := strconv.Atoi(depth)
        if err!= nil{
            proxywasm.LogCriticalf("Depth headers isn't a number")
        }
        depth++
        proxywasm.ReplaceHttpRequestHeader("Depth", strconv.Itoa(depth))
        ctx.Telemetry.Depth = depth
    }

    if ctx.Telemetry.RequestID == "" {
        xRequestID, err := proxywasm.GetHttpRequestHeader("x-request-id")
		if err != nil {
			proxywasm.LogWarnf("Failed to get x-request-id header: %v", err)
		}
		ctx.Telemetry.RequestID = xRequestID
	}

    // ReplaceHttpRequestHeader
    // GetHttpRequestHeader

    hs, err := proxywasm.GetHttpRequestHeaders()
    if err != nil {
		proxywasm.LogCriticalf("failed to get request headers: %v", err)
	}
    for _, h := range hs {
		proxywasm.LogInfof("request header --> %s: %s", h[0], h[1])
	}

    return types.ActionContinue
}


const jsonPayload string = `{"requestID":"%v","depth":"%v", "apilogid": "%v"}`
// var emptyTrailers = [][2]string{}

func (ctx *httpContext) OnHttpStreamDone() {

	proxywasm.LogInfof("Telemetry dispatched")
    body := fmt.Sprintf(jsonPayload,
		ctx.RequestID, ctx.Depth, ctx.apiLogId)

    asHeader := [][2]string{{":method", "POST"}, {":authority", "elasticsearch:9200"},
        {":path", "/api-traffic-log/_doc"}, {"accept", "*/*"}, {"Content-Type",
            "application/json"}}

    _, err := proxywasm.DispatchHttpCall("elasticsearch", asHeader, []byte(body),
        nil, httpCallTimeoutMs, httpCallResponseCallback); 

    if err != nil {
        proxywasm.LogErrorf("Dispatch httpcall failed. %v", err) 
        // return err 
    }

	// // if err := sendAuthPayload(&ctx.Telemetry, ctx.serverAddress); err != nil {
	// if err := sendAuthPayload(&ctx.Telemetry, "elasticsearch"); err != nil {
	// 	proxywasm.LogErrorf("Failed to send payload. %v", err)
	// }

}




const (
	httpCallTimeoutMs = 15000
	// MaxBodySize       = 1000 * 1000
)
const (
	statusCodePseudoHeaderName        = ":status"
	// contentTypeHeaderName             = "content-type"
	// defaultServiceMesh                = "istio"
)



// func sendAuthPayload(payload *Telemetry, clusterName string) error {
//
//     body := fmt.Sprintf(jsonPayload,
// 		payload.RequestID, payload.Depth, payload.apiLogId)
//
//
    // asHeader := [][2]string{{":method", "POST"}, {":authority", "elasticsearch:9200"},
    //     {":path", "/api-traffic-log/_doc"}, {"accept", "*/*"}, {"Content-Type",
    //         "application/json"}, {"x-request-id", payload.RequestID}}
//
//     _, err := proxywasm.DispatchHttpCall(clusterName, asHeader, []byte(body),
//         emptyTrailers, httpCallTimeoutMs, httpCallResponseCallback); 
//
//     if err != nil {
//         proxywasm.LogErrorf("Dispatch httpcall failed. %v", err) 
//         return err 
//     }
//
// 	proxywasm.LogInfof("Telemetry dispatched")
// 	return nil
// }

func httpCallResponseCallback(numHeaders, bodySize, numTrailers int) {
    proxywasm.LogWarnf("Callback")

	proxywasm.LogDebugf("httpCallResponseCallback. numHeaders: %v, bodySize: %v, numTrailers: %v", numHeaders, bodySize, numTrailers)
	headers, err := proxywasm.GetHttpCallResponseHeaders()
	if err != nil {
		proxywasm.LogWarnf("Failed to get http call response headers. %v", err)
		return
	}

    for _, h := range headers {
		proxywasm.LogInfof("request header --> %s: %s", h[0], h[1])
	}

	// for _, header := range headers {
	// 	if header[0] == statusCodePseudoHeaderName {
	// 		proxywasm.LogDebugf("Got response status from trace server: %v", header[1])
	// 	}
	// }
}

