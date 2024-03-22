/**
*
*
* @author Ardelean Robert-Emanuel
* @group 30225
*
*
*get_neighbors: Această funcție iterează prin vecinii unui punct dat în grid și
*verifică dacă fiecare vecin este valid. Complexitatea temporală este O(1)
*pentru fiecare verificare a vecinilor, iar deoarece există un număr constant de vecini (4 în acest caz), complexitatea totală este O(1).
*
*
*bfs: Complexitatea temporală a parcurgerii pe lățime (BFS) este O(V + E),
*unde V este numărul de vârfuri (noduri) și E este numărul de muchii din graf. În cel mai rău caz,
*BFS poate vizita toate vârfurile și muchiile. Implementarea BFS furnizată primește și un obiect Operation,
*care pare să fie folosit pentru numărarea operațiilor, dar nu afectează complexitatea temporală globală.
*
*print_bfs_tree: Complexitatea temporală depinde de numărul de noduri atingibile în arborele BFS, fiind O(n), unde n este numărul de noduri atingibile.
*
*shortest_path (incomplet): Complexitatea temporală a acestei funcții depinde de algoritmul folosit pentru calcularea celui mai scurt drum.
*Complexitatea temporală este în mod tipic O(V + E),
*unde V este numărul de vârfuri și E este numărul de muchii.
*
*generateRandomEdges: Complexitatea temporală depinde de numărul de muchii aleatoare de generat și, în cel mai rău caz, este O(numEdges).
*
*În rezumat, complexitatea temporală globală a întregului program depinde de funcția specifică care este executată.
*Partea cea mai semnificativă este de obicei legată de operațiile legate de graf, factorul dominant fiind numărul de noduri (V) și muchii (E) din graf.
*
*
*/

// Include necessary libraries
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <limits.h>
#include <cstdlib> 
#include "bfs.h"

// Function to get neighbors of a given point in a grid
int get_neighbors(const Grid* grid, Point p, Point neighb[])
{
    int count = 0;

    // Check up
    if (p.row - 1 >= 0 && grid->mat[p.row - 1][p.col] == 0) {
        //Checks if moving up from the current point is within the grid bounds
        neighb[count].row = p.row - 1;
        //Checks if the value at the corresponding position in the grid matrix is 0
        neighb[count].col = p.col;
        count++;
    }

    // Check down
    if (p.row + 1 < grid->rows && grid->mat[p.row + 1][p.col] == 0) {
        neighb[count].row = p.row + 1;
        neighb[count].col = p.col;
        count++;
    }

    // Check left
    if (p.col - 1 >= 0 && grid->mat[p.row][p.col - 1] == 0) {
        neighb[count].row = p.row;
        neighb[count].col = p.col - 1;
        count++;
    }

    // Check right
    if (p.col + 1 < grid->cols && grid->mat[p.row][p.col + 1] == 0) {
        neighb[count].row = p.row;
        neighb[count].col = p.col + 1;
        count++;
    }

    return count;
}

