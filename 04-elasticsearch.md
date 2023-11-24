The section is show how to configurate the jaeger-elastic search



API traffic log enrichment

Attention: 
1. insecure elastic configuration 

2. Config is here: is found here [TODO] 

Note: jaeger hasn't support elastic search 8 yet now (2023, Dec)
[issue](https://github.com/jaegertracing/jaeger/issues/3571) therefore, I'm
using the latest version of elastic7. 


## kibana queries
```
GET /_cat/indices

GET jaeger-span-2023-11-20/_search
{
    "query": {
        "match_all": {}
    }
}
```

# OpenTel setup 
Front-proxy
```
:authority: localhost:10000
:path: /trace/1
:method: GET
:scheme: http
user-agent: curl/8.1.2
accept: */*
x-forwarded-proto: http
x-request-id: ab63688c-3598-92fc-8510-69bd1a6f3e6d
x-envoy-decorator-operation: routeToEnvoy1
```

envoy-1
```
:authority: localhost:10000
:path: /trace/1
:method: GET
:scheme: http
user-agent: curl/8.1.2
accept: */*
x-forwarded-proto: http
x-request-id: ab63688c-3598-92fc-8510-69bd1a6f3e6d
traceparent: 00-50dc229dd2033eb7c109ae735b429a02-0858b99f636a63c0-01
tracestate:
```

From the
[doc](https://www.w3.org/TR/trace-context/#trace-context-http-headers-format)
traceparent: 00-50dc229dd2033eb7c109ae735b429a02-0858b99f636a63c0-01
traceparent: `version-format`-`trace-id`-`parent-id`-`trace-flags`
-> know the parent traceID and SpanID is possible to know my own traceID and
spanID? 

front-proxy
```json 
"traceID" : "50dc229dd2033eb7c109ae735b429a02",
"spanID" : "0858b99f636a63c0",
"operationName" : "egress localhost:10000",
"references" : [ ],
```

envoy-1
```json
"traceID" : "50dc229dd2033eb7c109ae735b429a02",
"spanID" : "45c06eae351f4fd8",
"operationName" : "ingress",
"references" : [
    {
        "refType" : "CHILD_OF",
        "traceID" : "50dc229dd2033eb7c109ae735b429a02",
        "spanID" : "0858b99f636a63c0"
    }
],
```


