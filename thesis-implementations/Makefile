# DFG_TEST = utils.cpp DFG.cpp DFG_test.cpp
# DFG = utils.cpp DFG.cpp DFG_main.cpp
G = gp_utils.cpp sc_utils.cpp greedy.cpp greedy_main.cpp
GT = gp_utils.cpp sc_utils.cpp greedy.cpp greedy_test.cpp
# RFGREEDY = utils.cpp rfgreedy.cpp rfgreedy_main.cpp
# RFGREEDY_TEST = utils.cpp rfgreedy.cpp rfgreedy_test.cpp
# SSSC = gp_utils.cpp sc_utils.cpp ec_utils.cpp sssc.cpp sssc_main.cpp
# SSSC_TEST = gp_utils.cpp sc_utils.cpp ec_utils.cpp sssc.cpp sssc_test.cpp
# ITER_SET_COVER = gp_utils.cpp ec_utils.cpp iter_set_cover.cpp
PG = gp_utils.cpp ssc_utils.cpp pgreedy.cpp pgreedy_main.cpp
PGT = gp_utils.cpp ssc_utils.cpp pgreedy.cpp pgreedy_test.cpp
# SSC_UTILS_TEST = gp_utils.cpp ssc_utils.cpp ssc_utils_test.cpp

FLAGS=-std=c++17 -g -pthread -lboost_iostreams
ifeq ($(shell uname -s),Darwin)
	CC=g++-8
else
	CC=g++
	EXTRA=-I/panfs/panasas01/cosc/an15739/boost_1_69_0 -L/panfs/panasas01/cosc/an15739/boost_1_69_0
endif

pg:
	$(CC) $(EXTRA) $(FLAGS)  $(PG) -o pg
	./pg

pgt:
	$(CC) $(EXTRA) $(FLAGS)  $(PGT) -o pgt
	./pgt

dfg:
	$(CC) $(EXTRA) $(FLAGS)  $(DFG) -o dfg
	./dfg

dfgt:
	$(CC) $(EXTRA) $(FLAGS)  $(DFG_TEST) -o dfg_test
	./dfg_test

g:
	$(CC) $(EXTRA) $(FLAGS)  $(G) -o g
	./g

gt:
	$(CC) $(EXTRA) $(FLAGS)  $(GT) -o gt
	./gt

# rfgreedy:
# 	$(CC) $(EXTRA) $(FLAGS)  $(RFGREEDY) -o rfgreedy
# 	./rfgreedy


# ssc_utils_test:
# 	$(CC) $(EXTRA) $(FLAGS)  $(SSC_UTILS_TEST) -o ssc_utils_test
# 	./ssc_utils_test

# rfgreedy_test:
# 	$(CC) $(EXTRA) $(FLAGS)  $(RFGREEDY_TEST) -o rfgreedy_test
# 	./rfgreedy_test

# sssc:
# 	$(CC) $(EXTRA) $(FLAGS)  $(SSSC) -o sssc
# 	./sssc

# sssc_test:
# 	$(CC) $(EXTRA) $(FLAGS)  $(SSSC_TEST) -o sssc_test
# 	./sssc_test

# iter_set_cover:
# 	$(CC) $(EXTRA) $(FLAGS)  $(ITER_SET_COVER) -o iter_set_cover
# 	./iter_set_cover

clean:
	rm dfg dfg_test greedy greedy_test rfgreedy rfgreedy_test iter_set_cover

.PHONY: pg pgt dfg dfgt g gt








