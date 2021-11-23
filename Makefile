CC=g++
CF=-std=c++17 -Wall
BUILD_DIR=build
BASE_HPPS=utilities.hpp defs.hpp libs.hpp

all: $(BUILD_DIR) main.out mapper.out reducer.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: main.cpp $(BASE_HPPS)
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

main.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/utilities.o
	$(CC) $(BUILD_DIR)/utilities.o $(CF) -o main.out $(BUILD_DIR)/main.o

$(BUILD_DIR)/mapper.o: mapper.cpp mapper.hpp $(BASE_HPPS)
	$(CC) $(CF) -c mapper.cpp -o $(BUILD_DIR)/mapper.o

mapper.out: $(BUILD_DIR)/mapper.o $(BUILD_DIR)/utilities.o
	$(CC) $(BUILD_DIR)/utilities.o $(CF) -o mapper.out $(BUILD_DIR)/mapper.o

$(BUILD_DIR)/reducer.o: reducer.cpp reducer.hpp $(BASE_HPPS)
	$(CC) $(CF) -c reducer.cpp -o $(BUILD_DIR)/reducer.o

reducer.out: $(BUILD_DIR)/reducer.o $(BUILD_DIR)/utilities.o
	$(CC) $(BUILD_DIR)/utilities.o $(CF) -o reducer.out $(BUILD_DIR)/reducer.o

$(BUILD_DIR)/utilities.o: utilities.cpp utilities.hpp
	$(CC) $(CF) -c utilities.cpp -o $(BUILD_DIR)/utilities.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
