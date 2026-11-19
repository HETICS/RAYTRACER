# Shortcuts for the build, like "npm run" scripts. Run inside the dev container.

.PHONY: build run test clean

build:
	cmake -B build -G Ninja
	cmake --build build

run: build
	./build/raytracer

test: build
	ctest --test-dir build --output-on-failure

clean:
	rm -rf build
