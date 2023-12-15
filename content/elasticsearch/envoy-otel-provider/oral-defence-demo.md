# example:
# Design a static mapping, A (Tracing data)
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

# Design a static mapping, b (api-traffic-log)
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

# Create Enrichment processor 
PUT _enrich/policy/policy-for-enrich-index-b
{
    "match": {
    "indices": "index-b",
    "match_field": "id",
    "enrich_fields": ["id", "prop-1","prop-2"]
  }
}

# Execution Enrichment processor to create enrich index
POST _enrich/policy/policy-for-enrich-index-b/_execute

GET .enrich-policy-for-enrich-index-b/_search

# Go through all the elements in the attributes. 
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

# Matching the documents, and enrich it
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

# Update index-a
POST index-a/_update_by_query?pipeline=for_each_ingest

GET /index-a/_search
{
  "query": {
    "match_all": {}
  }
}



# For API traffic

# Execution Enrichment processor to create enrich index
POST _enrich/policy/policy-for-enrich-api-traffic-log/_execute

GET .enrich-policy-for-enrich-api-traffic-log/_search


# Go through all the elements in the attributes. 
PUT _ingest/pipeline/for_each_ingest_api_traffic_log
{
  "processors": [
    {
      "foreach" : {
        "field" : "tags",
        "processor" : {
          "pipeline" : {
            "name" : "for_each_ingest_inner_api_traffic_log"
          }
        }
      }
    }
  ]
}

# Matching the documents, and enrich it
PUT _ingest/pipeline/for_each_ingest_inner_api_traffic_log
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
        "policy_name": "policy-for-enrich-api-traffic-log",
        "field": "current.value",
        "target_field": "current.from_api-traffic-log",
        "if": "ctx.current.key == 'API Log ID'"
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
POST jaeger-span-2023-12-13/_update_by_query?pipeline=for_each_ingest_api_traffic_log

GET jaeger-span-2023-12-13/_search
{
  "query": {
    "match_all": {}
  }
}