// Function to convert a grid representation into a graph representation
void grid_to_graph(const Grid* grid, Graph* graph)
{
    // Initialize a matrix to store nodes for each position in the grid
    Node* nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[4];

    // Compute the number of nodes and allocate memory for each node
    graph->nrNodes = 0;
    for (i = 0; i < grid->rows; ++i) {
        for (j = 0; j < grid->cols; ++j) {
            if (grid->mat[i][j] == 0) {
                nodes[i][j] = (Node*)malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); // Initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            }
            else {
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    k = 0;
    for (i = 0; i < grid->rows; ++i) {
        for (j = 0; j < grid->cols; ++j) {
            if (nodes[i][j] != NULL) {
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    // Compute the adjacency list for each node
    for (i = 0; i < graph->nrNodes; ++i) {
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if (graph->v[i]->adjSize != 0) {
            graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
            k = 0;
            for (j = 0; j < graph->v[i]->adjSize; ++j) {
                if (neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0) {
                    graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if (k < graph->v[i]->adjSize) {
                // get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
            }
        }
    }
}

// Function to free memory allocated for the graph
void free_graph(Graph* graph)
{
    if (graph->v != NULL) {
        for (int i = 0; i < graph->nrNodes; ++i) {
            if (graph->v[i] != NULL) {
                if (graph->v[i]->adj != NULL) {
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}

// Function to perform breadth-first search (BFS) on a graph
void bfs(Graph* graph, Node* s, Operation* op)
{
    //Check if the graph has nodes and if the starting point it's valid
    if (graph == NULL || s == NULL) {
        return;
    }

    /*Initialize nodes:
    This loop initializes each node in the graph
    Nodes are set to COLOR_WHITE indicating they have not been visited
    dist is set to INT_MAX representing an infinite distance from the starting node
    parent is set to NULL initially.*/ 

    for (int i = 0; i < graph->nrNodes; ++i) {
        if (op != NULL)
            op->count(3);
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->dist = INT_MAX;
        graph->v[i]->parent = NULL;
    }

    /* Initialize the queue for BFS:
    A standard queue (bfsQueue) is used to keep track of nodes to be visited
    The starting node s is enqueued, and its color is set to COLOR_GRAY indicating it is in progress
    Its distance is set to 0 since it is the starting node*/

    std::queue<Node*> bfs_queue;
    if (op != NULL)
        op->count(2);
    s->color = COLOR_GRAY;
    s->dist = 0;
    bfs_queue.push(s);

    while (!bfs_queue.empty()) {
        Node* u = bfs_queue.front();
        bfs_queue.pop();

        /* Process neighbors:
        Iterate through the neighbors of the current node u
        If a neighbor visit is white(not visited), it is marked as in progress(COLOR_GRAY), and its distance and parent information are updated
        The neighbor is enqueued for further exploration*/
        for (int i = 0; i < u->adjSize; ++i) {
            Node* visit = u->adj[i];
            if (op != NULL)
                op->count();
            if (visit->color == COLOR_WHITE) {
                if (op != NULL)
                    op->count(3);
                visit->color = COLOR_GRAY;
                visit->dist = u->dist + 1;
                visit->parent = u;

                if (op != NULL) op->count(); // Increment operation count if op is provided

                bfs_queue.push(visit);
            }
        }
        if (op != NULL)
            op->count();
        u->color = COLOR_BLACK; // Mark the current node as processed
    }
}

// Function to print spaces for visualization
void print_spaces(int count) {
    for (int i = 0; i < count; ++i) {
        printf(" ");
    }
}

// Recursive function to print BFS tree
void print_bfs_tree_recursive(Graph* graph, int* p, Point* repr, int number, int node, int level) {
    if (node == -1) {
        return;
    }

    // Print connecting lines
    for (int i = 0; i < level; ++i) {
        print_spaces(4); // Adjust the number of spaces based on your needs
    }

    // Print current node
    printf("(%d %d) \n", repr[node].row, repr[node].col);

    // Recursively print children
    for (int i = 0; i < number; ++i) {
        if (p[i] == node) {
            print_bfs_tree_recursive(graph, p, repr, number, i, level + 1);
        }
    }
}

// Function to print BFS tree
void print_bfs_tree(Graph* graph)
{
    // Represent the BFS tree as a parent array
    int n = 0; // Number of nodes
    int* p = NULL; // Parent array
    Point* repr = NULL; // Representation for each element in p

    // Some of the nodes in graph->v may not have been reached by BFS
    // p and repr will contain only the reachable nodes
    int* transf = (int*)malloc(graph->nrNodes * sizeof(int));
    for (int i = 0; i < graph->nrNodes; ++i) {
        if (graph->v[i]->color == COLOR_BLACK) {
            transf[i] = n;
            ++n;
        }
        else {
            transf[i] = -1;
        }
    }
    if (n == 0) {
        // No BFS tree
        free(transf);
        return;
    }

    int err = 0;
    p = (int*)malloc(n * sizeof(int));
    repr = (Point*)malloc(n * sizeof(Node));
    for (int i = 0; i < graph->nrNodes && !err; ++i) {
        if (graph->v[i]->color == COLOR_BLACK) {
            if (transf[i] < 0 || transf[i] >= n) {
                err = 1;
            }
            else {
                repr[transf[i]] = graph->v[i]->position;
                if (graph->v[i]->parent == NULL) {
                    p[transf[i]] = -1;
                }
                else {
                    err = 1;
                    for (int j = 0; j < graph->nrNodes; ++j) {
                        if (graph->v[i]->parent == graph->v[j]) {
                            if (transf[j] >= 0 && transf[j] < n) {
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if (!err) {
        //Print the tree
        for (int i = 0; i < n; ++i) {
            if (p[i] == -1) {
                print_bfs_tree_recursive(graph, p, repr, n, i, 0);
            }
        }
    }

    if (p != NULL) {
        free(p);
        p = NULL;
    }
    if (repr != NULL) {
        free(repr);
        repr = NULL;
    }
}

// Function to find the shortest path between two nodes in a graph
int shortest_path(Graph* graph, Node* start, Node* end, Node* path[]) {
    if (graph == NULL || start == NULL || end == NULL) {
        return -1;  // Invalid input
    }

    // Initialize nodes
    for (int i = 0; i < graph->nrNodes; ++i) {
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->dist = INT_MAX;
        graph->v[i]->parent = NULL;
    }

    // Initialize the queue for BFS
    std::queue<Node*> bfs_queue;
    start->color = COLOR_GRAY;
    start->dist = 0;
    bfs_queue.push(start);

    while (!bfs_queue.empty()) {
        Node* u = bfs_queue.front();
        bfs_queue.pop();

        // Process neighbors
        for (int i = 0; i < u->adjSize; ++i) {
            Node* visit = u->adj[i];
            if (visit->color == COLOR_WHITE) {
                visit->color = COLOR_GRAY;
                visit->dist = u->dist + 1;
                visit->parent = u;

                bfs_queue.push(visit);
            }
        }
        u->color = COLOR_BLACK;

        // If the end node is reached, reconstruct the path
        if (u == end) {
            int path_Length = 0;
            Node* current_Node = end;

            // Backtrack from end to start to get the path
            while (current_Node != NULL) {
                path[path_Length++] = current_Node;
                current_Node = current_Node->parent;
            }

            // Reverse the path array to get it in the correct order
            for (int i = 0, j = path_Length - 1; i < j; ++i, --j) {
                Node* dammy = path[i];
                path[i] = path[j];
                path[j] = dammy;
            }

            return path_Length;
        }
    }

    // If end is not reachable from start
    return -1;
}

// Function to generate random edges in a graph
void generateRandomEdges(Graph* graph, int numEdges)
{
    int totalNodes = graph->nrNodes;

    for (int i = 0; i < numEdges; ++i) {
        int source = rand() % totalNodes;
        int destination = rand() % totalNodes;

        // Ensure the source and destination are different
        while (source == destination) {
            destination = rand() % totalNodes;
        }

        // Add an edge between source and destination
        graph->v[source]->adjSize++;
        graph->v[source]->adj = (Node**)realloc(graph->v[source]->adj, graph->v[source]->adjSize * sizeof(Node*));
        graph->v[source]->adj[graph->v[source]->adjSize - 1] = graph->v[destination];

        // Since it's an undirected graph, add the reverse edge
        graph->v[destination]->adjSize++;
        graph->v[destination]->adj = (Node**)realloc(graph->v[destination]->adj, graph->v[destination]->adjSize * sizeof(Node*));
        graph->v[destination]->adj[graph->v[destination]->adjSize - 1] = graph->v[source];
    }
}

// Function to test performance of BFS with varying number of edges and vertices
void performance()
{
    int n, i;
    Profiler p("bfs");

    // Vary the number of edges
    for (n = 1000; n <= 4500; n += 100) {
        Operation op = p.createOperation("bfs-edges", n);
        Graph graph;
        graph.nrNodes = 100;
        // Initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }

        generateRandomEdges(&graph, n);

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    // Vary the number of vertices
    for (n = 100; n <= 200; n += 10) {
        Operation op = p.createOperation("bfs-vertices", n);
        Graph graph;
        graph.nrNodes = n;
        // Initialize the nodes of the graph
        graph.v = graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        
        generateRandomEdges(&graph, 4500);

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    p.showReport();
}
