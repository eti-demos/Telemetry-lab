targets := $(wildcard *.yaml) 

.PHONY: build

all: run
run: build
	docker compose up --no-attach kibana --no-attach elasticsearch

build: .build.docker
.build.docker: $(targets)
	docker compose build
	touch $@
