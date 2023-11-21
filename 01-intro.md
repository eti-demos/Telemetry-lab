# This lab contain 3 major sections
- Understanding jaeger distributed tracing solution especial understanding the
`jaeger-query` gRPC endpoint. 
- Envoy implements its ability of tracing in the `HTTP_Connection_manager`
filter. It not only allows us to choose so called `tracing provider` but also to
customize a little bit the tracing data. In this section, we provide a simple
configration of the tracing solution provided by envoy and we discusse about
what WebAssembly filter can do about the tracing data. 
- Saving tracing data in the elastic search. Enrichment processor to correlate
the API traffic logs (Exported by envoy wasm filter) and tracing data (exported
by envoy tracing provider). 


https://opentelemetry.io/docs/specs/otel/logs/
