DFG = utils.cpp DFG.cpp DFG_main.cpp
DFG_TEST = utils.cpp DFG.cpp DFG_test.cpp
GREEDY = utils.cpp greedy.cpp greedy_main.cpp
GREEDY_TEST = utils.cpp greedy.cpp greedy_test.cpp
FILES = utils.cpp greedy.cpp greedy_main.cpp

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

# util:
# 	g++-8 -std=c++17 -lboost_iostreams utils.cpp -o util
# 	./util
# 	make clean

clean:
	rm dfg dfg_test greedy greedy_test

.PHONY: DFG DFG_test greedy greedy_test
