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



