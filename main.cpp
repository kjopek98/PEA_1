#include "tsp.h"
#include "BnB.h"
#include "Timer.h"
#include "menu.h"
#include "DP.h"
#include <iostream>

using namespace std;

int main(){
    TSP load;
    Timer timer;
    menu start;
    DP* dp = new DP;
    int odp;

    int **matrixOfCost = load.loadOneInstance();

    int sizeofMatrix = load.sizeOfInstance;

    do{
        odp = start.show();

    switch(odp){

    case 1:
        {
             matrixOfCost = load.loadOneInstance();
             sizeofMatrix = load.sizeOfInstance;
             break;
        }

    case 2:
        {
        int costOfRoad = 0;
        vector<int> cities;
        int liczba = 0;
        int id;

        do{
        cout << "Wprowadz liczbe wierzcholkow w sciezce"<< endl;
        cin>> liczba;
        if (liczba <= sizeofMatrix){
        break;
        }
        else
        cout << "Zbyt duza liczba wierzcholkow"<< endl;
        }while(true);

        cout << "Podaj wierzcholki" <<endl;
        for(int i = 0; i < liczba; i++){
        cin>> id;
        cities.push_back(id);
        }
        timer.start();
        for (int i = 0; i < liczba - 1; i++)
        {
            costOfRoad += matrixOfCost[cities.at(i)][cities.at(i+1)];
        }

        costOfRoad += matrixOfCost[cities.at(liczba - 1)][cities.at(0)];

        cout<< "Koszt wynosi:" << costOfRoad <<endl;
        cout << "Czas wykonania: " << timer.duration() <<" ms" << endl;
        break;

        }

    case 3:
        {

        int sum = 0;
        int minTime = INT_MAX;
        int *tab = new int[sizeofMatrix];
        int *bestTab = new int[sizeofMatrix];
        int min = 99999;
        for (int i = 0; i < sizeofMatrix; i++){
            tab[i] = i;
        }
        for (int a = 0; a < 100; a++){
        timer.start();
        load.bestPermutation(tab, bestTab, 0, sizeofMatrix - 1, min, sizeofMatrix, matrixOfCost);
        int time = timer.duration();
        cout << "Czas wykonania: " << time <<" ms" << endl;
        cout << "\nMinimalna funkcja celu = " << load.calculateRoad(bestTab,sizeofMatrix,matrixOfCost) << endl;
        cout << "\nNajlepsza droga: ";
        for (int i = 0; i < sizeofMatrix; i++){
            cout << bestTab[i] << " ";
        }
        cout << endl << endl;
        sum = sum + time;
        if (time < minTime)
            minTime = time;
            }
        cout << "Sredni czas: " << sum / 100 << endl;
        cout << "Najkrotszy czas: " << minTime << endl;

        break;
        }
    case 4:
        {
            int sum = 0;
            int minTime = INT_MAX;
            //for (int a = 0; a < 100; a++){
            timer.start();
            BnB bnb = BnB( matrixOfCost, load.sizeOfInstance);
            bnb.branchAndBound();
            int time = timer.duration();
            cout << "Czas wykonania: " << timer.duration() <<" ms" << endl;
           // sum = sum + time;
           // if (time < minTime)
           // minTime = time;
           // }
           // cout << "Sredni czas: " << sum / 100 << endl;
            //cout << "Najkrotszy czas: " << minTime << endl;

            break;
        }
   case 5:
		{
		    int sum = 0;
            int minTime = INT_MAX;
            for (int a = 0; a < 100; a++){
			int min=INT_MAX;
			vector<vector<int>> tabNodeValues;
			vector<vector<int>> possibleRouteTab;
			int *bestTab = new int[sizeofMatrix];

			tabNodeValues = vector<vector<int>>(sizeofMatrix);
			possibleRouteTab = vector<vector<int>>(sizeofMatrix); //macierz wartosci kosztu drogi dla danego podzbioru wezlow
             //Tworzenie tablic wektorow o d³ugosci najwyzszej wartosci maski bitowej

			for (int i = 0; i < sizeofMatrix; i++) {
				tabNodeValues[i] = vector<int>(pow(2, sizeofMatrix));
				possibleRouteTab[i] = vector<int>(pow(2, sizeofMatrix));
                }
                timer.start();
				dp->startDynamic(min, matrixOfCost, sizeofMatrix, tabNodeValues, possibleRouteTab, bestTab);

				cout << "\nMinimalna funkcja celu = " << min;
				cout << "\nNajlepsza droga: ";
				for (int i = 0; i < sizeofMatrix; i++){
					cout << bestTab[i] << " ";
				}
				int time = timer.duration();
				cout << "\nCzas wykonania: " << time <<" ms" << endl;
                sum = sum + timer.duration();
                if (time < minTime){
                minTime = time;
                }
            }
                cout << "Sredni czas: " << sum / 100 << endl;
                cout << "Najkrotszy czas: " << minTime << endl;
				break;
        }


    case 6:
        {
        getchar();
        delete dp;
        return 0;
        }

    }
    }while(odp != 10);

    return 0;
 }
