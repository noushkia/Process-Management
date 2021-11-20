CC=g++
STD=-std=c++11
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) main.out mapper.out reducer.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: main.cpp
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

main.out: $(BUILD_DIR)/main.o
	$(CC) $(CF) -o main.out $(BUILD_DIR)/main.o

$(BUILD_DIR)/mapper.o: mapper.cpp mapper.hpp
	$(CC) $(CF) -c mapper.cpp -o $(BUILD_DIR)/mapper.o

mapper.out: $(BUILD_DIR)/mapper.o
	$(CC) $(CF) -o mapper.out $(BUILD_DIR)/mapper.o

$(BUILD_DIR)/reducer.o: reducer.cpp reducer.hpp
	$(CC) $(CF) -c reducer.cpp -o $(BUILD_DIR)/reducer.o

reducer.out: $(BUILD_DIR)/reducer.o
	$(CC) $(CF) -o reducer.out $(BUILD_DIR)/reducer.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
