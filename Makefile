DFG_FILES = gp_utils.cpp sc_utils.cpp DFG.cpp DFG_main.cpp
DFGT_FILES = gp_utils.cpp sc_utils.cpp DFG.cpp DFG_test.cpp
G_FILES = gp_utils.cpp sc_utils.cpp greedy.cpp greedy_main.cpp
GT_FILES = gp_utils.cpp sc_utils.cpp greedy.cpp greedy_test.cpp
# RFGREEDY = utils.cpp rfgreedy.cpp rfgreedy_main.cpp
# RFGREEDY_TEST = utils.cpp rfgreedy.cpp rfgreedy_test.cpp
SSSC_FILES = gp_utils.cpp ssc_utils.cpp sssc.cpp sssc_main.cpp
SSSCT_FILES = gp_utils.cpp ssc_utils.cpp sssc.cpp sssc_test.cpp
# ITER_SET_COVER = gp_utils.cpp ec_utils.cpp iter_set_cover.cpp
PG_FILES = gp_utils.cpp ssc_utils.cpp pgreedy.cpp pgreedy_main.cpp
PGT_FILES = gp_utils.cpp ssc_utils.cpp pgreedy.cpp pgreedy_test.cpp
# SSC_UTILS_TEST = gp_utils.cpp ssc_utils.cpp ssc_utils_test.cpp
ASSADIMP_FILES = gp_utils.cpp sc_utils.cpp DFG.cpp ssc_utils.cpp assadiMP.cpp assadiMP_main.cpp
ASSADIMPT_FILES = gp_utils.cpp sc_util.cpp DFG.cpp ssc_utils.cpp assadiMP.cpp assadiMP_test.cpp
LOWERBOUND_FILES = gp_utils.cpp sc_utils.cpp lowerbound.cpp

FLAGS=-std=c++17 -g -pthread
LIBS=
ifeq ($(shell uname -s),Darwin)
	CC=g++-8
else
	CC=g++
	EXTRA=
# -I/panfs/panasas01/cosc/an15739/boost_1_69_0 -L/panfs/panasas01/cosc/an15739/boost_1_69_0 -Wl,-rpath,/panfs/panasas01/cosc/an15739/boost_1_69_0
endif

pg:
	$(CC) $(FLAGS) $(PG_FILES) -o pg $(EXTRA) $(LIBS)
	./pg

pgt:
	$(CC) $(FLAGS)  $(PGT_FILES) -o pgt $(EXTRA) $(LIBS)
	./pgt

dfg:
	$(CC) $(FLAGS)  $(DFG_FILES) -o dfg $(EXTRA) $(LIBS)
	./dfg

dfgt:
	$(CC) $(FLAGS)  $(DFGT_FILES) -o dfgt $(EXTRA) $(LIBS)
	./dfgt

g:
	$(CC) $(FLAGS)  $(G_FILES) -o g $(EXTRA) $(LIBS)
	./g

gt:
	$(CC) $(FLAGS)  $(GT_FILES) -o gt $(EXTRA) $(LIBS)

sssc:
	$(CC) $(FLAGS)  $(SSSC_FILES) -o sssc

sssct:
	$(CC) $(FLAGS)  $(SSSCT_FILES) -o sssct

assadiMP:
	$(CC) $(FLAGS)  $(ASSADIMP_FILES) -o assadiMP

assadiMPt:
	$(CC) $(FLAGS)  $(ASSADIMPT_FILES) -o assadiMPt

lowerbound:
	$(CC) $(FLAGS)  $(LOWERBOUND_FILES) -o lowerbound

# rfgreedy:
# 	$(CC) $(FLAGS)  $(RFGREEDY) -o rfgreedy
# 	./rfgreedy

# ssc_utils_test:
# 	$(CC) $(FLAGS)  $(SSC_UTILS_TEST) -o ssc_utils_test
# 	./ssc_utils_test

# rfgreedy_test:
# 	$(CC) $(FLAGS)  $(RFGREEDY_TEST) -o rfgreedy_test
# 	./rfgreedy_test

# iter_set_cover:
# 	$(CC) $(FLAGS)  $(ITER_SET_COVER) -o iter_set_cover
# 	./iter_set_cover

clean:
	rm pg pgt dfg dfgt g gt sssc sssct

.PHONY: pg pgt dfg dfgt g gt sssc sssct assadiMP assadiMPt lowerbound








