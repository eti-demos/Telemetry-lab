[ref](https://www.envoyproxy.io/docs/envoy/v1.28.0/api-v3/type/tracing/v3/custom_tag.proto) 

Describe custom tags for active span.

```json
{
  "tag": "<tag name>",
  "literal": {...},
  "environment": {...},
  "request_header": {...},
  "metadata": {...}
}
```

- literal: custom tag with static value for the tag value
- environment: environment variable name to obtain the value to populate the
tag value
- request_header: it works
- metadata: Metadata type custom tag using `MetadataKey` to retrieve the protobuf
value from Metadata, and populate the tag value with the canonical JSON
representation of it. 

```cosole
curl -H "customtag: hello john" localhost:10000
```

