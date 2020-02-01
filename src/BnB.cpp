#include "BnB.h"
#include<iostream>
#include "TSP.h"
#include <queue>
#include <vector>

using namespace std;

BnB::BnB(int **m, int s)
{
    matrixOfCost = m;
    sizeOfMatrix = s;
}
//Struktura wezla
struct Node
{
    vector<pair<int, int>> edge;           // krawedzie grafu
    int **minimalMatrix;                   //zminimalizowana macierz  danego wezla
    int cost;                                // koszt wezla (lower bound)
    int vertex;                          //przechowuje wierzcholek, za ktory odpowiada wezel
    int level;                               //przechowuje ilosc wczesniej odwiedzonych miast
};

struct comparision          //funktor sortujacy kolejke priorytetowa
{
    bool operator()(const Node* first, const Node* second)const
    {
        return first->cost < second->cost;
    }
};

// Tworzenie nowego wezla
Node* newNode(int**& baseMatrix, vector<pair<int, int>> const &edge, int level, int k, int m, int sizeofMatrix)
{
    // k - numer rozpatrywanego wierzcholka reprezentujacego miasto
    // m - miasto do ktorego ma isc sciezka
    Node* node = new Node;
    node->edge = edge;

    if(level != 0) //jesli nie jest to wezel laczacy z glownym stworz nowa krawedz
    {
        node->edge.push_back(make_pair(k,m));
    }

    node->minimalMatrix = new int *[sizeofMatrix];
    for(int i = 0; i < sizeofMatrix; i++)
    {
        node->minimalMatrix[i] = new int[sizeofMatrix];
        for(int j = 0; j < sizeofMatrix; j++)
        {
            node->minimalMatrix[i][j] = baseMatrix[i][j];
        }
    }

    if(level != 0) //pomijanie dla pierwszego poziomu
    {
        for(int i = 0; i < sizeofMatrix; i++)    //wypelnienie rzedu i kolumny  wartosciami "-1"
        {
            node->minimalMatrix[k][i] = -1;
            node->minimalMatrix[i][m] = -1;
        }
    }

    node->minimalMatrix[m][0] = -1; //ustawienie  drogi powrotnej do wezla "0" na "-1"
    node->level = level;             //ustawienie liczby odwiedzonych miast
    node->vertex = m;             //ustawienie aktualnie rozpatrywanego wierzcholka

    return node;
}
void minimalization(int**& minimalMatrix, int row[], int column[], int sizeofMatrix)
{
    for(int i = 0; i < sizeofMatrix; i++) //inicjalizacja rzedu macierzy wartosciami "-1"
    {
        row[i] = -1;
        column[i] = -1;
    }

     //odnalezienie wartosci minimalnej w macierzy
    for(int i = 0; i < sizeofMatrix; i++)
    {
        for (int j = 0; j < sizeofMatrix; j++)
        {
            if(minimalMatrix[i][j] < row[i] && minimalMatrix[i][j] > -1)
            {
                row[i] = minimalMatrix[i][j];
            }
            if(minimalMatrix[i][j] < column[j] && minimalMatrix[i][j] > -1)
            {
                column[j] = minimalMatrix[i][j];
            }
        }
    }

    //odejmowanie minimum od kazdej wartosci w macierzy
    for(int i = 0; i < sizeofMatrix; i++)
    {
        for(int j = 0; j < sizeofMatrix; j++)
        {
            if(minimalMatrix[i][j] != -1 && row[i] != -1)
            {
                minimalMatrix[i][j] -= row[i];
            }
            if(minimalMatrix[i][j] != -1 && column[j] != -1)
            {
                minimalMatrix[i][j] -= column[j];
            }
        }
    }
}

int cost(int**& minimalMatrix, int sizeofMatrix)  //liczenie kosztu wynikajacej z minimalizacji macierzy wezla
{
    int cost = 0;

    int row[sizeofMatrix];
    int column[sizeofMatrix];

    minimalization(minimalMatrix, row, column, sizeofMatrix);

    for(int i = 0; i < sizeofMatrix; i++)
    {
        if(row[i] != -1)
        {
            cost += row[i];
        }
        if(column[i] != -1)
        {
            cost += column[i];
        }
    }

    return cost;
}



void BnB::branchAndBound()
{
    priority_queue<Node*, vector<Node*>, comparision> queueOfNodes;

    vector<pair<int, int>> vectorofEdges;

    int counter = 0;

    Node* first = newNode(matrixOfCost, vectorofEdges, 0, -1, 0, sizeOfMatrix);

    first->cost = cost(first->minimalMatrix, sizeOfMatrix); //obliczenie lower bound sciezki z pierwszego wezla w kolejce

    queueOfNodes.push(first); //dodanie wezla glownego do kolejki

    while(!queueOfNodes.empty() ) //szukanie wezlow o najnizszym koszcie - usuniecie znalezionego i dodanie ich potomkow do kolejki
    {
        Node* minimalNode = queueOfNodes.top(); // odnalezienie wezla o najnizszym koszcie

        queueOfNodes.pop(); //usuniecie wezla z kolejki

        int city = minimalNode ->vertex;    //przypisanie numeru wiercholka

        if(minimalNode->level == sizeOfMatrix - 1) //jesli odwiedzono wszystkie wierzcholki
        {
            int realCost = 0;

            minimalNode->edge.push_back(make_pair(city,0)); // dodanie krawedzi do wierzcholka poczatkowego

            for(unsigned int i = 0; i < minimalNode->edge.size(); i++) //wyswietlenie listy odwiedzonych wierzcholkow
            {
                    //wypisanie kolejnych wierzcholkow w sciezce optymalnej
                cout << minimalNode->edge[i].first << "->" << minimalNode->edge[i].second  << endl;
            }
            realCost = minimalNode->cost + matrixOfCost[minimalNode->edge[sizeOfMatrix-1].first][minimalNode->edge[sizeOfMatrix-1].second];
            //realny koszt jest rowny dotychczasowemu kosztowi wezla + koszt drogi z wezla do wezla poczatkowego
            cout << "Zminimalizowany koszt sciezki TSP  : " << minimalNode->cost << endl;
            cout << "Rzeczywisty koszt sciezki TSP: " << realCost << endl;
            cout << " Ilosc rozpatrzonych potomkow: " << counter << endl;
            cout << "Wielkosc kolejki: " << queueOfNodes.size() << endl;
            return;
        }

        for(int i = 0; i < sizeOfMatrix; i++) // utworzenie wezlow dla kazdego potomka badanego wierzcholka
        {
            if(minimalNode->minimalMatrix[city][i] != -1)
            {
                Node* child = newNode(minimalNode->minimalMatrix, minimalNode->edge, minimalNode->level+ 1, city , i, sizeOfMatrix);
                child->cost = minimalNode->cost + minimalNode->minimalMatrix[city][i] + cost(child->minimalMatrix, sizeOfMatrix);
                //koszt potomka jest równy dotychczasowemu kosztowi wêz³a + koszt drogi z wêz³a do potomka + koszt z minimalizacji macierzy potomka
                queueOfNodes.push(child);
                counter++;
            }
        }
    }
}
