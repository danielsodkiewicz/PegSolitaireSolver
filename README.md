C++ program solving Peg solitaire game
========================================

About Peg Solitaire.
----------------------
Peg solitaire (or Solo Noble) is a single player board game involving movement of pegs on a board with holes. In the United Kingdom the game is referred to as Solitaire while the card games are called Patience. The game is also known as Brainvita (especially in India). The first evidence of the game can be traced back to 1697.  More: http://en.wikipedia.org/wiki/Peg_solitaire

Game rules.
--------------------
The rules of Peg solitaire are similar to Checkers, in that a peg can jump over another peg as long as there is an empty hole on the other side.  Once a peg has been jumped over, it is removed from the board.  

The game starts with all the holes on the board filled with a peg except the hole in the center, which is empty. The first move begins with a peg jumping over another peg into an empty hole. A peg can jump left, right, up or down but cannot jump diagonally.  A peg can only jump one peg at a time, but as with Checkers, a peg can make a series of multiple jumps if there are open holes. Play continues with a peg jumping over another peg into an empty hole until there are no possible moves left.   

Winning the game.
----------------------
The game is won when all of the pegs are removed except one, which is in the center hole. 
More: http://www.ehow.com/list_6181682_peg-solitaire-rules.html

Problem complexity
----------------------
For the version with 33 holes (and 32 pegs) of Peg Solitaire there are 577,116,156,815,309,849,672 different game sequences (577+ quintillion possible games), with 40,861,647,040,079,968 solutions. (Source: http://www.durangobill.com/Peg33.html).

An algorithm which blindly checks all the possibilities will not work quickly, and even with a very fast machine it would take years to solve.

In a proposed solution, a “depth first” search is used ( http://en.wikipedia.org/wiki/Depth-first_search) which tries to search (make trial moves) as deeply as possible, and backs up only when it hits a dead end, at which point back tracking is used (http://en.wikipedia.org/wiki/Backtracking).  However, this is not enough to call it a good algorithm because it does not solve the problem in a reasonable time. 

Another improvement is needed - making an informed search which checks to see if a given board configuration was already checked, and if so, does not continue a search on that path. Storing information about already taken paths is implemented with a hash table.

This pseudo code was used http://courses.csail.mit.edu/6.884/spring10/labs/lab5.pdf as an inspiration for the program. However, the final result looks slightly different.

Results: within about 15 seconds the program is finding a solution and prints it out in the form of moves.

The code allows you to test any board configuration, and the algorithm will check if there is a solution to this sequence of pegs on the board. For some initial configurations there is no solution.

The program has a simple terminal interface:
```
Initial board:
  111  
  111  
1111111
1110111
1111111
  111  
  111

Final board:
  000  
  000  
0000000
0001000
0000000
  000  
  000  
```
Screenshots from the program and one of a solution:

```
----------
Final board:
  000  
  000  
0000000
0001000
0000000
  000  
  000  
------------------
SOLUTION
------------------

BOARD:
 ----------x--------
|     1 2 3 4 5 6 7 
|     ---------------
| 1  |     _ _ _    
| 2  |     _ _ _    
| 3  | _ _ _ _ _ _ _
y 4 | _ _ _ _ _ _ _
| 5  | _ _ _ _ _ _ _
| 6  |     _ _ _    
| 7  |     _ _ _    


DIRECTION:
     N    
     ^    
     |    
 W ---> E
     |    
     S    

------------------

STEPS:
Read from bottom to top

------------------
YX Direction
------------------
64 N
56 W
75 N
73 E
45 S
75 N
54 E
57 W
25 S
55 N
43 E
23 S
53 N
51 E
63 N
45 N
47 W
15 S
45 N
43 N
41 E
13 S
43 N
37 W
35 N
31 E
34 W
15 W
13 S
32 E
24 S
```


Other useful links:
---------------------
Online game: http://www.coolmath-games.com/0-pegsolitaire/ (can be used for testing the solution)
How to solve the game YouTUbe video: https://www.youtube.com/watch?v=33UgfA3jt7s



