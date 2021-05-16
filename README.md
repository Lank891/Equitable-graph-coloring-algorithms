# Equitable graph coloring algorithms
### Project created by Andrzej Litkowski and Nader Tavana for Chromatic Graph Theory classes
(Summer 2021, Warsaw University of Technology, Faculty of Mathematics and Information Science)

---

## Brief description:
Program takes a graph and applies colors it using given algorithm and then applies recoloring algorithm to make the coloring equitable. Combinations used:
* Greedy coloring + FJK recoloring
* Saturation Largest-First coloring + FJK recoloring
* Greedy coloring + Modified FJK (MFJK) recoloring

Then it shows the results so they can be used to compare the algorithms.

Additionally 9 graphs are prepared as example ones:
* Bipartite K_{2,6},
* Full binary tree with 12 nodes
* Exaple Hamiltonian graph
* Example disconnected graph
* Heawood graph with 14 vertices
* Tesseract graph
* Corona graph K4 K4
* Star graph with 8 vertices
* Petersen graph with 24 vertices
* Disconnected graph that consist of a square and second square with one diagonal
* Two fish-like graphs (k and l) with slightly different ordering of vertices

Files with those exaples are inside `test-graphs` folder

---

## Compilation and usage:
At first compile all `.cpp` files using favourite compiler, for example `g++` to executable `equitable.exe`:

```g++ -Wall -Wextra -Werror -std=c++17  "colorings.cpp" "equitable.cpp" "graph.cpp" "main.cpp" -o "equitable.exe"```

Then run the executable with one argument - file with the graph description:

```./equitable.exe "./test-graphs/example-a-bipartite.txt"```

---

## Graph file format:
Each vertex is represented by a number (id)

Each line of a file represents one vertex with `m` neighbours as `m + 1` numbers separated by spaces: the first number is id of the vertex, then `m` numbers are ids of neighbours. Connections are unidirectional, so if `1` is a neigbour of `3`, then you also should add `3` as a neighbour of `1` to have bidirectional connection.

Note: this representation allows for directed multigraphs, loops with one vertex or even multiple vertices with the same id. Since input is assumed valid, providing file that is not suitable for used algorithms may result in exceptions or garbage results.

Examples (described above) can be found in `test-graphs` folder.

---

## Code documentation:
Code contains documentation comments in `javadocs` format in `.h` files. Additionally much shorter version of this `readme` can be found at the top of `main.cpp` file.