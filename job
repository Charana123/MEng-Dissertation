#!/bin/bash
#SBATCH -t 0-01:00
#SBATCH -p test
#SBATCH --nodes=1
#SBATCH --cpus-per-task=1
#SBATCH -o out # File to which STDOUT will be written
#SBATCH -e err # File to which STDERR will be written

module load tools/git/2.18.0
module load icc/2017.1.132-GCC-5.4.0-2.26
g++ -std=c++17 -pthread -lboost_iostreams -g gp_utils.cpp ssc_utils.cpp pgreedy.cpp pgreedy_main.cpp -o pg
./pg
