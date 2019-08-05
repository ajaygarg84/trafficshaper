all: build

FILES = src/common/main.c

build:
	gcc $(FILES) -o trafficshaper

