# Roads

## Overview

**Roads** is an academic project developed for the *Algorithms and Data Structures (ASA)* course. The goal of the project is to efficiently analyze a **Directed Acyclic Graph (DAG)** representing roads between intersections and to compute information about **all possible paths** between pairs of vertices.

The project focuses on:

- Efficient graph processing using **topological ordering**
- Dynamic programming over DAGs
- Experimental performance analysis by varying graph size and density

---

## Problem Summary

Given a directed acyclic graph:

- Each vertex represents an intersection
- Each directed edge represents a road

The program:

1. Counts the number of distinct paths between all reachable pairs of vertices
2. Assigns each pair \((A,B)\) to a *truck category* based on the number of paths
3. Outputs results only for a given interval of truck categories
4. Reports execution statistics (number of vertices, number of edges, execution time)

All path counts are computed **modulo M**, as required by the specification.

---

## Algorithmic Approach

### Graph Representation

- Adjacency list (`vector<vector<int>>`)
- Graph is guaranteed to be a **DAG**

### Core Algorithm

1. **Topological Sort** (Kahn's algorithm) — `O(V + E)`
2. **Dynamic Programming over DAG**
   - For each source vertex `i`, propagate path counts following topological order
   - Path counts stored in a matrix `caminhos[i][j]`
3. **Filtering & Output**
   - For each pair `(i, j)`, compute:
     ```text
     truck = 1 + caminhos[i][j] % M
     ```
   - Output only if `truck ∈ [m1, m2]`

### Complexity

- **Time complexity:** `O(V · (V + E))`
  - `O(V²)` for sparse graphs
  - `O(V³)` for dense graphs
- **Memory complexity:** `O(V²)` due to the path-count matrix

---

## Experimental Evaluation

To study performance behavior:

- Graph size `N` and density are varied using a custom generator
- Execution time and number of edges `K` are collected automatically
- Results are exported to CSV for analysis

Each program run appends a footer like:

```text
-----------------------
N (vertice): 900
K (arestas): 202002
Tempo: 0.354663 segundos
-----------------------
```

---

## Repository Structure

```text
Roads/
├── main.cpp          # Main solution (graph + DP)
├── gerador_p2.cpp    # Random DAG generator with configurable density
├── run.sh            # Script to generate tests and run experiments
├── extract_time.sh   # Extracts N, K and execution time into CSV
├── testes/           # Generated test outputs
│   ├── teste_900.out
│   ├── teste_1100.out
│   └── ...
└── README.md
```

---

## Compilation

Compile the project using **C++11**:

```bash
g++ -std=c++11 -O2 main.cpp -o roads
```

Compile the generator:

```bash
g++ -std=c++11 -O2 gerador_p2.cpp -o gerador_p2
```

---

## Running Experiments

### Generate and run tests

```bash
chmod +x run.sh
./run.sh
```

This will:

- Generate multiple DAGs of increasing size
- Run the solution
- Save outputs to the `testes/` directory

### Extract performance data

```bash
chmod +x extract_time.sh
./extract_time.sh
```

This produces:

```text
roads_time.csv
```

with the format:

```csv
N,k,time_s
900,202002,0.354663
1100,302500,0.612341
...
```

---

## Graph Density

The generator supports a **density (edge probability)** parameter:

- Density ∈ [0,100]
- Indicates the probability that a possible edge exists

For a directed graph:

```text
K_max = N × (N − 1)
Density = K / K_max
```

Higher density leads to quadratic growth in edges and increased execution time.

---

## Author

Developed by **Afonso Sitima** and **Rafa Dias**\
Bachelor in Computer Science and Engineering

---

## License

This project is intended for **academic use only**.


