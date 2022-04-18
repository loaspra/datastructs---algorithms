#include <iostream>
#include <vector>
#include <set>
using namespace std;

constexpr auto nulo = "";


#include <iostream>

using namespace std;



template<typename E>
class ListaArreglo 
{
private:
    int tamMax;
    int tamLista;
    int actual;
    E* arreglo;
public:

    ListaArreglo(int tamMax = 100) {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    ~ListaArreglo() {
        delete[] this->arreglo;
    }

    void moverAInicio() {
        this->actual = 0;
    }

    void moverAlFinal() {
        this->actual = this->tamLista;
    }

    void siguiente() {
        if (this->actual < this->tamLista)
            this->actual++;
    }

    void anterior() {
        if (this->actual != 0) {
            this->actual--;
        }
    }

    void agregar(E elemento) {
        this->arreglo[this->tamLista++] = elemento;
    }

    void insertar(E elemento) {
        for (int i = tamLista; i > actual; i--) {
            this->arreglo[i] = this->arreglo[i - 1];
        }
        this->arreglo[actual] = elemento;
        this->tamLista++;
    }

    void limpiar() {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    E eliminar() {
        E temp = this->arreglo[actual];
        for (int i = actual; i < this->tamLista - 1; i++) {
            this->arreglo[i] = this->arreglo[i + 1];
        }
        this->tamLista--;
        return temp;
    }

    int longitud() {
        return this->tamLista;
    }

    int posicionActual() {
        return this->actual;
    }

    void moverAPosicion(int pos) {
        if (pos >= 0 && pos < this->tamLista) {
            this->actual = pos;
        }
    }

    E getValor()
    {
        return this->arreglo[this->actual];
    }

    E getValor(int pos) 
    {
        return this->arreglo[pos];
    }

};

template<typename E>
class Nodo
{
public:
    E valor;
    Nodo* siguiente;
    //Constructor
    Nodo(E valor, Nodo* siguiente = NULL)
    {
        this->valor = valor;
        this->siguiente = siguiente;
    }

    Nodo()
    {
        this->valor = nulo;
        this->siguiente = NULL;
    }
};

template<typename E>
class ListaNode
{
private:
    int tamMax;
    int tamLista;
    int actual;
    int auxiliar;
    Nodo<E>* arreglo;
    Nodo<E>* colisiones;
public:
    ListaNode(int tamMax = 500) {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new Nodo<E>[this->tamMax];
        this->auxiliar = tamMax;
        this->colisiones = new Nodo<E>[this->tamMax];
        for (int i = 0; i < tamMax; i++)
        {
            this->arreglo[i].valor = nulo;
            this->arreglo[i].siguiente = NULL;

            this->colisiones[i].valor = nulo;
            this->colisiones[i].siguiente = NULL;
        }
    }

    ~ListaNode() {
        delete[] this->arreglo;
    }

    void moverAInicio() {
        this->actual = 0;
    }

    void moverAlFinal() {
        this->actual = this->auxiliar;
    }

    void siguiente() {
        if (this->actual < this->tamLista)
            this->actual++;
    }

    void anterior() {
        if (this->actual != 0) {
            this->actual--;
        }
    }

    void insertar(E elemento)
    {
        if (this->arreglo[actual].valor == nulo)
        {
            this->arreglo[actual].valor = elemento;
            this->tamLista++;
        }
        else
        {
//            this->colisiones[actual].valor = this->colisiones[actual].valor + 1;
            this->arreglo[actual].siguiente = new Nodo<E>;
            this->arreglo[actual].siguiente->valor = elemento;
        }
    }

    void limpiar() {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new Nodo<E>[this->tamMax];
    }

    E eliminar()
    {
        E temp = this->arreglo[actual].valor;
        this->arreglo[actual].valor = nulo;
        this->auxiliar--;
        return temp;
    }

    int longitud() {
        return this->tamLista;
    }

    int posicionActual() {
        return this->actual;
    }

    void moverAPosicion(int pos) {
        if (pos >= 0 && pos < this->tamMax)
        {
            this->actual = pos;
        }
    }

    int get_tamMax()
    {
        return this->tamMax;
    }

    E getValor() {
        return this->arreglo[this->actual].valor;
    }

    void repeticiones()
    {
        int min = 0;
        int r = 0;
        for (auto e = 0; e < tamMax; e++)
        {
            if (colisiones[e].valor > 0)
            {
                if (colisiones[e].valor > min)
                {
                    r = 0;
                    min = colisiones[e].valor;
                }
                if (colisiones[e].valor == min)
                {
                    r++;
                }
            }
        }
        cout << min << endl;
    }

};



template<typename Key>
class Set {
private:
public:

    Set() {}

    virtual ~Set() {}

    virtual void limpiar() = 0;

    virtual void insertar(Key k) = 0;

    virtual void remover(Key k) = 0;

    virtual Key removerCualquiera() = 0;

    virtual bool encontrar(Key k) = 0;

    virtual int longitud() = 0;
};


//SET_chaining
template<typename Key>      //solo funciona para strings btw
class SET_chaining : public Set<Key>
{
private:
    ListaNode<Key>* lista;
public:
    //Constructor
    SET_chaining(int tamanho = 100)
    {
        lista = new ListaNode<Key>(tamanho);
    }

    ~SET_chaining()
    {
        delete lista;
    }

    void limpiar()
    {
        this->lista->limpiar();
    }

    //strings
    int Hash(Key k)
    {
        int c = 0;
        int ash = 0;
        for (auto e : k)
        {
            ash += int(e) + 30 * c;
            c++;
        }
        return (ash % this->lista->get_tamMax());
    }

    void insertar(Key k)
    {
        int indice = Hash(k);
        lista->moverAPosicion(indice);
        lista->insertar(k);
    }

    bool encontrar(Key k)
    {
        int indice = Hash(k);
        this->lista->moverAPosicion(indice);
        Key value = this->lista->getValor();
        if (value != "")
        {
            return true;
        }
        return false;
    }

    void remover(Key k)
    {
        int indice;
        if (encontrar(k))
        {
            indice = Hash(k);
            lista->moverAPosicion(indice);
            lista->eliminar();
        }
    }

    Key removerCualquiera()
    {
        lista->moverAlFinal();
        lista->anterior();
        Key temp = lista->eliminar();
        return temp;
    }

    int get_tamMax()
    {
        return this->lista->get_tamMax();
    }

    int longitud()
    {
        return this->lista->longitud();
    }
};


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

    double greedy(int root, int meta, ListaArreglo<int> h)
    {
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
                    if (menor > h.getValor(i))
                    {
                        menor = h.getValor(i);
                        c = i;
                    }
                }
            }
            distancia += matriz[pos][c];
            pos = c;
        }
        return distancia;
    }

    //Esto
    double dijkstra(int root, int pos)
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
        return distancias[pos];
    }
};

int main()
{
    SET_chaining<string> sett;
    ListaArreglo<int> h;
    ListaArreglo<int> p;
    ListaArreglo<string> ss;
    string a, b;
    int n, w;
    int aux = int('A');
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b >> w;
        sett.insertar(a);
        sett.insertar(b);
        ss.agregar({(a[0]),(b[0])});
        p.agregar(w);
    }
    for (int i = 0; i < sett.longitud(); i++)
    {
        cin >> n;
        h.agregar(n);
    }

    cin >> a >> b;
    GraphM* equis = new GraphM(sett.longitud());
    int c = 0;

    for (ss.moverAInicio(); ss.posicionActual() < ss.longitud(); ss.siguiente())
    {
        equis->setArista(int(ss.getValor()[0]) - aux, int(ss.getValor()[1]) - aux, p.getValor(c));
        c++;
    }
   

    double salud = equis->dijkstra(int(a[0]) - aux, int(b[0]) - aux);
    
    double especialista = equis->greedy(int(a[0]) - aux, int(b[0]) - aux, h);

    if (especialista > salud)
        cout << "INAPROPIADO" << endl;
    else
        cout << "APROPIADO" << endl;
    exit(0);
}