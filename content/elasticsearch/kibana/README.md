docker compose for elastic search and kibana 
https://www.elastic.co/blog/getting-started-with-the-elastic-stack-and-docker-compose 
# Steps 
- [x] Check it works 
- [x] Add kiana

kibana queries
```
GET /_cat/indices

GET jaeger-span-2023-11-20/_search
{
    "query": {
        "match_all": {}
    }
}
```


