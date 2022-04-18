#include <iostream>
#include <climits>
#include <vector>
#include <set>

#define INFINITY INT_MAX
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

    void eliminarArista(int v1, int v2) {
        if (matriz[v1][v2] != 0) {
            numArista--;
        }
        matriz[v1][v2] = 0;
    }

    bool esArista(int i, int j)
    {
        return matriz[i][j] != 0;
    }

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
                    return 1;

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
        return conjunto(0);
    }

    double greedy(int root, int meta, vector<int> h)
    {
        cout << "*********************" << endl;
        for (auto e : h)
            cout << e << "-";
        cout << "*********************" << endl;
        cout << "Greedy: " << root << " " << meta << endl;
        int pos = root;
        int distancia = 0;
        while (pos != meta)
        {
            int menor = INT_MAX;
            int c = 0;
            for (size_t i = 0; i < n; i++)
            {
                if (matriz[pos][i] > 0)
                {
                    if (menor > h[i])
                    {
                        menor = h[i];
                        c = i;
                    }
                }
            }
            distancia += matriz[pos][c];
            cout << "d_ " << distancia << endl;
            pos = c;
        }
        return distancia;
    }

    double dijkstra(int root, int pos)
    {
        cout << "Dijkstra: " << root << " " << pos << endl;
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
        return distancias[pos];
    }
};

int main()
{
    set<char> sett;
    vector<int> h;
    vector<int> p;
    vector<string> ss;
    char a, b;
    int n, w;
    int aux = int('A');
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b >> w;
        sett.insert(a);
        sett.insert(b);
        ss.push_back({ a,b });
        p.push_back(w);
    }
    for (int i = 0; i < sett.size(); i++)
    {
        cin >> n;
        h.push_back(n);
    }

    cin >> a >> b;
    GraphM* equis = new GraphM(sett.size());
    int c = 0;
    for (auto e : ss)
    {
        equis->setArista(e[0] - aux, e[1] - aux, p[c]);
        cout << e[0] - aux << " " << e[1] - aux << " " << p[c]<<endl;
        c++;
    }
    double salud = equis->dijkstra(int(a) - aux, int(b) - aux);

    double especialista = equis->greedy(int(a) - aux, int(b) - aux, h);

    if (especialista > salud)
        cout << "INAPROPIADO" << endl;
    else
        cout << "APROPIADO" << endl;
    return 0;
}