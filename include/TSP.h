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

        string instance;        //nazwa instancji
        int sizeOfInstance;           //rozmiar instancji
        int **matrixOfCost;  //wskaznik na macierz kosztow podrozy komiwojazera
        int **matrixOfPerm; //wskaznik na macierz wszystkich permutacji
        int**loadOneInstance();     //ladowanie jednej instancji problemu podanej przez uzytkownika
        void loadAllInstance();     //laduje wszystkie instancje z podanej sciezki
        void loadRoadFromUser();    //laduje drogê podan¹ przez u¿ytkownika
        int result;             //wartosc funkcji celu

        void heapPermutation(int a[], int , int**& );
        int travllingSalesmanProblem(int**& , int**& , int  );
        void aimFunction();    //funkcja liczaca funkcje celu



    protected:

    private:
};

#endif // TSP_H
