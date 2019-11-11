#ifndef BNB_H
#define BNB_H
#include"TSP.h"
#include <vector>

class BnB : public TSP
{
    public:
        BnB( int **k, int r);
         //~BnB();
         int rozmiar;
         int **macierzKosztow;

         void branchAndBound();


    protected:

    private:
};

#endif // BNB_H
