PARSE = parsing_benchmarks.cpp

parse:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(PARSE) -o parsing_benchmarks
	./parsing_benchmarks

clean:
	rm parsing_benchmarks

.PHONY: parse

