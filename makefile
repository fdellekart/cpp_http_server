SOURCE_FILES = $(shell ls -rt ./src/* | grep cpp)

compile: 
	g++ -std=c++20 -g -I./inc/ main.cpp $(SOURCE_FILES)  -o server

clean:
	rm server
