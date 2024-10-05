.PHONY: build test all

all: build test

build:
	.\dev\build.bat

build_release:
	.\dev\build_release.bat

test:
	.\dev\test.bat

format:
	clang-format -i src/*.cpp
	clang-format -i tests/*.cpp
