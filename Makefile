FILES = utils.cpp set_cover.cpp

main:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(FILES) -o main
	./main
	make clean

util:
	g++-8 -std=c++17 -lboost_iostreams utils.cpp -o util
	./util
	make clean

test:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(FILES) test.cpp -o test
	./test
	rm test

clean:
	rm main util
