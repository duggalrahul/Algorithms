#include <vector> 
#include <map>
#include <bits/stdc++.h> 
#include <math.h>
#include <time.h>
#include <tuple>
using namespace std;

std::vector<int> LS1(vector<tuple<int,float,float>> instance, float time, int seed){

    double timeStart = clock();
    int nVertices = instance.size();
    vector<vector<int>> dist(nVertices);  
    std::vector<int> path;
    std::vector<bool> vertexOnPath(nVertices, false);
    int verticesOnPath = 1;

    vertexOnPath[seed] = true;
    path.push_back(seed);

    for(int row = 0; row < nVertices; row++){
        dist[row].resize(nVertices);
    }
    // Create the distance matrix
    for(int row = 0; row < nVertices; row++)
    {
        for(int col = 0; col <= row; col++)
        {
            float dx = get<1>(instance[row])-get<1>(instance[col]);
            float dy = get<2>(instance[row])-get<2>(instance[col]);
            if(row!=col){
                dist[row][col] = int(sqrt(pow(dx,2) + pow(dy,2))+0.50000000001);
                dist[col][row] = dist[row][col];
            }
            else
                dist[row][col] = INT_MAX;          
      }  
    }

    // Start creating the Ham-Cycle
    while(verticesOnPath < nVertices){

        if ((clock() - timeStart) / CLOCKS_PER_SEC >= time) {
            printf("Maximum allowed time exceeded\n");
            return path;
        }

        int newVertex = 0;  
        // Find the next vertex to be added to the path
        int bestdistSorted = INT_MAX;
        for( unsigned int i = 0; i < path.size();  i++){
            auto loc = std::min_element(dist[path[i]].begin(), dist[path[i]].end())-dist[path[i]].begin();
            if(!vertexOnPath[loc] && dist[path[i]][loc] < bestdistSorted){
                bestdistSorted = dist[path[i]][loc];
                newVertex = loc;
            } 
        }
        vertexOnPath[newVertex] = true;
        // Remove the vertex from the set of vertices not on the path
        for( unsigned int i = 0; i < path.size();  i++){
            dist[path[i]][newVertex] = INT_MAX; 
        }

        // Insert the newVertex in between an edge such that the increase in TSP length is minimum
        int insertAfter = 0;
        int df = INT_MAX;
        for( unsigned int i = 0; i < path.size()-1;  i++){

            int d = dist[newVertex][path[i]]+dist[newVertex][path[i+1]]-dist[path[i]][path[i+1]];
            if(d < df){
                d = df;;
                insertAfter = i;

            } 
        }
        path.insert(path.begin()+insertAfter+1, newVertex);

        verticesOnPath++;
    }

    // Print out the solution
    for(unsigned int i = 0; i < path.size(); i++){
        std::cout<<path[i]<<" ";
    }
    std::cout<<std::endl;
    
    return path;
}