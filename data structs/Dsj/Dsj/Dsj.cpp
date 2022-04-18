#include <iostream> 
#include <vector>

using namespace std;
class DsjSet 
{
    int* aux, * padre, n;
    void inicializar()
    {
        for (int i = 0; i < n; i++) {
            padre[i] = i;
        }
        posibles.resize(n);
    }

public:

    DsjSet(int n)
    {
        aux = new int[n];
        padre = new int[n];
        this->n = n;
        inicializar();
    }


    int encontrar(int x)
    {

        if (padre[x] != x) 
        {
            padre[x] = encontrar(padre[x]);
        }

        return padre[x];
    }

 
    void unir(int x, int y)
    {
        int xset = encontrar(x);
        int yset = encontrar(y);

        if (xset == yset)
            return;

        if (aux[xset] < aux[yset]) 
        {
            padre[xset] = yset;
        }
        else
        {
            if (aux[xset] > aux[yset]) 
            {
                padre[yset] = xset;
            }
            else 
            {
                padre[yset] = xset;
                aux[xset] = aux[xset] + 1;
            }
        }
    }

    vector<int> posibles;

    int conjunto(int pos)
    {
        int amigos = 0;
        
        for (int i = 0; i < n; i++)
        {
            if (i == pos)
            {
                posibles[i] = -1;
            }
            else
            {
                posibles[i] = i;
            }
        }
        amigos = conjunto_(pos);
        for (int i = 0; i < n; i++)
        {
            posibles[i] = i;
        }
        return amigos;
    }

    int conjunto_(int e)
    {
        int amigos = 0;
        int y;
        for (int x = e; x < n; x++)
        {
            y = posibles[x];
            if (y >= 0 && e != y && encontrar(e) == encontrar(y))
            {
                amigos++;
                posibles[y] = -1,
                amigos += conjunto_(y);
            }
        }

        return amigos;
    }
};

int main()
{
    int N = 0,M = 0;
    cin >> N >> M;

    DsjSet obj(N);
    for (size_t i = 0; i < M; i++)
    {

        int a = 0, b = 0, c = 0;
        for (size_t i = 0; i < M; i++)
        {
            cin >> a >> b >> c;
            obj.unir(a, b);
        }

        int p;
        int aux = 0, max = 0;
        int e = 0;
        cin >> e;
        p = obj.conjunto(e);
        if (p > max)
            max = p;
        cout << max + 1;
        return 0;
    }
}