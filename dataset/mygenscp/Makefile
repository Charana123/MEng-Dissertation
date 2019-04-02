CC=clang++
FLAGS=-std=c++17 -O3

gen1:
	$(CC) $(FLAGS) gen_dataset.cpp -o gend.out
	./gend.out

gen2:
	$(CC) $(FLAGS) gen_dataset1.cpp -o gend1.out
	./gend1.out

clean:
	rm parsing_benchmarks

.PHONY: parse

