#include "BinaryTree.h"
#include "AVL.h"
#include <random>
#include <iostream>

using namespace std;
using namespace chrono;

double sum;
random_device rd;
default_random_engine generator(rd());
uniform_int_distribution<long long unsigned> distribution(0, 0xF424F1);
BST<int>* aux = new BST<int>;
AVL<int>* aucs = new AVL<int>;
unsigned int l = distribution(generator);
steady_clock::time_point Ins0_ini, Ins0_end, Srch0_ini, Srch0_end, Del0_ini, Del0_end, Ins1_ini, Ins1_end, Srch1_ini, Srch1_end, Del1_ini, Del1_end;
duration<double> t_ins0, t_srch0, t_del0, t_ins1, t_srch1, t_del1;
steady_clock::time_point aux0, aux1;
vector<int> data;
double t_insM, t_srchM, t_delM;

double mean_search_bst(int N)
{
	sum = 0;
	aux->limpiar();
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t i = 0; i < N - 1; i++)
		{
			l = distribution(generator);
			aux->insertar(l);
		}
		aux->insertar(INT_MAX - 1);

		aux0 = high_resolution_clock::now();
		aux->encontrar(INT_MAX - 1);
		aux1 = high_resolution_clock::now();
		t_srch0 = aux1 - aux0;
		sum += t_srch0.count() * 1000;
		aux->limpiar();
	}

	return sum / 10;
}

int main()
{
	vector<int> data;

	//cargando datos a memoria
	ifstream myfile;
	myfile.open("dataset.txt");

	ofstream binary_t("AVL_srch.txt", ofstream::out);
	int N = 50;

	int valor;

	while (myfile >> valor)
	{
		data.push_back(valor);
	}

	//BST:
	{AVL<int>* tree = new AVL<int>;		//se separa memmoria para un objeto de tipo "BST"
	binary_t << "N,Srch0,SrchM,Srch1" << endl;

	while (N < 50000)
	{
		//En el mejor caso para la inserción, el arbol en cuestion ya estara balanceado:
		for (int i = 0; i < N - 1; i++)
		{
			tree->insertar(data[i]);		//se insertan los elementos normalmente
		}

		//se procede a medir los ticks, tanto al inicio como al final de la insercion
		Ins0_ini = high_resolution_clock::now();
		tree->insertar(INT_MAX - 1);		            //estando ya el arbol balanceado, se inserta el elemento
		Ins0_end = high_resolution_clock::now();
		t_ins0 = Ins0_end - Ins0_ini;


		Srch0_ini = high_resolution_clock::now();
		tree->encontrar(INT_MAX - 1);		//se busca el ultimo elemento insertado, estando el arbol balanceado
		Srch0_end = high_resolution_clock::now();
		t_srch0 = Srch0_end - Srch0_ini;
;
		t_srchM = mean_search_bst(N);			//retorna lo mismo que mean_insert, pero en vez de insertar, busca el ultimo elemento

		//Para el peor caso, se ordenarán los valores, de tal manera que todos se vayan hacia la derecha del arbol, 
		//en teoria el arbol tendria la misma eficiencia que una lista de nodos, que siempre tiene el puntero empezando en el inicio
		for (int I = 0; I < N; I++)
		{
			tree->insertar(I + 1);
		}

		Ins1_ini = high_resolution_clock::now();
		tree->insertar(INT_MAX - 1);
		Ins1_end = high_resolution_clock::now();
		t_ins1 = Ins1_end - Ins1_ini;

		Srch1_ini = high_resolution_clock::now();
		tree->encontrar(INT_MAX - 1);
		Srch1_end = high_resolution_clock::now();
		t_srch1 = Srch1_end - Srch1_ini;
		
		binary_t << N << "," << t_srch0.count() * 1000 << "," << t_srchM * N/2 << "," << t_srch1.count() * 1000 * N << endl;
		N += 50;
		tree->limpiar();
		cout << "N: " << N << endl;
	}
	}
	data.clear();
	return 0;
}