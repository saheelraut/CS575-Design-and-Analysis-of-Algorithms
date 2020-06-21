#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//Printing nodes between source and destination
void printPath(int i, int j, int **P)
{
    if (P[i][j] != 0)
    {
        printPath(i, P[i][j], P);
        cout << "V" << P[i][j] + 1 << " ";
        printPath(P[i][j], j, P);
        return;
    }
    else
        return;
}

int main()
{
    srand(time(0));
    int random_number = rand() % 5 + 6;
    cout << "The selected Random Number is " << random_number << '\n';
    int A[random_number][random_number], D[random_number][random_number], i, j, k;
    int **P;
    P = new int *[random_number];
    for (i = 0; i < random_number; ++i)
    {
        P[i] = new int[random_number];
    }
    for (i = 0; i < random_number; i++)
    {
        for (j = 0; j < random_number; j++)
        {
            if (i == j)
            {
                A[i][j] = 0;
                D[i][j] = 0;
                P[i][j] = 0;
            }
            else if (i < j)
            {
                D[j][i] = D[i][j] = A[j][i] = A[i][j] = rand() % 10 + 1;
                P[i][j] = P[j][i] = 0;
            }
        }
    }

    //Filling the P matrix with value of k and D matrix 
    for (k = 0; k < random_number; k++)
    {
        for (i = 0; i < random_number; i++)
        {
            for (j = 0; j < random_number; j++)
            {
                if (D[i][j] > (D[i][k] + D[k][j]))
                {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
            }
        }
    }
    // Printing Adjacency
    cout << "Adjacency matrix: \n";
    for (i = 0; i < random_number; i++)
    {
        for (j = 0; j < random_number; j++)
        {
            cout << setw(4) << A[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nThe shortest distance between following vertices are: \n";

    // Prinitng nodes and distance between them
    for (i = 0; i < random_number; i++)
    {
        cout << "\nV" << i + 1 << "-Vj\n";
        
        for (j = 0; j < random_number; j++)
        {
            if (i != 0 || j != 0)
            {
                cout << "V" << i + 1 << " ";
                printPath(i, j, P);
                cout << "V" << j + 1 << " ";
                cout << ":" << D[i][j] << " ";
                cout << "\n";
            }
        }
    }
    return 0;
}
