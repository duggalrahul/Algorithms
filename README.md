# Algorithms Project


## Instructions
1. The code lies in the folder Code/. 
2. To run an instance, perform the following steps within Code/
    - Compile the project by runing make
  
      ```make```
    
    - Execute the object file with
  
      1. Branch and bound
            ```./tsp_main -inst "../DATA/Atlanta.tsp" -alg "BnB" -time 10 -seed 0```
      2. Approximation algorithm
            ```./tsp_main -inst "../DATA/Atlanta.tsp" -alg "Approx" -time 10 -seed 0```
      3. LS1 (Hill climbing)
            ```./tsp_main -inst "../DATA/Atlanta.tsp" -alg "LS1" -time 10 -seed 0```
      4. LS2 (Simulated annealing)
            ```./tsp_main -inst "../DATA/Atlanta.tsp" -alg "LS2" -time 10 -seed 0```

3. The above commands create the .sol and .trace files within DATA/
