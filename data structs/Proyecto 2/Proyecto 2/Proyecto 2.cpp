// Proyecto 2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include "BinaryTree.h"
#include "AVL.h"
#include "GrafoList.h"
#include "GrafoMatrix.h"
#include <random>

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

double mean_del_bst(int N)
{
	aux->limpiar();
	sum = 0;
	for (size_t i = 0; i < 10; i++)
	{
		l = distribution(generator);

		for (size_t i = 0; i < N - 1; i++)
		{
			l = distribution(generator);
			aux->insertar(l);
		}
		l = INT_MAX - 1;
		aux->insertar(l);
		aux0 = high_resolution_clock::now();
		aux->remover(l);
		aux1 = high_resolution_clock::now();
		t_del0 = aux1 - aux0;
		sum += t_del0.count() * 1000;
		aux->limpiar();
	}
	return sum / 10;
}

double mean_insert_bst(int N)
{
	aux->limpiar();
	sum = 0;
	for (size_t i = 0; i < 10; i++)
	{
		l = distribution(generator);

		for (size_t i = 0; i < N - 1; i++)
		{
			l = distribution(generator);
			aux->insertar(l);
		}
		l = INT_MAX - 1;

		aux0 = high_resolution_clock::now();
		aux->insertar(l);
		aux1 = high_resolution_clock::now();
		t_ins0 = aux1 - aux0;
		sum += t_ins0.count() * 1000;
		aux->limpiar();
	}
	return sum / 10;
}

double mean_search_avl(int N)
{
	sum = 0;
	aucs->limpiar();
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t i = 0; i < N - 1; i++)
		{
			l = distribution(generator);
			aucs->insertar(l);
		}
		aucs->insertar(INT_MAX - 1);

		aux0 = high_resolution_clock::now();
		aucs->encontrar(INT_MAX - 1);
		aux1 = high_resolution_clock::now();
		t_srch0 = aux1 - aux0;
		sum += t_srch0.count() * 1000;
		aucs->limpiar();
	}

	return sum / 10;
}

double mean_del_avl(int N)
{
	aucs->limpiar();
	sum = 0;
	for (size_t i = 0; i < 10; i++)
	{
		l = distribution(generator);

		for (size_t i = 0; i < N - 1; i++)
		{
			l = distribution(generator);
			aucs->insertar(l);
		}
		l = INT_MAX - 1;
		aucs->insertar(l);
		aux0 = high_resolution_clock::now();
		aucs->remover(l);
		aux1 = high_resolution_clock::now();
		t_del0 = aux1 - aux0;
		sum += t_del0.count() * 1000;
		aucs->limpiar();
	}
	return sum / 10;
}

double mean_insert_avl(int N)
{
	aucs->limpiar();
	sum = 0;
	for (size_t i = 0; i < 10; i++)
	{
		l = distribution(generator);

		for (size_t i = 0; i < N - 1; i++)
		{
			l = distribution(generator);
			aucs->insertar(l);
		}
		l = INT_MAX - 1;

		aux0 = high_resolution_clock::now();
		aucs->insertar(l);
		aux1 = high_resolution_clock::now();
		t_ins0 = aux1 - aux0;
		sum += t_ins0.count() * 1000;
		aucs->limpiar();
	}
	return sum / 10;
}

