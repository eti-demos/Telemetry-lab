targets := $(wildcard *.yaml) 

.PHONY: build stop

all: run
run: build
	docker compose up --no-attach kibana --no-attach elasticsearch --no-attach service-1 --no-attach service-2  --no-attach jaeger-collector --no-attach jaeger-query

build: .build.docker
.build.docker: $(targets)
	docker compose build
	touch $@

stop: 
	docker compose down
