#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <fstream>
#include <sstream>

class Graph {
public:
    int num_vertices;
    std::vector<std::vector<int>> adjMatrix;
    std::vector<std::list<int>> adjList;

    Graph(int n) : num_vertices(n), adjMatrix(n, std::vector<int>(n, 0)), adjList(n) {}

    void addEdge(int src, int dest, int weight) {
        adjMatrix[src][dest] = weight;
        
        if (src != dest) {
            adjMatrix[dest][src] = weight;
        }

        if (std::find(adjList[src].begin(), adjList[src].end(), dest) == adjList[src].end()) {
            adjList[src].push_back(dest);
            adjList[src].sort();
        }

        if (src != dest) {
            if (std::find(adjList[dest].begin(), adjList[dest].end(), src) == adjList[dest].end()) {
                adjList[dest].push_back(src);
                adjList[dest].sort();
            }
        }
    }

    void printGraph() {
        std::cout << "Numero de Vertices: " << num_vertices << "\n";
        std::cout << "Matriz de adjacencia:\n";
        std::cout << "[";
        for (int i = 0; i < num_vertices; ++i) {
            std::cout << "[";
            for (int j = 0; j < num_vertices; ++j) {
                std::cout << adjMatrix[i][j];
                if (j < num_vertices - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "]";
            if (i < num_vertices - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
        
        std::cout << "Lista de Adjacencia:\n";
        std::cout << "[";
        for (int i = 0; i < num_vertices; ++i) {
            std::cout << "[";
            for (auto it = adjList[i].begin(); it != adjList[i].end(); ++it) {
                std::cout << *it;
                if (std::next(it) != adjList[i].end()) {
                    std::cout << ", ";
                }
            }
            std::cout << "]";
            if (i < num_vertices - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }

    void BFS(int start, int end) {
        std::vector<bool> visited(num_vertices, false);
        std::vector<int> parent(num_vertices, -1);
        std::queue<int> q;

        visited[start] = true;
        q.push(start);
        bool pathFound = false;

        while (!q.empty() && !pathFound) {
            int u = q.front();
            q.pop();

            for (int v : adjList[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);

                    if (v == end) {
                        pathFound = true;
                        break;
                    }
                }
            }
        }

        if (pathFound) {
            std::cout << "Caminho encontrado: ";
            printPath(parent, end);
            std::cout << "\n";
        } else {
            std::cout << "Nao ha caminho entre os vertices " << start << " e " << end << "\n";
        }
    }

    void DFS(int start) {
        std::vector<bool> visited(num_vertices, false);
        std::stack<int> stack;

        stack.push(start);

        while (!stack.empty()) {
            int v = stack.top();
            stack.pop();

            if (!visited[v]) {
                std::cout << "Vertice: " << v << "\n";
                visited[v] = true;
            }

            for (auto it = adjList[v].rbegin(); it != adjList[v].rend(); ++it) {
                int u = *it;
                if (!visited[u]) {
                    stack.push(u);
                }
            }
        }
    }

    int countComponents() {
        std::vector<bool> visited(num_vertices, false);
        int count = 0;

        for (int v = 0; v < num_vertices; ++v) {
            if (!visited[v]) {
                std::stack<int> stack;
                stack.push(v);
                
                while (!stack.empty()) {
                    int u = stack.top();
                    stack.pop();
                    
                    if (!visited[u]) {
                        std::cout << "Vertice: " << u << "\n";
                        visited[u] = true;
                        
                        for (auto it = adjList[u].rbegin(); it != adjList[u].rend(); ++it) {
                            int neighbor = *it;
                            if (!visited[neighbor]) {
                                stack.push(neighbor);
                            }
                        }
                    }
                }
                
                ++count;
            }
        }

        std::cout << "Numero de Componentes: " << count << "\n";
        return count;
    }

private:
    void printPath(const std::vector<int>& parent, int j) {
        if (parent[j] == -1) {
            std::cout << j << " ";
            return;
        }
        printPath(parent, parent[j]);
        std::cout << j << " ";
    }
};

Graph loadGraphFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << fileName << "\n";
        exit(EXIT_FAILURE);
    }

    int n;
    file >> n;
    Graph g(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int weight;
            file >> weight;
            g.adjMatrix[i][j] = weight;
            
            if (weight != 0) {
                if (std::find(g.adjList[i].begin(), g.adjList[i].end(), j) == g.adjList[i].end()) {
                    g.adjList[i].push_back(j);
                    g.adjList[i].sort();
                }
            }
        }
    }

    file.close();
    return g;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo1> <arquivo2> ... <arquivoN>\n";
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        Graph graph = loadGraphFromFile(argv[i]);

        graph.printGraph();
        graph.DFS(0);
        graph.BFS(0, 3);
        graph.countComponents();
    }

    return 0;
}