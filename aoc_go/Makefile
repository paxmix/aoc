.PHONY: build install test clean

build:
	go build -o bin/run ./cmd/run

install:
	go build -o bin/install ./cmd/install

test:
	go test ./internal/solutions/year_2023

clean:
	rm -rf bin/
