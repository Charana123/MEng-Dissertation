DFG = utils.cpp DFG.cpp DFG_main.cpp
DFG_TEST = utils.cpp DFG.cpp DFG_test.cpp
GREEDY = utils.cpp greedy.cpp greedy_main.cpp
GREEDY_TEST = utils.cpp greedy.cpp greedy_test.cpp
RFGREEDY = utils.cpp rfgreedy.cpp rfgreedy_main.cpp
RFGREEDY_TEST = utils.cpp rfgreedy.cpp rfgreedy_test.cpp
SSSC = gp_utils.cpp sc_utils.cpp ec_utils.cpp sssc.cpp sssc_main.cpp
SSSC_TEST = gp_utils.cpp sc_utils.cpp ec_utils.cpp sssc.cpp sssc_test.cpp

dfg:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(DFG) -o dfg
	./dfg

dfg_test:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(DFG_TEST) -o dfg_test
	./dfg_test

greedy:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(GREEDY) -o greedy
	./greedy

greedy_test:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(GREEDY_TEST) -o greedy_test
	./greedy_test

rfgreedy:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(RFGREEDY) -o rfgreedy
	./rfgreedy

rfgreedy_test:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(RFGREEDY_TEST) -o rfgreedy_test
	./rfgreedy_test

sssc:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(SSSC) -o sssc
	./sssc

sssc_test:
	g++-8 -std=c++17 -pthread -lboost_iostreams $(SSSC_TEST) -o sssc_test
	./sssc_test

clean:
	rm dfg dfg_test greedy greedy_test rfgreedy rfgreedy_test

.PHONY: dfg dfg_test greedy greedy_test rfgreedy rfgreedy_test sssc sssc_test

