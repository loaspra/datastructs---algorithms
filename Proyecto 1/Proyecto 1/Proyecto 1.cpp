#include <fstream>
#include "pila.h"
#include "cola.h"
#include "lista.h"	//falta lista_enlazada
#include <chrono>
#include <vector>
#include <string>

using namespace std;


int main()
{
	//inicializando 
	vector<int> data(0,0);


	//cargando datos a memoria
	ifstream myfile;
	ofstream carga_datos("test.txt", ofstream::out);
	myfile.open("dataset.txt");

	ofstream Alista_file("Alista_t.txt", ofstream::out);
	ofstream Nlista_file("Nlista_t.txt", ofstream::out);

	ofstream Acola_file("Acola_t.txt", ofstream::out);
	ofstream Ncola_file("Ncola_t.txt", ofstream::out);

	ofstream APila_file("Apila_t.txt", ofstream::out);
	ofstream NPila_file("Npila_t.txt", ofstream::out);

	int indice = 0;
	int valor;

	while (myfile >> valor)
	{
		data.push_back(valor);
		indice++;
	}
	
	
	//Insercion maxima
	int N = 50;
	
	//--------------------fin, lectura-------------------
	carga_datos << "Muestras" << "," << "ListaArreglo" << "," << "ListaEnlazada" << "," << "PilaArreglo" << "," << "PilaNodos" << "," << "ColaArreglo" << "," << "ColaNodos" << endl;
	//----------------------Empieza------------------------
	
	while (N <= data.size())
	{
		APila<int>* a_pila = new APila<int>(N);
		LPila<int>* l_pila = new LPila<int>;

		ACola<int>* a_cola = new ACola<int>(N);
		LCola<int>* l_cola = new LCola<int>;

		ListaArreglo<int>* a_lista = new ListaArreglo<int>(N);
		ListaEnlazada<int>* l_lista = new ListaEnlazada<int>;

		//Lista|arreglo

		auto start_lista = chrono::high_resolution_clock::now();
		for (int i = 0; i < N; i++)
		{
			a_lista->agregar(data[i]);
		}
		auto finish_lista = chrono::high_resolution_clock::now();

		chrono::duration<double> t_alista = finish_lista - start_lista;


		//ListaEnlazada
		auto start_Elista = chrono::high_resolution_clock::now();
		for (int i = 0; i < N; i++)
		{
			l_lista->agregar(data[i]);
		}
		auto finish_Elista = chrono::high_resolution_clock::now();

		chrono::duration<double> t_Elista = finish_Elista - start_Elista;

		//pila|arreglo

		auto start = chrono::high_resolution_clock::now();
		for (int i = 0; i < N; i++)
		{
			a_pila->apilar(data[i]);
		}
		auto finish = chrono::high_resolution_clock::now();

		chrono::duration<double> t_apila = finish - start;

		//pila|nodos
		auto start_l = chrono::high_resolution_clock::now();
		for (int i = 0; i < N; i++)
		{
			l_pila->apilar(data[i]);
		}
		auto finish_l = chrono::high_resolution_clock::now();

		chrono::duration<double> t_lpila = finish_l - start_l;


		//Colas
		//cola|arreglo
		auto start_ac = chrono::high_resolution_clock::now();
		for (int i = 0; i < N; i++)
		{
			a_cola->encolar(data[i]);
		}
		auto finish_ac = chrono::high_resolution_clock::now();

		chrono::duration<double> t_acola = finish_ac - start_ac;


		//cola|nodos
		auto start_nc = chrono::high_resolution_clock::now();
		for (int i = 0; i < N; i++)
		{
			l_cola->encolar(data[i]);
		}
		auto finish_nc = chrono::high_resolution_clock::now();

		chrono::duration<double> t_ncola = finish_nc - start_nc;


		carga_datos << N << "," << t_alista.count()*1000 << "," << t_Elista.count()*1000 << "," << t_apila.count()*1000 << "," << t_lpila.count()*1000 << "," << t_acola.count()*1000 << "," << t_ncola.count()*1000 << endl;

		N += 50;
	
		delete a_pila;
		delete l_pila;

		delete a_cola;
		delete l_cola;

		delete a_lista;
		delete l_lista;
		cout << "Ini-> N: " << N << endl;
	}
	
	
	N = 50;
	//ListaArreglo
	Alista_file << "Muestras,Insertar0,InsertarM,Insertar1,Buscar0,BuscarM,Buscar1,Eliminar0,EliminarM,Eliminar1,Ordenar0,OrdenarM,Ordenar1" << endl;

	while (N <= data.size()) 
	{	
		ListaArreglo<int>* a_lista = new ListaArreglo<int>(N);
		//Recogiendo datos para el mejor, promedio y peor caso.
		int el_0 = data[0];
		int el_m = data[(N / 2) + 1];
		int el_1 = data[N - 1];

		auto inser_alista_ = chrono::high_resolution_clock::now();
		a_lista->agregar(el_0);
		auto finser_alista_ = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_alista_0 = finser_alista_ - inser_alista_;

		//inicializando
		for (int i = 1; i < N - 1; i++)
		{
			a_lista->agregar(data[i]);
		}
		
		auto inser_alista_M = chrono::high_resolution_clock::now();
		a_lista->agregar(el_m);
		auto finser_alista_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_alista_M = finser_alista_M - inser_alista_M;


		auto inser_alista_f = chrono::high_resolution_clock::now();
		a_lista->agregar(el_1);		//entra a resize
		auto finser_alista_f = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_alista_f = finser_alista_f - inser_alista_f;


		//buscar
		auto ibus_alista_0 = chrono::high_resolution_clock::now();
		a_lista->buscar(el_0);
		auto fbus_alista_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_alista_0 = fbus_alista_0 - ibus_alista_0;


		auto ibus_alista_M = chrono::high_resolution_clock::now();
		a_lista->buscar(data[N/2]);
		auto fbus_alista_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_alista_M = fbus_alista_M - ibus_alista_M;


		auto ibus_alista_1 = chrono::high_resolution_clock::now();
		a_lista->buscar(el_1);
		auto fbus_alista_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_alista_1 = fbus_alista_1 - ibus_alista_1;

		
		//Delete
		auto idel_alista_0 = chrono::high_resolution_clock::now();
		a_lista->eliminar(el_0);
		auto fdel_alista_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_alista_0 = fdel_alista_0 - idel_alista_0;


		auto idel_alista_M = chrono::high_resolution_clock::now();
		a_lista->eliminar(data[N / 2]);
		auto fdel_alista_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_alista_M = fdel_alista_M - idel_alista_M;


		auto idel_alista_1 = chrono::high_resolution_clock::now();
		a_lista->eliminar(el_1);
		auto fdel_alista_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_alista_1 = fdel_alista_1 - idel_alista_1;



		//Sort+++++++
		auto isort_alista_M = chrono::high_resolution_clock::now();
		a_lista->ordenar();
		auto fsort_alista_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_sort_alista_M = fsort_alista_M - isort_alista_M;


		delete a_lista;
		ListaArreglo<int>* b_lista = new ListaArreglo<int>(N);
		for (size_t i = 0; i < N; i++)	//creando una lista ya ordenada
		{
			b_lista->agregar(i + 1);
		}
		auto isort_alista_0 = chrono::high_resolution_clock::now();
		b_lista->ordenar();
		auto fsort_alista_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_sort_alista_0 = fsort_alista_0 - isort_alista_0;


		delete b_lista;
		ListaArreglo<int>* c_lista = new ListaArreglo<int>(N);
		for (size_t i = 0; i < N; i++)	//creando una lista de mayor a menor (peor caso, en teoria)
		{
			c_lista->agregar(N - i);
		}
		auto isort_alista_1 = chrono::high_resolution_clock::now();
		c_lista->ordenar();
		auto fsort_alista_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_sort_alista_1 = fsort_alista_1 - isort_alista_1;


		delete c_lista;
		cout << "ALista-> N: " << N << endl;
		Alista_file << N << "," << m_inserta_alista_0.count()*1000 << "," << m_inserta_alista_M.count()*1000 << "," << m_inserta_alista_f.count()*1000 << "," <<
			m_bus_alista_0.count()*1000 << "," << m_bus_alista_M.count()*1000 << "," << m_bus_alista_1.count()*1000 << "," << m_del_alista_0.count()*1000 << "," << m_del_alista_M.count()*1000 << "," << m_del_alista_1.count()*1000
			<< "," << m_sort_alista_0.count()*1000 << "," << m_sort_alista_M.count()*1000 << "," << m_sort_alista_1.count()*1000 << endl;
		N += 50;
	}
	
	
	Nlista_file << "Muestras,Insertar0,InsertarM,Insertar1,Buscar0,BuscarM,Buscar1,Eliminar0,EliminarM,Eliminar1,Ordenar0,OrdenarM,Ordenar1" << endl;
	
	N = 50; 
	
	//ListaEnlazada
	while (N <= data.size())
	{
		ListaEnlazada<int>* l_lista = new ListaEnlazada<int>;
		//Recogiendo datos para el mejor, promedio y peor caso.
		int el_0 = data[0];
		int el_m = data[(N / 2) + 1];
		int el_1 = data[N - 1];

		auto inser_llista_ = chrono::high_resolution_clock::now();
		l_lista->agregar(el_0);
		auto finser_llista_ = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_llista_0 = finser_llista_ - inser_llista_;

		//inicializando
		for (int i = 1; i < N - 2; i++)
		{
			l_lista->agregar(data[i]);
		}

		auto inser_llista_M = chrono::high_resolution_clock::now();
		l_lista->agregar(el_m);
		auto finser_llista_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_llista_M = finser_llista_M - inser_llista_M;

		auto inser_llista_f = chrono::high_resolution_clock::now();
		l_lista->agregar(el_1);
		auto finser_llista_f = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_llista_f = finser_llista_f - inser_llista_f;

		//buscar
		auto ibus_llista_0 = chrono::high_resolution_clock::now();
		l_lista->buscar(el_0);
		auto fbus_llista_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_llista_0 = fbus_llista_0 - ibus_llista_0;


		auto ibus_llista_M = chrono::high_resolution_clock::now();
		l_lista->buscar(data[N / 2]);
		auto fbus_llista_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_llista_M = fbus_llista_M - ibus_llista_M;
		
		auto ibus_llista_1 = chrono::high_resolution_clock::now();
		l_lista->buscar(el_1);
		auto fbus_llista_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_llista_1 = fbus_llista_1 - ibus_llista_1;


		//Delete
		auto idel_llista_0 = chrono::high_resolution_clock::now();
		l_lista->eliminar(el_0);
		auto fdel_llista_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_llista_0 = fdel_llista_0 - idel_llista_0;


		auto idel_llista_M = chrono::high_resolution_clock::now();
		l_lista->eliminar(data[N / 2]);
		auto fdel_llista_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_llista_M = fdel_llista_M - idel_llista_M;


		auto idel_llista_1 = chrono::high_resolution_clock::now();
		l_lista->eliminar(el_1);
		auto fdel_llista_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_llista_1 = fdel_llista_1 - idel_llista_1;

		
		//Sort+
		delete l_lista;

		ListaArreglo<int>* c_lista = new ListaArreglo<int>(N);
		for (size_t i = 0; i < N; i++)	//creando una lista ya ordenada
		{
			c_lista->agregar(i + 1);
		}
		auto isort_llista_0 = chrono::high_resolution_clock::now();
		c_lista->ordenar();
		auto fsort_llista_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_sort_llista_0 = fsort_llista_0 - isort_llista_0;


		delete c_lista;
		ListaArreglo<int>* k_lista = new ListaArreglo<int>(N);
		for (size_t i = 0; i < N; i++)	//creando una lista de mayor a menor (peor caso, en teoria)
		{
			k_lista->agregar(N - i);
		}
		auto isort_llista_1 = chrono::high_resolution_clock::now();
		k_lista->ordenar();
		auto fsort_llista_1 = chrono::high_resolution_clock::now();
		delete k_lista;
		chrono::duration<double> m_sort_llista_1 = fsort_llista_1 - isort_llista_1;

		//cout << "NLista-> N: " << N << endl;
		Nlista_file << N << "," << m_inserta_llista_0.count()*1000 << "," << m_inserta_llista_M.count()*1000 << "," << m_inserta_llista_f.count()*1000 << "," <<
			m_bus_llista_0.count()*1000 << "," << m_bus_llista_M.count()*1000 << "," << m_bus_llista_1.count()*1000 << "," << m_del_llista_0.count()*1000 << "," << m_del_llista_M.count()*1000 << "," << m_del_llista_1.count()*1000
			<<"," << m_sort_llista_0.count()*1000 << "," << (m_sort_llista_0.count() + m_sort_llista_1.count()) * 500 << "," << m_sort_llista_1.count() * 1000 <<endl;
		N += 50;
	}
	
	
	Ncola_file << "Muestras,Insertar0,InsertarM,Insertar1,Buscar0,BuscarM,Buscar1,Eliminar0,EliminarM,Eliminar1" << endl;
	

	//ColaNodos
	N = 50;
	while (N <= data.size())
	{
		LCola<int>* l_cola = new LCola<int>;
		//Recogiendo datos para el mejor, promedio y peor caso.
		int el_0 = data[0];
		int el_m = data[(N / 2) + 1];
		int el_1 = data[N - 1];

		auto inser_lcola_ = chrono::high_resolution_clock::now();
		l_cola->encolar(el_0);
		auto finser_lcola_ = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_lcola_0 = finser_lcola_ - inser_lcola_;


		//inicializando
		for (int i = 1; i < N - 2; i++)
		{
			l_cola->encolar(data[i]);
		}

		auto inser_lcola_M = chrono::high_resolution_clock::now();
		l_cola->encolar(el_m);
		auto finser_lcola_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_lcola_M = finser_lcola_M - inser_lcola_M;


		auto inser_lcola_f = chrono::high_resolution_clock::now();
		l_cola->encolar(el_1);
		auto finser_lcola_f = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_lcola_f = finser_lcola_f - inser_lcola_f;
;

		//buscar
		auto ibus_lcola_0 = chrono::high_resolution_clock::now();
		l_cola->buscar(el_0);
		auto fbus_lcola_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_lcola_0 = fbus_lcola_0 - ibus_lcola_0;



		auto ibus_lcola_M = chrono::high_resolution_clock::now();
		l_cola->buscar(data[N / 2]);
		auto fbus_lcola_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_lcola_M = fbus_lcola_M - ibus_lcola_M;


		auto ibus_lcola_1 = chrono::high_resolution_clock::now();
		l_cola->buscar(el_1);
		auto fbus_lcola_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_lcola_1 = fbus_lcola_1 - ibus_lcola_1;


		//Delete
		auto idel_lcola_0 = chrono::high_resolution_clock::now();
		l_cola->desencolar();
		auto fdel_lcola_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_lcola_0 = fdel_lcola_0 - idel_lcola_0;


		auto idel_lcola_M = chrono::high_resolution_clock::now();
		l_cola->eliminar(data[N / 2]);
		auto fdel_lcola_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_lcola_M = fdel_lcola_M - idel_lcola_M;


		auto idel_lcola_1 = chrono::high_resolution_clock::now();
		l_cola->eliminar(el_1);
		auto fdel_lcola_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_lcola_1 = fdel_lcola_1 - idel_lcola_1;

		
		cout << "NCola-> N: " << N << endl;
		Ncola_file << N << "," << m_inserta_lcola_0.count()*1000 << "," << m_inserta_lcola_M.count()*1000 << "," << m_inserta_lcola_f.count()*1000 << "," <<
			m_bus_lcola_0.count()*1000 << "," << m_bus_lcola_M.count()*1000 << "," << m_bus_lcola_1.count()*1000 << "," << m_del_lcola_0.count()*1000 << "," << m_del_lcola_M.count()*1000 << "," << m_del_lcola_1.count()*1000
			<< endl;
		N += 50;
		delete l_cola;
	}
	
	Acola_file << "Muestras,Insertar0,InsertarM,Insertar1,Buscar0,BuscarM,Buscar1,Eliminar0,EliminarM,Eliminar1" << endl;
	//ColaArreglo
	
	N = 50;
	while (N <= data.size())
	{
		ACola<int>* a_cola = new ACola<int>(N);
		//Recogiendo datos para el mejor, promedio y peor caso.
		int el_0 = data[0];
		int el_m = data[(N / 2) + 1];
		int el_1 = data[N - 1];

		auto inser_lcola_ = chrono::high_resolution_clock::now();
		a_cola->encolar(el_0);
		auto finser_lcola_ = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_lcola_0 = finser_lcola_ - inser_lcola_;


		//inicializando
		for (int i = 1; i < N - 1; i++)
		{
			a_cola->encolar(data[i]);
		}

		auto inser_lcola_M = chrono::high_resolution_clock::now();
		a_cola->encolar(el_m);
		auto finser_lcola_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_lcola_M = finser_lcola_M - inser_lcola_M;

		auto inser_lcola_f = chrono::high_resolution_clock::now();
		a_cola->encolar(el_1);
		auto finser_lcola_f = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_lcola_f = finser_lcola_f - inser_lcola_f;

		//buscar
		auto ibus_lcola_0 = chrono::high_resolution_clock::now();
		a_cola->buscar(el_0);
		auto fbus_lcola_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_lcola_0 = fbus_lcola_0 - ibus_lcola_0;

		auto ibus_lcola_M = chrono::high_resolution_clock::now();
		a_cola->buscar(data[N / 2]);
		auto fbus_lcola_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_lcola_M = fbus_lcola_M - ibus_lcola_M;

		auto ibus_lcola_1 = chrono::high_resolution_clock::now();
		a_cola->buscar(el_1);
		auto fbus_lcola_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_lcola_1 = fbus_lcola_1 - ibus_lcola_1;

		//Delete
		auto idel_lcola_0 = chrono::high_resolution_clock::now();
		a_cola->desencolar();
		auto fdel_lcola_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_lcola_0 = fdel_lcola_0 - idel_lcola_0;

		auto idel_lcola_M = chrono::high_resolution_clock::now();
		a_cola->eliminar(data[N / 2]);
		auto fdel_lcola_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_lcola_M = fdel_lcola_M - idel_lcola_M;

		auto idel_lcola_1 = chrono::high_resolution_clock::now();
		a_cola->eliminar(el_1);
		auto fdel_lcola_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_lcola_1 = fdel_lcola_1 - idel_lcola_1;

		cout << "ACola-> N: " << N << endl;
		Acola_file << N << "," << m_inserta_lcola_0.count()*1000 << "," << m_inserta_lcola_M.count()*1000 << "," << m_inserta_lcola_f.count()*1000 << "," <<
			m_bus_lcola_0.count()*1000 << "," << m_bus_lcola_M.count()*1000 << "," << m_bus_lcola_1.count()*1000 << "," << m_del_lcola_0.count()*1000 << "," << m_del_lcola_M.count()*1000 << "," << m_del_lcola_1.count()*1000
			<< endl;
		N += 50;
		delete a_cola;
	}
	
	APila_file << "Muestras,Insertar0,InsertarM,Insertar1,Buscar0,BuscarM,Buscar1,Eliminar0,EliminarM,Eliminar1" << endl;
	//PilaArreglo
	N = 50;
	while (N <= data.size())
	{
		APila<int>* a_Pila = new APila<int>(N);
		//Recogiendo datos para el mejor, promedio y peor caso.
		int el_0 = data[0];
		int el_m = data[(N / 2) + 1];
		int el_1 = data[N - 1];

		auto inser_lPila_ = chrono::high_resolution_clock::now();
		a_Pila->apilar(el_0);
		auto finser_lPila_ = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_lPila_0 = finser_lPila_ - inser_lPila_;

		//inicializando
		for (int i = 1; i < N - 1; i++)
		{
			a_Pila->apilar(data[i]);
		}

		auto inser_lPila_M = chrono::high_resolution_clock::now();
		a_Pila->apilar(el_m);
		auto finser_lPila_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_lPila_M = finser_lPila_M - inser_lPila_M;

		auto inser_lPila_f = chrono::high_resolution_clock::now();
		a_Pila->apilar(el_1);
		auto finser_lPila_f = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_lPila_f = finser_lPila_f - inser_lPila_f;

		//buscar
		auto ibus_lPila_0 = chrono::high_resolution_clock::now();
		a_Pila->buscar(el_0);
		auto fbus_lPila_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_lPila_0 = fbus_lPila_0 - ibus_lPila_0;

		auto ibus_lPila_M = chrono::high_resolution_clock::now();
		a_Pila->buscar(data[N / 2]);
		auto fbus_lPila_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_lPila_M = fbus_lPila_M - ibus_lPila_M;

		auto ibus_lPila_1 = chrono::high_resolution_clock::now();
		a_Pila->buscar(el_1);
		auto fbus_lPila_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_lPila_1 = fbus_lPila_1 - ibus_lPila_1;

		//Delete
		auto idel_lPila_0 = chrono::high_resolution_clock::now();
		a_Pila->pop();
		auto fdel_lPila_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_lPila_0 = fdel_lPila_0 - idel_lPila_0;

		auto idel_lPila_M = chrono::high_resolution_clock::now();
		a_Pila->eliminar(data[N / 2]);
		auto fdel_lPila_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_lPila_M = fdel_lPila_M - idel_lPila_M;

		auto idel_lPila_1 = chrono::high_resolution_clock::now();
		a_Pila->eliminar(el_1);
		auto fdel_lPila_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_lPila_1 = fdel_lPila_1 - idel_lPila_1;

		cout <<"APila-> N: " << N << endl;
		APila_file << N << "," << m_inserta_lPila_0.count()*1000 << "," << m_inserta_lPila_M.count()*1000 << "," << m_inserta_lPila_f.count()*1000 << "," <<
			m_bus_lPila_0.count()*1000 << "," << m_bus_lPila_M.count()*1000 << "," << m_bus_lPila_1.count()*1000 << "," << m_del_lPila_0.count()*1000 << "," << m_del_lPila_M.count()*1000 << "," << m_del_lPila_1.count()*1000
			<< endl;
		N += 50;
		delete a_Pila;
	}

	NPila_file << "Muestras,Insertar0,InsertarM,Insertar1,Buscar0,BuscarM,Buscar1,Eliminar0,EliminarM,Eliminar1" << endl;
	//PilaNodos
	N = 50;
	while (N <= data.size())
	{
		LPila<int>* l_pila = new LPila<int>;
		//Recogiendo datos para el mejor, promedio y peor caso.
		int el_0 = data[0];
		int el_m = data[(N / 2) + 1];
		int el_1 = data[N - 1];

		auto inser_LPila_ = chrono::high_resolution_clock::now();
		l_pila->apilar(el_0);
		auto finser_LPila_ = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_LPila_0 = finser_LPila_ - inser_LPila_;

		//inicializando
		for (int i = 1; i < N - 2; i++)
		{
			l_pila->apilar(data[i]);
		}

		auto inser_LPila_M = chrono::high_resolution_clock::now();
		l_pila->apilar(el_m);
		auto finser_LPila_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_LPila_M = finser_LPila_M - inser_LPila_M;


		auto inser_LPila_f = chrono::high_resolution_clock::now();
		l_pila->apilar(el_1);
		auto finser_LPila_f = chrono::high_resolution_clock::now();
		chrono::duration<double> m_inserta_LPila_f = finser_LPila_f - inser_LPila_f;


		//buscar
		auto ibus_LPila_0 = chrono::high_resolution_clock::now();
		l_pila->buscar(el_0);
		auto fbus_LPila_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_LPila_0 = fbus_LPila_0 - ibus_LPila_0;


		auto ibus_LPila_M = chrono::high_resolution_clock::now();
		l_pila->buscar(data[N / 2]);
		auto fbus_LPila_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_LPila_M = fbus_LPila_M - ibus_LPila_M;


		auto ibus_LPila_1 = chrono::high_resolution_clock::now();
		l_pila->buscar(el_1);
		auto fbus_LPila_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_bus_LPila_1 = fbus_LPila_1 - ibus_LPila_1;



		//Delete
		auto idel_LPila_0 = chrono::high_resolution_clock::now();
		l_pila->pop();
		auto fdel_LPila_0 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_LPila_0 = fdel_LPila_0 - idel_LPila_0;

		auto idel_LPila_M = chrono::high_resolution_clock::now();
		l_pila->eliminar(data[N / 2]);
		auto fdel_LPila_M = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_LPila_M = fdel_LPila_M - idel_LPila_M;

		auto idel_LPila_1 = chrono::high_resolution_clock::now();
		l_pila->eliminar(el_1);
		auto fdel_LPila_1 = chrono::high_resolution_clock::now();
		chrono::duration<double> m_del_LPila_1 = fdel_LPila_1 - idel_LPila_1;

		cout << "NPIla-> N: " << N << endl;
		NPila_file << N << "," << m_inserta_LPila_0.count()*1000 << "," << m_inserta_LPila_M.count()*1000 << "," << m_inserta_LPila_f.count()*1000 << "," <<
			m_bus_LPila_0.count()*1000 << "," << m_bus_LPila_M.count()*1000 << "," << m_bus_LPila_1.count()*1000 << "," << m_del_LPila_0.count()*1000 << "," << m_del_LPila_M.count()*1000 << "," << m_del_LPila_1.count()*1000
			<< endl;
		N += 50;
		delete l_pila;
	}
	
	

	Alista_file.close();
	Nlista_file.close();
	
	Acola_file.close();
	Ncola_file.close();

	APila_file.close();
	NPila_file.close();
	return 0;
}