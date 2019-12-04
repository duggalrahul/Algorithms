// Header file for Simulated Annealing Algorithm
#include <iostream>
#include <fstream>
#include <algorithm>
//#include "/Users/rahul/Projects/headers/stdc++.h" // For rahul's macbook
#include <stdlib.h> 
#include <sstream>
#include <iterator>

#include "auxiliar_func.h"

using namespace std;


bool metropolis_criterion(double cost1, double cost2, double T);
tuple<vector<int>,int,double> simulated_annealing(vtup instance,double time,int seed, vector<tuple<int, double>> &trace);