int BST_AVL()
{
	vector<int> data;

	//cargando datos a memoria
	ifstream myfile;
	myfile.open("dataset.txt");

	ofstream AVL_t("AVL_t.txt", ofstream::out);
	ofstream binary_t("binary_t.txt", ofstream::out);
	int N = 50;

	int valor;

	while (myfile >> valor)
	{
		data.push_back(valor);
	}
	
	//BST:
	{BST<int>* tree = new BST<int>;		//se separa memmoria para un objeto de tipo "BST"
	binary_t << "N,Ins0,InsM,Ins1,Del0,DelM,Del1,Srch0,SrchM,Srch1" << endl;

	while (N < 50000)
	{
		//En el mejor caso para la inserción, el arbol en cuestion ya estara balanceado:
		for (int i = 0; i < N - 1; i++)
		{
			tree->insertar(data[i]);		//se insertan los elementos normalmente
		}
		//se balancea el BST:
		tree->balancear();

		//se procede a medir los ticks, tanto al inicio como al final de la insercion
		Ins0_ini = high_resolution_clock::now();
		tree->insertar(INT_MAX - 1);		            //estando ya el arbol balanceado, se inserta el elemento
		Ins0_end = high_resolution_clock::now();
		t_ins0 = Ins0_end - Ins0_ini;

		Srch0_ini = high_resolution_clock::now();
		tree->encontrar(INT_MAX - 1);		//se busca el ultimo elemento insertado, estando el arbol balanceado
		Srch0_end = high_resolution_clock::now();
		t_srch0 = Srch0_end - Srch0_ini;

		Del0_ini = high_resolution_clock::now();
		tree->remover(INT_MAX - 1);		                //se elimina el ultimo elemento insertado, estando el arbol balanceado
		Del0_end = high_resolution_clock::now();
		t_del0 = Del0_end - Del0_ini;
		tree->limpiar();

		//Para el caso promedio, se hara un promedio de varios casos con el dataset crudo, es decir
		t_insM = mean_insert_bst(N);		//esta funcion retornara un promedio de N^2 casos con datos tomados aleatoriamente del dataset aleatorio
		t_srchM = mean_search_bst(N);			//retorna lo mismo que mean_insert, pero en vez de insertar, busca el ultimo elemento
		t_delM = mean_del_bst(N);			//retorna el promedio de 10 casos donde se elimina el ultimo valor insertado

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

		Del1_ini = high_resolution_clock::now();
		tree->remover(INT_MAX - 1);
		Del1_end = high_resolution_clock::now();
		t_del1 = Del1_end - Del1_ini;
		binary_t << N << "," << t_ins0.count() * 1000 << "," << t_insM << "," << t_ins1.count() * 1000 << "," << t_del0.count() * 1000 << "," << t_delM <<
			"," << t_del1.count() * 1000 << "," << t_srch0.count() * 1000 << "," << t_srchM << "," << t_srch1.count() * 1000 << endl;
		N += 50;
		tree->limpiar();
		cout << "N: " << N << endl;
	}
	}
	
	//------------------AVL--------------------
	{
		N = 50;

		AVL<int>* avl = new AVL<int>;		//se separa memmoria para un objeto de tipo "BST"
		AVL_t << "N,Ins0,InsM,Ins1,Del0,DelM,Del1,Srch0,SrchM,Srch1" << endl;

		while (N < 50000)
		{
			for (int i = 0; i < N - 1; i++)	//En el mejor caso para la inserción, el arbol en cuestion ya estara balanceado :
			{
				avl->insertar(data[i]);		//se insertan los elementos normalmente
			}

			Ins0_ini = high_resolution_clock::now(); //se procede a medir los ticks, tanto al inicio como al final de la insercion
			avl->insertar(INT_MAX - 1);		            //estando ya el arbol balanceado, se inserta el elemento
			Ins0_end = high_resolution_clock::now();
			t_ins0 = Ins0_end - Ins0_ini;


			Srch0_ini = high_resolution_clock::now();
			avl->encontrar(INT_MAX - 1);		//se busca el ultimo elemento insertado, estando el arbol balanceado
			Srch0_end = high_resolution_clock::now();
			t_srch0 = Srch0_end - Srch0_ini;

			Del0_ini = high_resolution_clock::now();
			avl->remover(INT_MAX - 1);		                //se elimina el ultimo elemento insertado, estando el arbol balanceado
			Del0_end = high_resolution_clock::now();
			t_del0 = Del0_end - Del0_ini;
			avl->limpiar();

			//Para el caso promedio, se hara un promedio de varios casos con el dataset crudo, es decir
			t_insM = mean_insert_avl(N);		//esta funcion retornara un promedio de N^2 casos con datos tomados aleatoriamente del dataset aleatorio
			t_srchM = mean_search_avl(N);			//retorna lo mismo que mean_insert, pero en vez de insertar, busca el ultimo elemento
			t_delM = mean_del_avl(N);			//retorna el promedio de 10 casos donde se elimina el ultimo valor insertado

			//Para el peor caso, se ordenarán los valores, de tal manera que todos se vayan hacia la derecha del arbol, 
			//en teoria el arbol tendria la misma eficiencia que una lista de nodos, que siempre tiene el puntero empezando en el inicio
			for (int I = 0; I < N; I++)
			{
				avl->insertar(I + 1);
			}

			Ins1_ini = high_resolution_clock::now();
			avl->insertar(INT_MAX - 1);
			Ins1_end = high_resolution_clock::now();
			t_ins1 = Ins1_end - Ins1_ini;

			Srch1_ini = high_resolution_clock::now();
			avl->encontrar(INT_MAX - 1);
			Srch1_end = high_resolution_clock::now();
			t_srch1 = Srch1_end - Srch1_ini;

			Del1_ini = high_resolution_clock::now();
			avl->remover(INT_MAX - 1);
			Del1_end = high_resolution_clock::now();
			t_del1 = Del1_end - Del1_ini;
			AVL_t << N << "," << t_ins0.count() * 1000 << "," << t_insM << "," << t_ins1.count() * 1000 << "," << t_del0.count() * 1000 << "," << t_delM <<
				"," << t_del1.count() * 1000 << "," << t_srch0.count() * 1000 << "," << t_srchM << "," << t_srch1.count() * 1000 << endl;
			N += 50;
			avl->limpiar();
			cout << "N: " << N << endl;
		}}
	data.clear();
	return 0;
}

