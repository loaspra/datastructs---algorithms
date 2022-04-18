#pragma once
#include <vector>
#include <math.h>
#include <fstream>
#include <chrono>
#include <iostream>
using namespace std;

class GraphM
{
private:
    int n;
    int numVertice, numArista;
    int** matriz;
    int* marca;

    int minDistance(float distancia[], int marca[])
    {
        float min = INFINITY;
        int min_index = 0;

        for (int v = 0; v < n; v++)
        {
            if (marca[v] == 0 && distancia[v] <= min)
            {
                min = distancia[v];
                min_index = v;
            }
        }
        return min_index;
    }

    void init_marca()
    {
        for (int i = 0; i < numVertice; i++)
        {
            this->marca[i] = 0;
        }
    }

public:
    vector<int> posi;
    GraphM(int numVertices)
    {
        n = numVertices;
        Init(numVertices);
    }
    ~GraphM() {}

    vector<int> posibles;

    void Init(int n)
    {
        numVertice = n;
        numArista = 0;
        this->marca = new int[n];
        for (int i = 0; i < numVertice; i++)
        {
            this->marca[i] = 0;
        }

        matriz = (int**) new int* [numVertice];
        for (int i = 0; i < numVertice; i++)
        {
            *(matriz + i) = new int[numVertice];
        }

        for (int i = 0; i < numVertice; i++)
        {
            for (int j = 0; j < numVertice; j++)
            {
                matriz[i][j] = 0;
            }
        }
    }

    int longitud()
    {
        return numVertice;
    }

    int aristas()
    {
        return numArista;
    }


    //Modificación de la arista
    //v1, v2 son los vértices
    //w: peso de arista
    void setArista(int v1, int v2, int w)
    {
        if (w > 0)
        {
            if (matriz[v1][v2] == 0)
            {
                numArista++;
            }
            matriz[v1][v2] = w;
        }
    }

    //Eliminar arista
    void eliminarArista(int v1, int v2) {
        if (matriz[v1][v2] != 0) {
            numArista--;
        }
        matriz[v1][v2] = 0;
    }

    //Determina si hay una arista entre i-j
    bool esArista(int i, int j)
    {
        return matriz[i][j] != 0;
    }

    //Retornar el peso de la arista v1-v2
    int getW(int v1, int v2)
    {
        return matriz[v1][v2];
    }

    void print_mat()
    {
        for (int i = 0; i < numVertice; i++)
        {
            for (int j = 0; j < numVertice; j++)
            {
                cout << matriz[i][j] << "\t";
            }
            cout << endl;
        }
    }

    int conjunto(int pos)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (matriz[pos][i] > 0 && marca[pos] != 1)
            {
                this->marca[pos] = 1;
                return conjunto(i);
            }
            else
                if (marca[pos] == 1)
                {
                    return 1;
                }

        }
        return 0;
    }

    bool find(int valor, int c)
    {
        if (matriz[c][valor] != 0)
            return true;
        return false;
    }

    bool unique(vector<int> vec, int val)
    {
        for (auto e : vec)
            if (e == val)
                return false;
        return true;
    }

    bool cycle()
    {
        bool hay = false;
        int equis = 0;
        while (!hay && equis < this->numVertice)
        {
            init_marca();
            hay = conjunto(equis);
            equis++;
        }
        return hay;
    }

    //Esto
    void dijkstra(int root)
    {
        vector<int> path(n);
        vector<int> rpta;
        float* distancias = new float[n];
        path[root] = -1;
        for (int i = 0; i < n; i++)
        {
            distancias[i] = INFINITY;
            marca[i] = 0;
        }
        distancias[root] = 0;

        for (int count = 0; count < n - 1; count++)
        {
            int u = minDistance(distancias, marca);

            marca[u] = 1;

            for (int v = 0; v < n; v++)
                if (marca[v] == 0 && matriz[u][v] && distancias[u] != INFINITY && distancias[u] + matriz[u][v] < distancias[v])
                {
                    path[v] = u;
                    distancias[v] = distancias[u] + matriz[u][v];
                }
        }
        //cout << distancias[n - 1] << endl;
    }
};