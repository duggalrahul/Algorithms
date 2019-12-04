#include <iostream>
#include <fstream>
#include <algorithm>
//#include "/Users/rahul/Projects/headers/stdc++.h" // For rahul's macbook
#include <stdlib.h> 
#include <sstream>
#include <iterator>
#include "auxiliar_func.h"

using namespace std;


tuple<vector<int>,double,double> hill_climbing(vtup instance,double time,int seed, vector<tuple<int, double>> &trace);
