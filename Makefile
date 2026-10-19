.PHONY: all build run test clean reconfigure

BUILD_DIR := build
BUILD_TYPE := Release
TARGET := shoot-the-aliens
FLAGS := -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Wnull-dereference -Wold-style-cast -Woverloaded-virtual

all: build

build:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) DCMAKE_CXX_FLAGS="$(FLAGS)"
	cmake --build $(BUILD_DIR) --config $(BUILD_TYPE)

run: build
	cmake --build $(BUILD_DIR) --config $(BUILD_TYPE) --target $(TARGET)
	./$(BUILD_DIR)/$(TARGET)

test:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	cmake --build $(BUILD_DIR) --config $(BUILD_TYPE) --target run_tests
	ctest --test-dir $(BUILD_DIR) --output-on-failure -C $(BUILD_TYPE)

clean:
	rm -rf $(BUILD_DIR)

reconfigure:
	rm -rf $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
