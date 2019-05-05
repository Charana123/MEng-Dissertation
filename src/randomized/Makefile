SS_FILES = ../gp_utils.cpp ../sc_utils.cpp ../ssc_utils.cpp ../DFG.cpp sp-assadi.cpp sp-assadi-main.cpp
REC_FILES = ../gp_utils.cpp ../sc_utils.cpp ../ssc_utils.cpp ../lazy_greedy.cpp element-sampling.cpp element-sampling_main.cpp
ISS_FILES = ../gp_utils.cpp ../sc_utils.cpp ../ssc_utils.cpp ../lazy_greedy.cpp set-sampling.cpp set-sampling_main.cpp
ASSADIMP_FILES = ../gp_utils.cpp ../sc_utils.cpp ../ssc_utils.cpp ../lazy_greedy.cpp mp-assadi.cpp mp-assadi_main.cpp

FLAGS=-std=c++17 -pthread -O3 -fopenmp
CC=g++-8

rec:
	$(CC) $(FLAGS) $(REC_FILES) -o rec.out

iss:
	$(CC) $(FLAGS) $(ISS_FILES) -o iss.out

spa:
	$(CC) $(FLAGS) $(SS_FILES) -o spa.out
	./spa.out

mpa:
	$(CC) $(FLAGS)  $(ASSADIMP_FILES) -o mpa.out

clean:
	rm *.out

.PHONY: rec spa mpa








