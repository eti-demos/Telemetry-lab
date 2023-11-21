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

What happend if app send tracing data as well? 

```
curl -H "Number: 10" 127.0.0.1:10000
curl -H "Number: 11" 127.0.0.1:10000
```


