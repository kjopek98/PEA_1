#include "TSP.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

TSP::TSP()
{
    matrixOfPerm = 0; //
    int sizeOfInstance;
    int index = 0;
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
    int **matrixOfCost = 0;
    cout << "Wprowadz nazwe instancji: 'instancja'.txt" << endl;
    cin >> name;

    instance = name;
    ifstream data(instance.c_str());
    if(!data)
    {
        cout << "Nie mozna otworzyc danego pliku." << endl << endl;
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

	cout << "Instancja zostala wczytana pomyslnie." << endl << endl;

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
    }
}


void TSP::bestPermutation(int *a, int *b, int c, int d, int &min, int size, int **matrix)
{
	int value;
	if (c == d) {
		value = calculateRoad(a , size, matrix);
		if (value < min) {
			for (int i = 0; i <= d; i++)
				b[i] = a[i];
			min = value;
		}

	}
	else
	{
		for (int i = c; i <= d; i++)
		{
			swap(a[c], a[i]);
			bestPermutation(a, b, c + 1, d, min, size,matrix);
			swap(a[c], a[i]);
		}
	}
}


int TSP::calculateRoad(int* permut, int size, int **matrix) {

	int sum = 0;
	int i, j;
	for (int iter = 0; iter < size - 1; iter++) {
		i = permut[iter];
		j = permut[iter + 1];
		//cout << "I= " << i << " j = " << j << endl;
		sum += matrix[i][j];
	}
	sum = sum + matrix[j][permut[0]];
	return sum;
}


