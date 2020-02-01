#include "DP.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <chrono>
#include <limits.h>

using namespace std;

DP::DP()
{
    //ctor
}

DP::~DP()
{
    //dtor
}

int DP::getMinimum(int first, int set, int size, int **matrix, vector<vector<int>>&tabSubsetValues,
                    vector<vector<int>>&tabPossibleRoute, int &bitMask, int &newSubset) {
		int min = INT_MAX;
		int temporaryMin;        //tymczasowa najkrótsza sciezka
		if (tabSubsetValues[first][set] != -1)    //jezeli minimum dla podzbioru juz zostalo obliczone
			return tabSubsetValues[first][set];
		else {
			for (int i = 0; i < size; i++) {                // i - badany wierzchołek -  miasto
				bitMask = pow(2, size) - 1 - pow(2, i);    // "zaznaczanie" zerem kolejnego miasta;
				newSubset = set & bitMask;                 // tworzenie nowego podzbioru pozostałych miast do zbadania
				if (newSubset != set) {         //jesli rozpatrujemy nowy podzbior
                        temporaryMin = matrix[first][i] + getMinimum(i, newSubset, size, matrix,
                                                                 tabSubsetValues, tabPossibleRoute,bitMask,newSubset);
					if (temporaryMin < min) { //minimalizacja w zakresie podwywolania
						min = temporaryMin;
						tabPossibleRoute[first][set] = i;       //wpisujemy od ktorego miasta zaczynamy droge do "podzbioru"
					}
				}
			}
		}
		tabSubsetValues[first][set] = min; // zapisywanie do komorki sciezki minimalnej dla konkretnego podzbioru miast
		return min;
	}

void DP::getRoute(int start, int set, int size, vector<vector<int>>&possibleRouteTab,int*bestTab, int &c, int &bitMask, int &newSubset) {
	if (possibleRouteTab[start][set] == -1) { //jesli doszlismy do konca
		return;
	}

	int i = possibleRouteTab[start][set];
	bestTab[c] = i;             //do bestTab przesyłamy kolejne wierzchołki
	c++;

	bitMask = pow(2, size) - 1 - pow(2, i);
	newSubset = set & bitMask;

	getRoute(i, newSubset, size, possibleRouteTab,bestTab,c,bitMask,newSubset);
}

void DP::startDynamic(int &min, int **matrix, int size, vector<vector<int>>&tabNodeValues, vector<vector<int>>&possibleRouteTab, int *bestTab) {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < pow(2, size); j++) {    //uzupelniamy macierze wartosciami -1
				tabNodeValues[i][j] = -1;
				possibleRouteTab[i][j] = -1;
			}

		for (int i = 0; i < size; i++) {
			tabNodeValues[i][0] = matrix[i][0];         //przepisujemy pierwsze wartosci sciezki dla pierwszego wezla
		}

		int bitMask = 0, newSubset = 0;
		bestTab[0] = 0;
        // pow(2, size) - 2 -> "111...1110" -> zaczynamy od węzła '0'
		min = getMinimum(0, pow(2, size) - 2, size, matrix, tabNodeValues, possibleRouteTab,bitMask,newSubset);
		int counter = 1;
		getRoute(0, pow(2, size) - 2, size, possibleRouteTab,bestTab,counter,bitMask,newSubset);
	}
