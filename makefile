HEADER_FILES = $(shell find ./inc/* | grep .h)
SOURCE_FILES = $(shell find ./src/* | grep .cpp)

compile: 
	g++ -std=c++20 -g -I./inc/ main.cpp $(SOURCE_FILES) -lfmt -o server

format:
	clang-format -i main.cpp $(SOURCE_FILES) $(HEADER_FILES)

clean:
	rm server
