#include "TSP.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Timer.h"

using namespace std;

TSP::TSP()
{
    matrixOfPerm = 0;
    int sizeOfInstance;
}

TSP::~TSP()
{
    //dtor
}

int** TSP::loadOneInstance()
{
    string name = "";
    string instance = "";
    sizeOfInstance = 0;
    int** matrixOfCost = 0;
    cout << "Wprowadz nazwe instancji: 'instancja'.txt" << endl;
    cin >> name;

    instance = name;
    ifstream data(instance.c_str());
    if(!data)
    {
        cout << "Nie mozna otworzyc pliku!!!" << endl << endl;
        return 0;
    }

    data >> instance >> sizeOfInstance;

	matrixOfCost = new int *[sizeOfInstance];         // stworzenie tablicy wskaznikow

	for (int i = 0; i < sizeOfInstance; i++)
    {
        matrixOfCost[i] = new int[sizeOfInstance];    //stworzenie macierzy dwuwymiaorwej
    }

	for (int i = 0; i < sizeOfInstance; i++)         //wypelnianie macierzy wartosciami wejsciowymi z wczytanego pliku
	{
		for (int j = 0; j < sizeOfInstance; j++)
        {
            data >> matrixOfCost[i][j];
        }
	}
	cout << endl;
    data.close();

	cout << "Instancja zostala wczytana pomyslnie!!!" << endl << endl;

	for (int i = 0; i < sizeOfInstance; i++)
    {
        for (int j = 0; j < sizeOfInstance; j++)
        {
            cout << matrixOfCost[i][j] << "  ";          //wypisywanie kolejnych wartoœci macierzy
        }
        cout << endl;
    }
    cout << endl;

    return matrixOfCost;
}
/*
    int a[sizeOfInstance];
    for (int i = 0; i < sizeOfInstance ; i++){
        a[i] = i;   //tworzenie tablicy z numerami wszystkich wierzchołków
    }

    matrixOfPerm = heapPermutation(a[], sizeOfInstance, matrixOfPerm);
*/


void TSP::loadAllInstance()
{
    string tab[] = {"10","11" ,"12" ,"13" , "14" ,"15" ,"16" ,"17", "18"};
    for(int i =0; i<9; i++)
    {
    instance = "data"+ tab[i] +".txt";
    ifstream data(instance.c_str());
    if(!data)
    {
        cout << "Blad przy otwieraniu pliku!!!" << endl << endl;
        return;
    }

    data >> instance >> sizeOfInstance;

	matrixOfCost = new int *[sizeOfInstance];         // utworzenie tablicy wskaznikow

	for (int i = 0; i < sizeOfInstance; i++)
    {
        matrixOfCost[i] = new int[sizeOfInstance];    //utworzenie macierzy dwuwymiaorwej
    }

	for (int i = 0; i < sizeOfInstance; i++)         //wypelnienie macierzy wartosciami wejsciowymi
	{
		for (int j = 0; j < sizeOfInstance; j++)
        {
            data >> matrixOfCost[i][j];
        }
	}
	cout << endl;
    data.close();

	cout << "Instancja wczytana pomyslnie!!!" << endl << endl;

	for (int i = 0; i < sizeOfInstance; i++)
    {
        for (int j = 0; j < sizeOfInstance; j++)
        {
            cout << matrixOfCost[i][j] << "  ";          //wypisywanie kolejnych wartoœci w macierzy
        }
        cout << endl;
    }
 //    aimFunction();
    }
}




int silnia(unsigned int n) // wersja rekurencyjna
{
   return (n < 1) ? 1 : n * silnia(n-1);
}
// Generating permutation using Heap Algorithm
void TSP::heapPermutation(int a[], int sizeOfInstance, int**& matrixOfPerm)
{

    for (int i = 0; i < sizeOfInstance; i++){

        // if sizeOfInstance becomes 1 then prints the obtained
        // permutation
        if (sizeOfInstance == 1)
        {
            for(int j = 0; j < sizeOfInstance ; j++ ){
                matrixOfPerm[i][j] = a[j];  //wstawianie permutacji do macierzy
        }
        }
        else for (int i=0; i<sizeOfInstance; i++)
        {
            TSP::heapPermutation(a,sizeOfInstance-1, matrixOfPerm);

            // if sizeOfInstance is odd, swap first and last
            // element
            if (sizeOfInstance%2==1)
            swap(a[0], a[sizeOfInstance-1]);

            // If sizeOfInstance is even, swap ith and last
            // element
            else
            swap(a[i], a[sizeOfInstance-1]);
        }
    }
    return;
}

int TSP::travllingSalesmanProblem(int**& matrixOfCost, int**& matrixOfPerm, int sizeOfInstance )
{
    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;

    for(int j = 0; j < silnia(sizeOfInstance)  ; j++){


        // store current Path weight(cost)
        int current_pathweight = 0;

        // compute current path weight
        for (int i = 0; i < sizeOfInstance - 1; i++) {
            current_pathweight += matrixOfCost[matrixOfPerm[j][i]][matrixOfPerm[j][i+1]] ;
        }
        current_pathweight += matrixOfCost[matrixOfPerm[j][sizeOfInstance-1]][matrixOfPerm[j][0]];

        // update minimum
        min_path = min(min_path, current_pathweight);

    }
    return min_path;
}

