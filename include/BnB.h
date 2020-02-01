#ifndef BNB_H
#define BNB_H
#include"TSP.h"
#include <vector>

class BnB : public TSP
{
    public:
        BnB( int **m, int s);
         //~BnB();
         int sizeOfMatrix;
         int **matrixOfCost;

         void branchAndBound();


    protected:

    private:
};

#endif // BNB_H
