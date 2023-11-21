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


