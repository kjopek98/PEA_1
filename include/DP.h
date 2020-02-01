#ifndef DP_H
#define DP_H
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <float.h>
#include <bits.h>
#include <string>
#include <conio.h>
#include <vector>
#include <math.h>

using namespace std;

class DP
{
    public:

        DP();
        virtual ~DP();

        int getMinimum(int startV, int set, int size, int **array, vector<vector<int>> &tabNodeValues, vector<vector<int>> &possibleRouteTab, int &bitMask, int &newSubset);
        void startDynamic(int &min, int **array, int size, vector<vector<int>> &tabNodeValues, vector<vector<int>> &possibleRouteTab, int *bestTab);
        void getRoute(int start, int set, int size, vector<vector<int>> &possibleRouteTab,int*bestTab, int &c, int &bitMask, int &newSubset);


    protected:

    private:
};


#endif // DP_H
