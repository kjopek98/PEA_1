#include "menu.h"
#include <iostream>

using namespace std;

menu::menu()
{
    //ctor
}

menu::~menu()
{
    //dtor
}

int menu::show(){
    int odp;
	cout << "\n1. Wczytaj plik txt z macierza sasiedztwa" << endl;
	cout << "2. Dla zadanej permutacji oblicz funkcje celu" << endl;
	cout << "3. Brute force za pomoca swap" << endl;
	cout << "4. Branch and Bound" <<endl;
	cout << "5. Dynamic Programming" <<endl;
	cout << "6. EXIT" << endl;
	cin >> odp;

	return odp;

}
