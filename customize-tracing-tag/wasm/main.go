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

	"github.com/tetratelabs/proxy-wasm-go-sdk/proxywasm"
	"github.com/tetratelabs/proxy-wasm-go-sdk/proxywasm/types"
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
	proxywasm.LogWarnf("New HTTP Contxt is created")
    return &httpContext{} 
}

type httpContext struct{
    types.DefaultHttpContext
}

func (h *httpContext) OnHttpRequestHeaders(numHeaders int, endOfStream bool) types.Action {
    number_str, err :=proxywasm.GetHttpRequestHeader("Number")
    if err != nil {
        proxywasm.LogWarnf("Error while retriving the value of hearder Number")
    }
    proxywasm.LogWarnf("The Number header value is %s", number_str)

    return types.ActionContinue

}

