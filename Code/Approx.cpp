// Implements Closest Insertion Algorithm to find a TSP Solution
#include "Approx.h"

tuple<int,vector<int>> Approx(vector<vector<int>> dist, float time, int seed){

    unsigned int nVertices = dist.size();
    // Store the TSP route in path
    std::vector<int> path{seed};
    // Store the distance of all vertices from path
    std::vector<int> distFromPath;
    // Boolean vector keeping track of the vertices on path
    std::vector<bool> vertexOnPath(nVertices, false);
    std::tuple<int,vector<int>> result;

    int pathLength = 0;

    double timeStart = clock(), timeEnd = 0;
    distFromPath = dist[seed];
    vertexOnPath[seed] = true;

    // Add the second vertex to path
    int newVertex =  std::min_element(distFromPath.begin(),distFromPath.end())-distFromPath.begin();
    path.push_back(newVertex);
    pathLength += 2*dist[seed][newVertex];
    vertexOnPath[newVertex] = true;
    distFromPath[newVertex] = inf;

    for(unsigned int i = 0; i < nVertices;  i++){
        if(!vertexOnPath[i])
            distFromPath[i] = min(distFromPath[i], dist[i][newVertex]);
    }

    // Start creating the Ham-Cycle
    while(path.size() < nVertices){
        // Find the next vertex to be added to the path
        newVertex =  std::min_element(distFromPath.begin(),distFromPath.end())-distFromPath.begin();
        vertexOnPath[newVertex] = true;
        distFromPath[newVertex] = inf;

        for(unsigned int i = 0; i < nVertices;  i++){
            if(!vertexOnPath[i])
                distFromPath[i] = min(distFromPath[i], dist[i][newVertex]);
        }

        // Insert the newVertex in between an edge such that the increase in TSP length is minimum
        int insertAfter = path.size()-1;
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
            return make_tuple(pathLength, path);
        }
    }

    return make_tuple(pathLength, path);
}