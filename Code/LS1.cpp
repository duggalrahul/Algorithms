<<<<<<< HEAD
#include <vector> 
#include <map>
#include <bits/stdc++.h> 
#include <math.h>
#include <time.h>
#include <tuple>
#include "auxiliar_func.h"
using namespace std;

std::tuple<double,vector<int>> LS1(vector<tuple<int,float,float>> instance, float time, int seed){
=======
#include "LS1.h"

std::vector<int> LS1(vector<tuple<int, double, double>> instance, float time, int seed){
>>>>>>> a50b97a8d65933397980c45d367613c61f92706b

    unsigned int nVertices = instance.size();
    td::tuple<double,vector<int>> result;
    // Maintain a distance matrix to keep track
    // vector<vector<int>> dist(nVertices);  
    // Store the TSP route in path
    std::vector<int> path{seed};
    // Store the distance of all vertices from path
    std::vector<int> distFromPath;
    // Boolean vector keeping track of the vertices on path
    std::vector<bool> vertexOnPath(nVertices, false);

    int pathLength = 0;

<<<<<<< HEAD
    // for(unsigned int row = 0; row < nVertices; row++){
    //     dist[row].resize(nVertices);
    // }
    // // Create the distance matrix
    // for(unsigned int row = 0; row < nVertices; row++)
    // {
    //     for(unsigned int col = 0; col <nVertices; col++)
    //     {
    //         float dx = get<1>(instance[row])-get<1>(instance[col]);
    //         float dy = get<2>(instance[row])-get<2>(instance[col]);
    //         if(row!=col){
    //             dist[row][col] = int(sqrt(pow(dx,2) + pow(dy,2))+0.50000000001);
    //             dist[col][row] = dist[row][col];
    //         }
    //         else
    //             dist[row][col] = INT_MAX;          
    //   }  
    // }
=======
    for(unsigned int row = 0; row < nVertices; row++){
        dist[row].resize(nVertices);
    }
    // Create the distance matrix
    for(unsigned int row = 0; row < nVertices; row++)
    {
        for(unsigned int col = 0; col <nVertices; col++)
        {
			double dx = get<1>(instance[row]) - get<1>(instance[col]);
			double dy = get<2>(instance[row]) - get<2>(instance[col]);
            if(row!=col){
                dist[row][col] = int(sqrt(pow(dx,2) + pow(dy,2))+0.50000000001);
                dist[col][row] = dist[row][col];
            }
            else
                dist[row][col] = INT_MAX;          
      }  
    }
>>>>>>> a50b97a8d65933397980c45d367613c61f92706b

    double timeStart = clock(), timeEnd = 0;
    distFromPath = dist[seed];
    vertexOnPath[seed] = true;

    // Add the second vertex to path
    int newVertex =  std::min_element(distFromPath.begin(),distFromPath.end())-distFromPath.begin();
    path.push_back(newVertex);
    pathLength += dist[seed][newVertex];
    vertexOnPath[newVertex] = true;
    distFromPath[newVertex] = INT_MAX;

    for(unsigned int i = 0; i < nVertices;  i++){
        if(!vertexOnPath[i])
            distFromPath[i] = min(distFromPath[i], dist[i][newVertex]);
    }

    // Start creating the Ham-Cycle
    while(path.size() < nVertices){

        // Find the next vertex to be added to the path
        newVertex =  std::min_element(distFromPath.begin(),distFromPath.end())-distFromPath.begin();
        vertexOnPath[newVertex] = true;
        distFromPath[newVertex] = INT_MAX;

        for(unsigned int i = 0; i < nVertices;  i++){
            if(!vertexOnPath[i])
                distFromPath[i] = min(distFromPath[i], dist[i][newVertex]);
        }

        // Insert the newVertex in between an edge such that the increase in TSP length is minimum
        int insertAfter = path.back();
        int df = dist[path[0]][newVertex] + dist[newVertex][path.back()] - dist[path[0]][path.back()];
        for( unsigned int i = 0; i < path.size()-1;  i++){
            int d = dist[path[i]][newVertex] + dist[newVertex][path[i+1]] - dist[path[i]][path[i+1]];
            if(d < df){
                df = d;
                insertAfter = i;
            } 
        }
        pathLength += df;
        path.insert(path.begin()+insertAfter+1, newVertex);

        timeEnd = (clock() - timeStart) / CLOCKS_PER_SEC;
        if ( timeEnd >= time) {
            printf("Maximum allowed time exceeded.\n");
            return path;
        }
    }
    pathLength += dist[path[0]][path.back()];
    path.push_back(pathLength);
    // Print out the solution
    for(unsigned int i = 0; i < path.size(); i++){
        std::cout<<path[i]<<" ";
    }
    std::cout<<std::endl;
    result=make_tuple(timeEnd, path);
    std::cout<<"time:"<< get<0>result << endl; 
    return path;
}