targets := $(wildcard *.yaml) 

.PHONY: build

all: run
run: build
	docker compose up --no-attach kibana

build: .build.docker
.build.docker: $(targets)
	docker compose build
	touch $@
