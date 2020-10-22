#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;
int compares;

int binarySearch(int* tab, int l, int r, int k){
    if (r >= l) {
        int mid = (l+r) / 2;
        if (tab[mid] == k){
            return 1;
        }
        compares++;
        if (tab[mid] > k)
            return binarySearch(tab, l, mid - 1, k);
        return binarySearch(tab, mid + 1, r, k);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    double start_t, end_t;
    double timeSec;
    int k,tab_size,result;
    cout<<"Wczytaj długość danych w tablicy:";
    cin>>tab_size;
    int* tab = (int*) malloc(sizeof(int)*tab_size);
    cout<<"Wczytaj jakiej liczby istnienie chcesz sprawdzić:";
    cin>>k;
    cout<<"Wpisz tablicę posortowaną rosnąco::";
    for(int i = 0; i<tab_size; i++){
        cin>>tab[i];
    }
    result = binarySearch(tab,0,tab_size-1,k);
    cout<<((result)?"1: szukana liczba jest w tej tablicy":"0: szukanej liczby nie ma w tej tablicy")<<endl;

    for(int i = 1000; i <= 100000; i+=1000){
        compares = 0;
        tab = (int*) malloc(sizeof(int)*i);
        for(int j = 1; j<=i; j++){
            tab[j-1] = j;
        }
        start_t = clock();
        result = binarySearch(tab,0,i-1,k);
        end_t = clock();
        timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        cout<<"Czy znaleziono: "<<((result)?"tak | ":"nie | ")<<compares<<" porównań | czas to: "<< fixed << setprecision(10) << timeSec <<" | i=: "<<i<< endl;
    }

    return 0;
}
