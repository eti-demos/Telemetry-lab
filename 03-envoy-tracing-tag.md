# Tracing in envoy 

[Official
doc](https://www.envoyproxy.io/docs/envoy/latest/intro/arch_overview/observability/tracing#arch-overview-tracing)

For response_header, maybe using the outbound traffic is that possible? 

HTTP connection manager tracing provider? 

# customising tracing tags 
- request_header
- matadata (for the filter's configuration)
- environment variable while start running envoy
- literal

[Customising tag](https://www.envoyproxy.io/docs/envoy/latest/api-v3/type/tracing/v3/custom_tag.proto)


wasm filter can only interact with the connection flow, according to the wasm
ABI spec.


The wasm filter do is modify the modify the value of `Number` and add
`header_size` header. 
- Number less than or equal 10 `Header-Size: small`
- Number bigger then 10, `Header-Size: big`


```
curl -H "Number: 10" 127.0.0.1:10000
curl -H "Number: 11" 127.0.0.1:10000
```

What happend if app send tracing data as well? 

[envoy ref](https://www.envoyproxy.io/docs/envoy/v1.28.0/api-v3/type/tracing/v3/custom_tag.proto) 
[Istio customize
ref](https://istio.io/latest/docs/tasks/observability/distributed-tracing/mesh-and-proxy-config/#customizing-tracing-tags)

example of envo config https://gist.github.com/poolski/9318b70285379d884422b2419c0325c9

Describe custom tags for active span.

```json
{
  "tag": "<tag name>",
  "literal": {...},
  "environment": {...},
  "request_header": {...},
  "metadata": {...} # it seems that it's to configure envoy filter 
}
```

- literal: custom tag with static value for the tag value
- environment: environment variable name to obtain the value to populate the
tag value
- request_header: it works
- metadata: Metadata type custom tag using `MetadataKey` to retrieve the protobuf
value from Metadata, and populate the tag value with the canonical JSON
representation of it. 
How to configure? 

```cosole
curl -H "customtag: hello john" localhost:10000
```

WASM filter is able to modify the input header and the tracer can successfully
export the tracing value to jaeger

eg: 
- Number header is removed -> NaN
- Number-size is added -> big/small


