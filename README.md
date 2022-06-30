# A_Star_Implementation
- This is the first Project from [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)
- The Project Implements the A_Star Searching Algorithm, which finds a path between between ```2 coordinates``` on a grid.
- Implemented Algorithm Works as:
  - The *A_star algorithm* behaviour is like a *BFS algorithm* but with additional priority constraint.
  - At each ```node``` (say ```n1```), the next path ```node```(say ```n2```) is selected based on ```int f``` value, which is again the sum of ```int g``` and ```int h``` value.
  - where ```int g``` is the number of steps required to reach ```n2```(or simply 
  [Manhattan Distance](https://www.sciencedirect.com/topics/mathematics/manhattan-distance#:~:text=The%20Manhattan%20distance%20is%20defined,which%20is%20its%20L1%2Dnorm.)) from ```n1``` and can be calculated dynamically at each step,<br>
  and ```h (Heuristic)``` value is [Manhattan Distance](https://www.sciencedirect.com/topics/mathematics/manhattan-distance#:~:text=The%20Manhattan%20distance%20is%20defined,which%20is%20its%20L1%2Dnorm.)
  between node ```n2``` and ```goal_position/finish_position```<br>
  i.e. ```f(n) = g(n) + h(n)```

  Code Structure of Implementation:
  ![cannot load](./resources/addtoopen.png "Code Structure")
