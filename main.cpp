#include "tsp.h"
#include "BnB.h"
#include <iostream>

using namespace std;

int main(){
    TSP load = TSP();

    int** matrixOfCost;
    int** matrixOfPerm;
    int min_path;

    matrixOfCost = load.loadOneInstance();

    matrixOfPerm = new int *[load.sizeOfInstance];
    matrixOfPerm = 0;

    int a[load.sizeOfInstance];
    for (int i = 0; i < load.sizeOfInstance; i++){
        a[i] = i;
    }

    load.heapPermutation( a , load.sizeOfInstance, matrixOfPerm);

    min_path = load.travllingSalesmanProblem(matrixOfCost, matrixOfPerm, load.sizeOfInstance);

    cout<< "Najkrótsza sciezka: " << min_path << endl;
    /*
    BnB bnb = BnB( matrixOfCost, load.sizeOfInstance);
    bnb.branchAndBound();
    */
 return 0;
 }
