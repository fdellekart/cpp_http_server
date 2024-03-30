HEADER_FILES = $(shell ls -rt ./inc/* | grep .h)
SOURCE_FILES = $(shell ls -rt ./src/* | grep .cpp)

compile: 
	g++ -std=c++20 -g -I./inc/ main.cpp $(SOURCE_FILES) -lfmt -o server

format:
	clang-format -i main.cpp $(SOURCE_FILES) $(HEADER_FILES)

clean:
	rm server
