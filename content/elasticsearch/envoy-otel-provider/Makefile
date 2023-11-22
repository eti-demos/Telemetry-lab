targets := $(wildcard *.yaml) 

.PHONY: build

all: run
run: build
	docker compose up

build: .build.docker
.build.docker: $(targets)
	docker compose build
	touch $@
