#include<stack>
#include<iostream>

using namespace std;

int main()
{
    int* aux = new int(0);
    int* N = new int(1);
    while (!(*N == 0 && *aux == 0))
    {
        *aux = *N;
        cin >> *N;

        if (*N == 0 && *aux == 0)
        {

            return 0;
        }

        while (true)
        {
            stack<int> tren;
            bool posible = true;
            bool des = false;
            for (int i = 0; i < *N; i++)
            {
                int* x = new int(0);
                cin >> *x;

                if (*x == *N)
                {
                    des = true;
                    tren.push(*x);
                    continue;
                }
                if (des)
                {
                    if (tren.top() - *x > 1)
                    {
                        posible = false;
                    }
                }
                tren.push(*x);
            }
            if (posible)
            {
                cout << "SI" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
            cout << *N << "|";
            cout << *aux << endl;
            delete& tren;
        }
    }
    return 0;
}