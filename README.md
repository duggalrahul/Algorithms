# Algorithms Project


## Instructions
1. The code lies in the folder Code/. 
2. To run an instance, perform the following steps
    - Compile the main file with
  
      ```g++ -Wall -o main main.cpp```
    
    - Execute the object file with
  
      ```./main -inst "../DATA/Atlanta.tsp" -alg "BnB" -time 10 -seed 0```
      
## Notes for team
1. Please assume your function (BnB/Approx/LS1/LS2) is called as follows
    - ```BnB(instance,time,seed)```
    - instance is a tuple defined as <int,string,string>.
    - A tuple represents <index,x_coordinate,y_coordinate>
    
