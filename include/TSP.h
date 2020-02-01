#ifndef TSP_H
#define TSP_H
#include <string>
#include <cstdlib>

using namespace std;

class TSP
{
    public:
        TSP();
        virtual ~TSP();

        void bestPermutation(int *, int *, int , int , int &, int , int **);
        int calculateRoad(int* , int , int **);

        string instance;        //nazwa instancji
        int sizeOfInstance;           //rozmiar instancji
        int **matrixOfCost;  //wskaznik na macierz kosztow podrozy komiwojazera
        int **matrixOfPerm; //wskaznik na macierz wszystkich permutacji
        int **loadOneInstance();     //ladowanie jednej instancji problemu podanej przez uzytkownika
        void loadAllInstance();     //laduje wszystkie instancje z podanej sciezki
        int result;             //wartosc funkcji celu
        int index;              //zmienna pomocnicza dla funkcji heapPermutation




    protected:

    private:
};

#endif // TSP_H
