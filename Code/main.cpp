// compile : g++ -Wall -o main main.cpp
// execute : ./main -inst "../DATA/Atlanta.tsp" -alg "BnB" -time 10 -seed 0


#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <sstream>
#include <iterator>
#include "LS1.cpp"
  

using namespace std;

string INPUT_FORMAT = "./main.cpp -inst <filename> -alg [BnB | Approx | LS1 | LS2] -time <cutoff_in_seconds> [-seed <random_seed>]";


void throw_input_parse_error(){
	cout<<"Please follow the specified input format"<<endl<<INPUT_FORMAT<<endl;
}

tuple<string,string,float,int> parse_input(int argc, char** argv){
	string filename;
	string algorithm;
	float time;
	int seed;

	if (argc != 9) {
        // we assume there are 8 input args
        throw_input_parse_error();
        // return 0;
    }
    else{

    	if ((string)"-inst" == (string)argv[1]) {
    		filename = argv[2];
    	}
    	else{
    		throw_input_parse_error();
    	}

    	if ((string)"-alg" == (string)argv[3]) {
    		algorithm = argv[4];
    	}
    	else{
    		throw_input_parse_error();
    	}

    	if ((string)"-time" == (string)argv[5]) {
    		time = atof(argv[6]);
    	}
    	else{
    		throw_input_parse_error();
    	}

    	if ((string)"-seed" == (string)argv[7]) {
    		seed = atoi(argv[8]);
    	}
    	else{
    		throw_input_parse_error();
    	}
    }

    auto input = std::make_tuple(filename,algorithm,time,seed); 

    return input;

}

vector<tuple<int,float,float>> read_tsp_file(string filename){
	vector<tuple<int,float,float>> instance;
	ifstream tspfile(filename);
	string line;
	int skip_flag = 1;

	if(tspfile.is_open()){
		while ( getline (tspfile,line) )
	    {
	    	// skip until you encounter a line saying "NODE_COORD_SECTION"
			if((string)"NODE_COORD_SECTION" == line){
	    		skip_flag = 0;
	    		continue;
	    	} 
	    	if(skip_flag){
	    		continue;
	    	}

	      	int index;
	      	float x_coordinate,y_coordinate;

	      	if((string)"EOF" != line){
	      		std::istringstream buf(line);
    			std::istream_iterator<std::string> beg(buf), end;

    			std::vector<std::string> tokens(beg, end); // done!

			    index = stoi(tokens[0]);
			    x_coordinate = stof(tokens[1]);
			    y_coordinate = stof(tokens[2]);

			    auto city = make_tuple(index,x_coordinate,y_coordinate);

			    instance.push_back(city);
	      	}
	      	else{
	      		break;
	      	}	      	
	    }

	    tspfile.close();
	}


	

    return instance;


}


int main(int argc, char** argv){
	
	std::tuple<string,string,float,int> input;

	input = parse_input(argc, argv);

	// parse input parameters
	string filename = get<0>(input);
	string algorithm = get<1>(input);
	float time = get<2>(input);
	int seed = get<3>(input);

	// read .tsp file specified by -inst
	vector<tuple<int,float,float>> instance;
	instance = read_tsp_file(filename);

	if(algorithm == (string)"BnB"){
		// add call to branch and bound algorithm here
		// solution = BnB(instance,time,seed);
	}
	else if(algorithm == (string)"Approx"){
		// add call to Approx algorithm here
		// solution = Approx(instance,time,seed);
	}
	else if(algorithm == (string)"LS1"){
		LS1(instance,time,seed);
	}
	else if(algorithm == (string)"LS2"){
		// add call to LS2 algorithm here
		// solution = LS2(instance,time,seed);
	}
   
  
    return 0; 
}