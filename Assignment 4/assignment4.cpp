#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//---------- Kruskal's ALgortithm------------//

class Find_Union
{
public:
    int size;

    int height[100];

    int set[100];

    int numberofComponents;

    Find_Union(int size)
    {

        this->size = numberofComponents = size;

        for (int i = 0; i < size; i++)
        {
            set[i] = i;
            height[i] = 1;
        }
    }

    int find3(int x)
    {

        int root = x;
        while (root != set[root])
        {
            root = set[root];
        }
        int node = x;
        while (node != root)
        {
            int parent = set[node];
            set[node] = root;
            node = parent;
        }

        return root;
    }

    bool Isconnected(int x, int y)
    {
        return find3(x) == find3(y);
    }

    int componentSize(int x)
    {
        return height[find3(x)];
    }

    int components()
    {
        return numberofComponents;
    }

    void union3(int repx, int repy)
    {

        if (height[repx] == height[repy])
        {
            height[repx]++;
            set[repy] = repx;
        }

        else if (height[repx] > height[repy])
        {
            set[repx] = repy;
        }
        else
        {
            set[repx] = repy;
        }

        numberofComponents--;
    }
};

class Edge
{
public:
    int node_source;
    int node_destination;
    int node_weight;

    Edge() {}

    Edge(int node_source, int node_destination, int node_weight)
    {
        this->node_source = node_source;
        this->node_destination = node_destination;
        this->node_weight = node_weight;
    }
};

void Sort(Edge *edges, int size)
{
    int i, j;
    Edge *key = new Edge();
    for (i = 1; i < size; i++)
    {
        key->node_weight = edges[i].node_weight;
        key->node_source = edges[i].node_source;
        key->node_destination = edges[i].node_destination;
        j = i - 1;

        while (j >= 0 && edges[j].node_weight > key->node_weight)
        {
            edges[j + 1].node_weight = edges[j].node_weight;
            edges[j + 1].node_source = edges[j].node_source;
            edges[j + 1].node_destination = edges[j].node_destination;
            j = j - 1;
        }
        edges[j + 1].node_weight = key->node_weight;
        edges[j + 1].node_source = key->node_source;
        edges[j + 1].node_destination = key->node_destination;
    }
}

void kruskal(int **a, Edge *edges, int size, int random_number)
{
    int i, j, k;
    int height[random_number];
    Find_Union fnU = Find_Union(random_number);
    Edge *spannedEdges = new Edge[size];
    Edge e = Edge(-1, -1, -1);

    k = 0;
    j = 0;
    while (k != (random_number - 1))
    {
        e = edges[j];
        j++;
        if (!fnU.Isconnected(e.node_source, e.node_destination))
        {
            spannedEdges[k] = Edge(e.node_source, e.node_destination, e.node_weight);
            k++;
            fnU.union3(e.node_source, e.node_destination);
        }
    }
    cout << "\nEdge \tWeight\n";
    int Kruskals[random_number][random_number];
    memset(Kruskals, 0, sizeof(Kruskals[0][0]) * random_number * random_number);

    while (k > 0)
    {
        e = spannedEdges[--k];

        cout << "V" << e.node_source << " - "
             << "V" << e.node_destination << "  \t " << e.node_weight << '\n';
        Kruskals[e.node_source][e.node_destination] = Kruskals[e.node_destination][e.node_source] = e.node_weight;
    }

    cout << "Kruskal's matrix: \n";
    for (i = 0; i < random_number; i++)
    {
        for (j = 0; j < random_number; j++)
        {

            cout << setw(4) << Kruskals[i][j] << " ";
        }
        cout << "\n";
    }
}

//---------- Prims ALgortithm------------//

void display_minimum_spanning_tree(int parent[], int random_number, int **A)
{
    int Prims[random_number][random_number];
    memset(Prims, 0, sizeof(Prims[0][0]) * random_number * random_number);
    cout << "\nEdge \t \tWeight\n";
    for (int i = 1; i < random_number; i++)
    {
        cout << "V" << parent[i] << " - "
             << "V" << i << " \t" << setw(4) << A[i][parent[i]] << " \n";
        Prims[i][parent[i]] = A[i][parent[i]];
        Prims[parent[i]][i] = A[parent[i]][i];
        Prims[parent[i]][i] = A[i][parent[i]];
    }

    cout << "Prims Matrix:\n";
    for (int j = 0; j < random_number; j++)
    {
        for (int k = 0; k < random_number; k++)
        {
            cout << setw(4) << Prims[j][k] << " ";
        }
        cout << "\n";
    }
}

int minKey(int key[], bool mstSet[], int random_number)
{
    int min = INT_MAX;
    int min_index;

    for (int v = 0; v < random_number; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void init_prims(int key[], bool mstSet[], int parent[], int random_number)
{
    for (int i = 0; i < random_number; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;
}

void prim_minimum_spanning_tree(int **A, int random_number)
{
    int parent[random_number];
    int key[random_number];
    bool mstSet[random_number];
    init_prims(key, mstSet, parent, random_number);

    for (int count = 0; count < random_number - 1; count++)
    {

        int u = minKey(key, mstSet, random_number);

        mstSet[u] = true;

        for (int v = 0; v < random_number; v++)
        {
            if (A[u][v] && mstSet[v] == false && A[u][v] < key[v])
            {
                parent[v] = u, key[v] = A[u][v];
            }
        }
    }
    display_minimum_spanning_tree(parent, random_number, A);
}

int main()
{
    srand(time(0));
    int random_number = rand() % 5 + 6;
    cout << "The selected Random Number is " << random_number << '\n';
    int i, j;
    int **A;
    int option;
    int maxSize;
    A = new int *[random_number];
    for (i = 0; i < random_number; ++i)
    {
        A[i] = new int[random_number];
    }
    maxSize = (random_number * random_number - random_number) / 2;
    Edge *edges = new Edge[maxSize];
    int k = 0;

    // Filling the Adjacency matrix with random number
    for (i = 0; i < random_number; i++)
    {
        for (j = 0; j < random_number; j++)
        {
            if (i == j)
            {
                A[i][j] = 0;
            }
            else if (i < j)
            {
                A[j][i] = A[i][j] = rand() % 10 + 1;
                edges[k] = Edge(i, j, A[i][j]);
                k++;
            }
        }
    }

    // Printing Random Adjacency matrix
    cout << "Random Adjacency matrix: \n";
    for (i = 0; i < random_number; i++)
    {
        for (j = 0; j < random_number; j++)
        {
            cout << setw(4) << A[i][j] << " ";
        }
        cout << "\n";
    }
    // Option to select the algorithm
    cout << "Enter 1 for Prim's Algorithm and 2 for Kruskal's Algorithm\n";
    cin >> option;
    if (option == 1)
    {
        cout << "Prims Algorithm\n";
        prim_minimum_spanning_tree(A, random_number);
    }
    else if (option == 2)
    {
        cout << "Kruskal's Algorithm\n";
        Sort(edges, k);
        kruskal(A, edges, k, random_number);
    }
    else
    {
        //print in case of wrong input
        cout << " Error: Wrong Option Entered. I only have prim and kruskal algorithm.\n";
        cout << "Exiting\n";
    }

    return 0;
}