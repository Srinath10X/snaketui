CXX = c++
CXXFLAGS = -Wall -Werror -I include

SRC_FILES = src/main.cpp \
						src/handlers/terminal_handler.cpp 

BIN_FILE_NAME = snaketui
BUILD_DIR = build

all: build

build: $(SRC_FILES)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(BIN_FILE_NAME)

run: $(BUILD_DIR)/$(BIN_FILE_NAME)
	./$(BUILD_DIR)/$(BIN_FILE_NAME)

$(BUILD_DIR)/$(BIN_FILE_NAME): $(SRC_FILES)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(BIN_FILE_NAME)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean build run