int grafos_r()
{
	steady_clock::time_point grafo_ini, grafo_end;
	duration<double> t_grafoM, t_grafoL, t_grafoM_1, t_grafoL_1, t_grafoM_2, t_grafoL_2, t_grafoM_3, t_grafoL_3;

	//Grafos-----------------------------------
	ofstream graf("Graf_t.txt", ofstream::out);

	ifstream dg;
	dg.open("gra.txt");
	int N = 50;
	double a, b;
	vector<int> item1, item2;
	while (dg >> a >> b)
	{
		item1.push_back(a);
		item2.push_back(b);
	}

	graf << "N,GrafoMatrix,GrafoLista" << endl;
	long int k = 1000;

	GraphM* gmat = new GraphM(25);
	GrafoL* glist = new GrafoL(25);


	GraphM* gmat_1 = new GraphM(100);
	GrafoL* glist_1 = new GrafoL(100);


	GraphM* gmat_2 = new GraphM(200);
	GrafoL* glist_2 = new GrafoL(200);


	GraphM* gmat_3 = new GraphM(375);
	GrafoL* glist_3 = new GrafoL(375);

	while (k < 200000)
	{
		grafo_ini = high_resolution_clock::now();
		for (int i = 0; i < k * 2; i++)
		{
			gmat->setArista(item1[i] % 25, item2[i] % 25, 1);
			glist->setArista(item1[i] % 25, item2[i] % 25, 1);
			gmat_1->setArista(item1[i] % 100, item2[i] % 100, 1);
			glist_1->setArista(item1[i] % 100, item2[i] % 100, 1);
			gmat_2->setArista(item1[i] % 200, item2[i] % 200, 1);
			glist_2->setArista(item1[i] % 200, item2[i] % 200, 1);
			gmat_3->setArista(item1[i] % 375, item2[i] % 375, 1);
			glist_3->setArista(item1[i] % 375, item2[i] % 375, 1);
		}
		grafo_end = high_resolution_clock::now();
		auto caarga = grafo_end - grafo_ini;

		grafo_ini = high_resolution_clock::now();
		gmat->cycle();
		grafo_end = high_resolution_clock::now();
		t_grafoM = grafo_end - grafo_ini;
		grafo_ini = high_resolution_clock::now();
		glist->cycle();
		grafo_end = high_resolution_clock::now();
		t_grafoL = grafo_end - grafo_ini;

		grafo_ini = high_resolution_clock::now();
		gmat_1->cycle();
		grafo_end = high_resolution_clock::now();
		t_grafoM_1 = grafo_end - grafo_ini;
		grafo_ini = high_resolution_clock::now();
		glist_1->cycle();
		grafo_end = high_resolution_clock::now();
		t_grafoL_1 = grafo_end - grafo_ini;

		grafo_ini = high_resolution_clock::now();
		gmat_2->cycle();
		grafo_end = high_resolution_clock::now();
		t_grafoM_2 = grafo_end - grafo_ini;
		grafo_ini = high_resolution_clock::now();
		glist_2->cycle();
		grafo_end = high_resolution_clock::now();
		t_grafoL_2 = grafo_end - grafo_ini;

		grafo_ini = high_resolution_clock::now();
		gmat_3->cycle();
		grafo_end = high_resolution_clock::now();
		t_grafoM_3 = grafo_end - grafo_ini;
		grafo_ini = high_resolution_clock::now();
		glist_3->cycle();
		grafo_end = high_resolution_clock::now();
		t_grafoL_3 = grafo_end - grafo_ini;

		for (int i = k; i < k * 2; i++)
		{
			gmat->eliminarArista(item1[i] % 25, item2[i] % 25);
			glist->eliminarArista(item1[i] % 25, item2[i] % 25);
			gmat_1->eliminarArista(item1[i] % 100, item2[i] % 100);
			glist_1->eliminarArista(item1[i] % 100, item2[i] % 100);
			gmat_2->eliminarArista(item1[i] % 200, item2[i] % 200);
			glist_2->eliminarArista(item1[i] % 200, item2[i] % 200);
			gmat_3->eliminarArista(item1[i] % 375, item2[i] % 375);
			glist_3->eliminarArista(item1[i] % 375, item2[i] % 375);
		}

		cout << "k(g): " << k << endl;
		graf << k << "," << t_grafoM.count() * 1000 << "," << t_grafoM_1.count() * 1000 << "," << t_grafoM_2.count() * 1000 << "," << t_grafoM_3.count() * 1000
			<< "," << t_grafoL.count() * 1000 << "," << t_grafoL_1.count() * 1000 << "," << t_grafoL_2.count() * 1000 << "," << t_grafoL_3.count() * 1000 << "," << caarga.count() * 1000 << endl;
		k += 1000;
	}

	GraphM test_m(375);
	GrafoL test_l(375);

	ofstream corto("G_corto_t.txt", ofstream::out);
	corto << "k,Matriz,Lista" << endl;
	k = 375;

	vector<int> valores_usados;
	uniform_int_distribution<long long unsigned> distribution_g(0, item1.size() - 1);
	while (k < 5000)
	{
		for (size_t i = 0; i < k; i++)
		{
			l = distribution_g(generator);
			test_m.setArista(item1[l] % 375, item2[l] % 375, 1);
			test_l.setArista(item1[l] % 375, item2[l] % 375, 1);
			valores_usados.push_back(l);
		}
		grafo_ini = high_resolution_clock::now();
		test_m.cycle();
		grafo_end = high_resolution_clock::now();
		t_grafoM = grafo_end - grafo_ini;

		grafo_ini = high_resolution_clock::now();
		test_l.cycle();
		grafo_end = high_resolution_clock::now();
		t_grafoL = grafo_end - grafo_ini;

		for (auto e:valores_usados)
		{
			test_m.eliminarArista(item1[e] % 375, item2[e] % 375);
			test_l.eliminarArista(item1[e] % 375, item2[e] % 375);
		}
		valores_usados.clear();
		cout << test_m.aristas() << "++" << endl;
		cout << test_l.e() << "++" << endl;
		corto << k << "," << t_grafoM.count() * 1000 << "," << t_grafoL.count() * 1000 << endl;
		k += 500;
		cout << "k(c): " << k << endl;
	}
	return 0;
}

int main()
{
	//Arboles 
	BST_AVL();

	//Grafos
	grafos_r();
	//-------------------Fin-ejecucion-----------------
	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
