#include <iostream>
#include <vector>

using namespace std;

void imprimir(vector<int> vec)
{
	
}


void swap(vector<int> vec, int a, int b)
{
	auto aux = vec[a];
	vec[a] = vec[b];
	vec[b] = aux;
}

void bubble(vector<int> vec)
{
	size_t c = 9;
	while(c > 1)
	{
		for (auto i = 0; i < c; i++)
		{
			if (vec[i] > vec[i + 1])
			{
				swap(vec, i, i + 1);
			}
		}
		c--;
	}
}

void insert(vector<int> vec)
{

}

void blab(vector<int> vec)
{

}

int main()
{
	vector<int> A;
	A.resize(10);
	A = {5, 7, 19, 99 , 2, 1, 3 ,4 ,55, 10};

}
