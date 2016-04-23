all: dfa.cpp
	g++ -O3 -Wall -Wextra -std=c++1y -g -o dfa dfa.cpp

clean: 
	rm dfa
