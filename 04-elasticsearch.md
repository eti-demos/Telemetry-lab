The section is show how to configurate the jaeger-elastic search



API traffic log enrichment

Attention: 
1. insecure elastic configuration 

2. Config is here: is found here [TODO] 

Note: jaeger hasn't support elastic search 8 yet now (2023, Dec)
[issue](https://github.com/jaegertracing/jaeger/issues/3571) therefore, I'm
using the latest version of elastic7. 


Remark, 
Once the a doc is created, the type of value of a key is important. 
Eg: if there is a doc like this 
```json
{
    "id": 12313
}
```

"id" has to be long type.

If I want to submit
```json
{
    "id": "my-id-nub"
}
```
it occur be some parsing error.


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
It works the following command 
```console 
curl -XPOST -H "Content-Type: application/json" localhost:9200/api-traffic-log/_doc -d '
{
    "apilogid": 123,
    "depth": 5
}'
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


Backup of ES command:
```
GET /_cat/indices

DELETE api-traffic-log
PUT api-traffic-log
GET api-traffic-log/_mapping

GET api-traffic-log/_search
{
    "query": {
        "match_all": {}
    }
}
GET jaeger-span-2023-11-30/_mapping

GET jaeger-span-2023-11-30/_search
{
  "query": {
    "match_all": {}
  }
}



PUT _enrich/policy/pl-api-traffic-log
{
  "match": {
    "indices": "api-traffic-log",
    "match_field": "apilogid",
    "enrich_fields": ["depth"]
  }
}



POST _enrich/policy/pl-api-traffic-log/_execute

GET _cat/aliases

GET .enrich-pl-api-traffic-log-1701360439699/_search
{
  "query": {
    "match_all": {}
  }
}

PUT _ingest/pipeline/pipeline_api_traffic_log_integration
{
  "processors": [
    {
      "enrich": {
        "policy_name": "pl-api-traffic-log",
        "field": "pub_id",
        "target_field": "publisher_info",
        "on_failure": [
          {
            "set": {
              "field": "error.msg",
              "value": "{{ _ingest.on_failure_message }}"
            }
          },
          {
            "set": {
              "field": "error.code",
              "value": 100
            }
          }
        ]
      }
    }
  ]
}


PUT _ingest/pipeline/blog_book_publisher
{
  "processors": [
    {
      "enrich": {
        "policy_name": "blog_book_publisher",
        "field": "pub_id",
        "target_field": "publisher_info",
        "on_failure": [
          {
            "set": {
              "field": "error.msg",
              "value": "{{ _ingest.on_failure_message }}"
            }
          },
          {
            "set": {
              "field": "error.code",
              "value": 100
            }
          }
        ]
      }
    }
  ]
}

GET blog_enrich_books/_search
{
  "query": {
    "match_all": {}
  }
}

POST blog_enrich_books/_update_by_query?pipeline=blog_book_publisher
```



GET /_cat/indices
GET /jaeger-span-2023-12-01/_search
{
  "query": {
    "match_all": {}
  }
}

# a index  <- b source

# Design a static mapping, A and B

# Create some documents 

# create a enrichment processor 

# Pipeline

# Verifie



# example:

DELETE /index-a

PUT /index-a
{
 "mappings": {
    "dynamic": "true", 
   "properties": {
     "attribute": {
       "type": "nested",
       "properties": {
         "key": {
           "type": "keyword"
         },
         "type": {
           "type": "keyword"
         },
         "value": {
           "type": "keyword"
         }
       }
     }
   }
 }
}

PUT index-a/_doc/1
{
  "attribute": [
    {
      "key": "id",
      "type": "string",
      "value": "10"

    },
    {
      "key": "prop",
      "type": "string",
      "value": "10+10"
    }
  ]
}

PUT index-a/_doc/2
{
  "attribute": [
    {
      "key": "id",
      "type": "string",
      "value": "20"

    },
    {
      "key": "prop",
      "type": "string",
      "value": "20+20"
    }
  ]
}
PUT index-a/_doc/3
{
  "attribute": [
    {
      "key": "id",
      "type": "string",
      "value": "30"

    },
    {
      "key": "prop",
      "type": "string",
      "value": "30+30"
    }
  ]
}

GET /index-a/_search
{
  "query": {
    "match_all": {}
  }
}


DELETE /index-b
PUT /index-b
{
 "mappings": {
    "dynamic": "true", 
    "properties": {
      "id":{
        "type": "keyword"
      },
      "prop-1": {
        "type": "keyword"
      },
      "prop-2":{
        "type": "keyword"
      }
   }
 }
}

PUT index-b/_doc/1
{
  "id": "20",
  "prop-1": "21+21",
  "prop-2": "22+22"
}

PUT index-b/_doc/2
{
  "id": "10",
  "prop-1": "11+11",
  "prop-2": "12+12"
}

PUT index-b/_doc/3
{
  "id": "40",
  "prop-1": "41+41",
  "prop-2": "42+42"
}

PUT index-b/_doc/4
{
  "id": "30",
  "prop-1": "31+31",
  "prop-2": "32+32"
}

GET /index-b/_search
{
  "query": {
    "match_all": {}
  }
}

PUT _enrich/policy/policy-for-enrich-index-b
{
    "match": {
    "indices": "index-b",
    "match_field": "id",
    "enrich_fields": ["id", "prop-1","prop-2"]
  }
}

POST _enrich/policy/policy-for-enrich-index-b/_execute

GET .enrich-policy-for-enrich-index-b/_search


PUT _ingest/pipeline/test_foreach
{
  "processors": [
    {
      "foreach": {
        "field": "attribute",
        "processor": {
          "enrich": {
            "policy_name": "policy-for-enrich-index-b",
            "field": "_ingest._value.value",
            "target_field": "_ingest._value.from_index-b",
            "if": "{{_injest._value.key}} == 'id'"
          }
        } 
      }
    }
  ]
}


PUT _ingest/pipeline/test_foreach_ctx
{
  "processors": [
    {
      "foreach": {
        "field": "attribute",
        "processor": {
          "script": {
            "source": "ctx._source"
          }
        }
      }
    }
  ]
}


POST /_ingest/pipeline/test_foreach/_simulate?verbose
{
  "docs": [
    {
      "_index": "index",
      "_id": "id",
      "_source": {
        "attribute": [
          {
            "key": "id",
            "type": "string",
            "value": "10"
          },
          {
            "key": "prop",
            "type": "string",
            "value": "10+10"
          }
        ]
      }
    }
  ]
}


PUT _ingest/pipeline/for_each_ingest_inner
{
  "processors": [
    {
      "set": {
        "description": "Work around lack of access to _ingest from conditionals and scripts",
        "field": "current",
        "copy_from": "_ingest._value"
      }
    },
    {
      "enrich": {
        "policy_name": "policy-for-enrich-index-b",
        "field": "current.value",
        "target_field": "current.from_index-b",
        "if": "ctx.current.key == 'id'"
      }
    },
    {
      "set": {
        "description": "Work around lack of access to _ingest from conditionals and scripts",
        "field": "_ingest._value",
        "copy_from": "current"
      }
    },
    {
      "remove": {
        "description": "Work around lack of access to _ingest from conditionals and scripts",
        "field": "current"
      }
    }
  ]
}

PUT _ingest/pipeline/for_each_ingest
{
  "processors": [
    {
      "foreach" : {
        "field" : "attribute",
        "processor" : {
          "pipeline" : {
            "name" : "for_each_ingest_inner"
          }
        }
      }
    }
  ]
}

POST /_ingest/pipeline/for_each_ingest/_simulate?verbose
{
  "docs": [
    {
      "_index": "index",
      "_id": "id",
      "_source": {
        "attribute": [
          {
            "key": "id",
            "type": "string",
            "value": "10"
          },
          {
            "key": "prop",
            "type": "string",
            "value": "10+10"
          }
        ]
      }
    },
    {
      "_index": "2",
      "_id": "id",
      "_source": {
        "attribute": [
          {
            "key": "id",
            "type": "string",
            "value": "20"
          },
          {
            "key": "prop",
            "type": "string",
            "value": "20+20"
          }
        ]
      }
    }
  ]
}




