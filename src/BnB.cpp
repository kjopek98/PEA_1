#include "BnB.h"
#include<iostream>
#include "TSP.h"
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

BnB::BnB(int **k, int r)
{
    macierzKosztow = k;
    rozmiar = r;
}

struct Wezel //budowa wezla
{
    vector<pair<int, int>> krawedz;           //przechowuje krawedzie grafu
    int **minimalnaMacierz;                   //przechowuje zminimalizowana macierz wezla
    int koszt;                                //przechowuje koszt wezla (lower bound)
    int wierzcholek;                          //przechowuje wierzcholek, za ktory odpowiada wezel
    int poziom;                               //przechowuje ilosc wczesniej odwiedzonych miast
};

struct porownanie
{
    bool operator()(const Wezel* pierwszy, const Wezel* drugi)const
    {
        return pierwszy->koszt > drugi->koszt;
    }
};

// tworzy nowy wezel
Wezel* nowyWezel(int**& macierzBazowa, vector<pair<int, int>> const &krawedz, int poziom, int k, int m, int rozmiar)
{
    Wezel* wezel = new Wezel;

    wezel->krawedz = krawedz;

    if(poziom != 0) //jesli nie jest to wezel laczacy z glownym stworz nowa krawedz
    {
        wezel->krawedz.push_back(make_pair(k,m));
    }

    //memcpy(wezel->minimalnaMacierz, macierzBazowa, sizeof wezel->minimalnaMacierz);
    wezel->minimalnaMacierz = new int *[rozmiar];
    for(int i = 0; i < rozmiar; i++)
    {
        wezel->minimalnaMacierz[i] = new int[rozmiar];
        for(int j = 0; j < rozmiar; j++)
        {
            wezel->minimalnaMacierz[i][j] = macierzBazowa[i][j];
        }
    }

    if(poziom != 0) //pomijamy dla pierwszego poziomu
    {
        for(int i = 0; i < rozmiar; i++)    //wypelnniamy rzad i kolumne "-1"
        {
            wezel->minimalnaMacierz[k][i] = -1;
            wezel->minimalnaMacierz[i][m] = -1;
        }
    }

    wezel->minimalnaMacierz[m][0] = -1; //ustawienie popwrotu do 0 na "-1"
    wezel->poziom = poziom;             //ustawienie liczby odwiedzonych miast
    wezel->wierzcholek = m;             //ustawienie aktualnie rozpatrywanego wierzcholka

    return wezel;
}
//PODAC REFERENCJE DO MACIERZY !!!!!!
void minimalizacja(int**& minimalnaMacierz, int rzad[], int kolumna[], int rozmiar)
{
    for(int i = 0; i < rozmiar; i++) //inicjalizacja rzedu macierzy wartosciami "-1"
    {
        rzad[i] = -1;
        kolumna[i] = -1;
    }

    for(int i = 0; i < rozmiar; i++) //odnalezienie wartosci minimalnej w macierzy
    {
        for (int j = 0; j < rozmiar; j++)
        {
            if(minimalnaMacierz[i][j] < rzad[i] && minimalnaMacierz[i][j] > -1)
            {
                rzad[i] = minimalnaMacierz[i][j];
            }
            if(minimalnaMacierz[i][j] < kolumna[j] && minimalnaMacierz[i][j] > -1)
            {
                kolumna[j] = minimalnaMacierz[i][j];
            }
        }
    }

    for(int i = 0; i < rozmiar; i++) //odjecie minimum od kazdej wartosci w macierzy
    {
        for(int j = 0; j < rozmiar; j++)
        {
            if(minimalnaMacierz[i][j] != -1 && rzad[i] != -1)
            {
                minimalnaMacierz[i][j] -= rzad[i];
            }
            if(minimalnaMacierz[i][j] != -1 && kolumna[j] != -1)
            {
                minimalnaMacierz[i][j] -= kolumna[j];
            }
        }
    }
}

int koszt(int**& minimalnaMacierz, int rozmiar)
{
    int koszt = 0;

    int rzad[rozmiar];
    int kolumna[rozmiar];

    minimalizacja(minimalnaMacierz, rzad, kolumna, rozmiar);

    for(int i = 0; i < rozmiar; i++)
    {
        if(rzad[i] != -1)
        {
            koszt += rzad[i];
        }
        if(kolumna[i] != -1)
        {
            koszt += kolumna[i];
        }
    }

    return koszt;
}



void BnB::branchAndBound()
{
    priority_queue<Wezel*, vector<Wezel*>, porownanie> kolejka;

    vector<pair<int, int>> wektor;

    Wezel* glowny = nowyWezel(macierzKosztow, wektor, 0, -1, 0, rozmiar);   //OBSERWOWAC!!!!

    glowny->koszt = koszt(glowny->minimalnaMacierz, rozmiar); //obliczenie lower bound sciezki z pierwszego wezla

    kolejka.push(glowny); //dodanie wezla glownego do kolejki

    while(!kolejka.empty()) //szukanie wezlow o najnizszym koszcie - usuniecie znalezionego i dodanie ich potomkow do kolejki
    {
        Wezel* minimalny = kolejka.top(); // odnalezienie wezla o najnizszym koszcie

        kolejka.pop(); //usuniecie wezla z kolejki

        int miasto = minimalny->wierzcholek;

        if(minimalny->poziom == rozmiar - 1) //jesli odwiedzono wszystkie wierzcholki
        {
            minimalny->krawedz.push_back(make_pair(miasto,0)); //powrot do wierzcholka poczatkowego

            for(unsigned int i = 0; i < minimalny->krawedz.size(); i++) //wyswietlenie listy odwiedzonych wierzcholkow
            {
                cout << minimalny->krawedz[i].first + 1 << "->" << minimalny->krawedz[i].second + 1 << endl;
            }
            cout << "Koszt sciezki: " << minimalny->koszt << endl << endl;
            return;
        }

        for(int i = 0; i < rozmiar; i++) // utworzenie wezla dla kazdego potomka badanego wierzcholka
        {
            if(minimalny->minimalnaMacierz[miasto][i] != -1)
            {
                Wezel* potomek = nowyWezel(minimalny->minimalnaMacierz, minimalny->krawedz, minimalny->poziom + 1, miasto, i, rozmiar);

                potomek->koszt = minimalny->koszt + minimalny->minimalnaMacierz[miasto][i] + koszt(potomek->minimalnaMacierz, rozmiar);

                kolejka.push(potomek);
            }
        }
    }
}
