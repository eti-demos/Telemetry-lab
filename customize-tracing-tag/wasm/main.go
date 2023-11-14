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
	proxywasm.LogWarn("New Plugin!")

	return &pluginContext{
        contextID: contextID,
    }
}

type pluginContext struct {
	// Embed the default plugin context here,
	// so that we don't need to reimplement all the methods.
	types.DefaultPluginContext
	contextID uint32
}

// Override types.DefaultPluginContext.
// func (ctx *pluginContext) OnPluginStart(pluginConfigurationSize int) types.OnPluginStartStatus {
	// rand.Seed(time.Now().UnixNano())
	// proxywasm.LogWarn("OnPluginStart from Go!")
	// if err := proxywasm.SetTickPeriodMilliSeconds(tickMilliseconds); err != nil {
	// 	proxywasm.LogCriticalf("failed to set tick period: %v", err)
	// }

	// return types.OnPluginStartStatusOK
// }
// Override types.DefaultPluginContext.
// func (ctx *pluginContext) OnTick() {
// 	t := time.Now().UnixNano()
// 	proxywasm.LogWarnf("It's %d: random value: %d", t, rand.Uint64())
// 	proxywasm.LogWarnf("OnTick called")
// }

func (*pluginContext) NewHttpContext(contextID uint32) types.HttpContext { 
	proxywasm.LogWarnf("Creat new Http Context")
    return &httpContext{
        contextID: contextID,
    } 
}


type httpContext struct {
	// Embed the default http context here,
	// so that we don't need to reimplement all the methods.
	types.DefaultHttpContext
	contextID   uint32
}

// func (ctx *httpContext) OnHttpRequestHeaders(numHeaders int, endOfStream bool) types.Action {
//     number_str, _ := proxywasm.GetHttpRequestHeader("Nubmer")
// 	proxywasm.LogWarnf("Number header is", number_str)
//
// 	return types.ActionContinue
//
//
// }
