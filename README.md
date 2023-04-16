# Finding The Shortest Distance

Name: Marian Padron

Github Account name: mpadron-neu

Link to your repository: https://github.com/Spring23-CS5008-BOS-Lionelle/homework-11-mpadron-neu.git

How many hours did it take you to complete this assignment (estimate)? 10 hrs

Did you collaborate with any other students/TAs/Professors? If so, tell us who and in what capacity.  
- one per row, add more if needed


Did you use any external resources (you do not have to cite in class material)? (Cite them below)  
- read lines of file : https://www.cppbuzz.com/program-to-read-text-file-line-by-line-in-c
- split string into tokens : https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split#:~:text=To%20split%20a%20string%20we,words%20are%20separated%20by%20space.
- dijkstra shortest path algo : https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
- directed vs undirected : https://www.baeldung.com/cs/graphs-directed-vs-undirected-graph
- Big O of adj matrix vs list : https://www.scaler.com/topics/data-structures/dijkstra-algorithm/


(Optional) What was your favorite part of the assignment? 

(Optional) How would you improve the assignment? 

## Further Thinking Questions 

1. What is the difference between a directed and undirected graph?

   A directed graph does not presume symmetry is the direction of its edges. Meaning, edge A can connect and lead to edge B, but B may not conect to A. Undirected graphs assumes reciprocity in the realationship between the vertices and their edges. Meaning that in a undirected graph A can connect to B, and B connect to A. It is not a one way relationship.

2. What is the Big O of Dijkstra's algorithm.... 
   * Assuming you used an array (or list) to store the vertices.
   The Big O of using an adjacency matrix for Dijkstra's algorithm is O(V^2), where V is the number of vertices in the graph. This is because each vertices in the matrix has to be visited, and then each neighbor has to be visited to find the shortest path. The Big O of implementing the algorithm with an adjacency list would be O((E + V)^2), where E is the number of edges and V the number of vertices. This is because without using a priority queue, a linear search would need to be conducted with would take O(V) for each vertex making it V^2. Additionally, the cost of traversing to each vertex needs to be acounted for which would be O(E).

   * Assuming you used a heap / priority queue to store the vertices.
   When using a priority queue the Big O of Dijkstra's algorithm can be brought down to O((V + E)log V).
   This is because the priority queue is used to store the vertices that have not been visited yet, and they are ordered by their distance from the origin vertex. At each step the vertex with the smallest distance is selected from the priority queue and the neighboring vertices are added to the queue. The operations of the priority queue take O(logV) time and because as the edges are traveled each vertex is added to the queue and removed the total runtime simplifies to O((V + E)logV).

3. Explain in your own words what that means for larger graphs when trying to find the shortest distance. 
   For much larger graphs it is more sensible to implement Dijkstra's algorithm using a priority queue as the difference in runtime between O(V^2) and O((V + E)logV) is exponential. For larger graphs the amount of traveling the algorithm has to do to compute the shortest paths will keep growing in time complexity unless a more efficient data structure is used. This is especially true depending on the type of graph, it is more dense (has more connectivity) or more sparse.

4. For this assignment, you didn't need the most "efficient" set of data structures (for example, a heap wasn't required). However, think on the scale of google/apple maps - they have to deal with millions of vertices and edges. What data structures would you use to store the graph? Why? Somethings to consider - would you be able to store the entire graph at a time? Could you break it up into smaller pieces? How would you do that? Would there be advantages to caching/memoization of paths? You are free to explore your thoughts on this subject/reflect on various ideas. Other than a realization of some scalability of problems, there isn't a wrong answer. 


5. Related to shortest distance, is a problem called the "messenger" or "traveling sales (man/person)" problem commonly abbreviated to TSP. This problem is to find the shortest path that visits **every** vertex in a graph. Another way to look at it, is you are an delivery driver, and you have a series of packages to deliver. Can you find an optimal path for your deliveries that minimizes the total distance traveled? Imagine if you had 5 stops. How many different paths are there?  There are 120 possible paths to look at! (assuming fully connected routes). 
   * How many possible paths are there if you have 6 stops?
   * How many possible paths are there if you have 10 stops?
6. What type of growth is this problem? 
7. Take some time to research TSP problems. It falls under a certain classification of problems? What is it? 
8. Provide some examples of fields / problems that use TSP.



---
Note: we are having you explore TSP, so you can see the terms used for problem classification that you will also explore in more depth in 5800. You will not be asked to know about TSP outside of this assignment or even problem classification. Computer Science is often about dealing with problems considered "too hard" or "impossible", and finding ways to make them possible! As such, knowing topics such as N, NP, NP-Complete, etc. is important to understand the limits (to break).