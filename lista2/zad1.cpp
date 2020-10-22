#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
using namespace std;

struct Settings
{
    int sortType; // 1 - insert, 2 - merge, 3 - quick, -1 - wrong type
    bool asc;  //>= false, <= true, if not set set to <=
};

Settings setSettings(string sett[], int i);
int* create_tab(int n);
void printTab(int *tab, int size);
bool checkIfSorted(int* tab, int size, bool asc);
void swap(int* a, int* b);
void insertionSort(int tab[], int size, bool asc);
void mergeSort(int tab[], int l, int r, bool asc);
void merge(int tab[], int l, int m, int r, bool asc);
void quickSort(int tab[], int l, int r, bool asc);
int partition(int tab[], int l, int r, bool asc);

int compareCount, swapCount;

int main(int argc, char *argv[]) {
    time_t tt;
    int seed = time(&tt);
    srand(seed);

    clock_t start_t, end_t;
    double timeSec;
    compareCount = 0, swapCount = 0;
    string sett[argc-1];
    for(int i = 1, j=0; i<argc; i++, j++){
        sett[j] = argv[i];
    }
    Settings settings = setSettings(sett, argc - 1);

    int n,*tab;
    cout << "Podaj ilość elementów do posortowania"<< endl;
    cin>>n;
    cout << "Podaj elementy do posortowania"<< endl;
        switch ( settings.sortType )
        {
            case 1:
                tab = create_tab(n);

                start_t = clock();
                insertionSort(tab,n,settings.asc);
                end_t = clock();
                timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;

                cerr << "Compare count: " << compareCount << " |  Swap count: " << swapCount << " |  Time: " << timeSec << endl;
                if(checkIfSorted(tab,n,settings.asc)){
                    cout << "Ilość elementów: " << n << endl;
                    printTab(tab,n);
                } else {
                    cout << "Błąd sortowania!"<< endl;
                }
                break;
            case 2:
                tab = create_tab(n);

                start_t = clock();
                mergeSort(tab,0,n-1,settings.asc);
                end_t = clock();
                timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;

                cerr << "Compare count: " << compareCount << " |  Swap count: " << swapCount << " |  Time: " << timeSec << endl;
                if(checkIfSorted(tab,n,settings.asc)){
                    cout << "Ilość elementów: " << n << endl;
                    printTab(tab,n);
                } else {
                    cout << "Błąd sortowania!"<< endl;
                }
                break;
            case 3:
                tab = create_tab(n);

                start_t = clock();
                quickSort(tab, 0, n-1, settings.asc);
                end_t = clock();
                timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;

                cerr << "Compare count: " << compareCount << " |  Swap count: " << swapCount << " |  Time: " << timeSec << endl;
                if(checkIfSorted(tab,n,settings.asc)){
                    cout << "Ilość elementów: " << n << endl;
                    printTab(tab,n);
                } else {
                    cout << "Błąd sortowania!"<< endl;
                }
                break;
            default:
                cout << "Zły typ sortowania! " << endl;
        }


    return 0;
}

Settings setSettings(string sett[], int size) {
    Settings settings;
    settings.sortType = -1;
    settings.asc = true;

    for(int i = 0; i < size; i++){
        if(sett[i] == "--type" && i+1 < size){
            if(sett[i+1] == "insert"){
                settings.sortType = 1;
            } else if(sett[i+1] == "merge"){
                settings.sortType = 2;
            } else if (sett[i+1] == "quick"){
                settings.sortType = 3;
            } else {
                settings.sortType = -1;
                cout << "Nie podano właściwego formatu w jak sortować.";
            }
        } else if (sett[i] == "--comp" && i+1 < size) {
            if(sett[i+1] == ">="){
                settings.asc = false;
            }else if (sett[i+1] == "<=") {
                settings.asc = true;
            } else {
                settings.asc = true;
                cout << "Nie podano właściwego formatu w którą stronę sortować.";
            }
        }
    }

    return settings;
}

int* create_tab(int n){
    int *tab = (int*) malloc(sizeof(int)*n);
    for(int i = 0; i<n; i++){
        cin >> tab[i];
    }
    return tab;
}

bool checkIfSorted(int* tab, int size, bool asc){
    if(asc){
        for(int i = 0; i<size-1; i++){
            if(tab[i]>tab[i+1])
                return false;
        }
    } else {
        for(int i = 0; i<size-1; i++){
            if(tab[i]<tab[i+1])
                return false;
        }
    }
    return true;
}

void printTab(int *tab, int size){
    for(int i = 0; i < size; i++){
        cout << tab[i] << ", ";
    }
    cout << endl;
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void insertionSort(int tab[], int size, bool asc){
    if(size > 1){
        string comp = (asc)? " <= " : " >= ";
        if(asc){
            int val,i,j;
            for( i = 1; i < size; i++){
                val = tab[i];
                for( j = i-1; j >= 0; j--){
                    if(tab[j] <= val){
                        cerr << tab[j] << comp << val << endl;
                        compareCount++;
                        break;
                    } else {
                        cerr << tab[j] << comp << val << endl;
                        compareCount++;
                    }
                    cerr << tab[j+1] << " =element  swapped key= " << tab[j] << endl;
                    swapCount++;
                    tab[j+1] = tab[j];
                }
                cerr << tab[j+1] << " =element  swapped key= " << val << endl;
                swapCount++;
                tab[j+1]=val;
            }
        } else {
            int val,i,j;
            for( i = 1; i < size; i++){
                val = tab[i];
                for( j = i-1; j >= 0; j--){
                    if(tab[j] >= val){
                        cerr << tab[j] << comp << val << endl;
                        compareCount++;
                        break;
                    } else {
                        cerr << tab[j] << comp << val << endl;
                        compareCount++;
                    }
                    tab[j+1] = tab[j];
                }
                cerr << tab[j+1] << " =element  swapped key= " << val << endl;
                swapCount++;
                tab[j+1]=val;
            }
        }


    }
}

void mergeSort(int tab[], int l, int r, bool asc){
    if (l < r)
    {
        int m = (l+r)/2;
        mergeSort(tab, l, m, asc);
        mergeSort(tab, m+1, r, asc);
        merge(tab, l, m, r, asc);

    }
}

void merge(int tab[], int l, int m, int r, bool asc) {
    int i,j,k;
    string comp = (asc)? " <= " : " >= ";
    int sizeL = m - l + 1, sizeR = r - m; //[l > m+1], [m+1 > r]
    int L[sizeL],R[sizeR];

    for(i=0; i < sizeL; i++){
        L[i] = tab[l+i];
    }
    for(i=0; i < sizeR; i++){
        R[i] = tab[m+1+i];
    }
    if(asc){
        for(i=0,j=0,k=l;i<sizeL && j<sizeR;k++){
            if(L[i] < R[j]){
                cerr << L[i] << comp << R[j] << endl;
                cerr << tab[k] << " =element  swapped key= " << L[i] << endl;
                tab[k] = L[i];
                i++;
            } else {
                cerr << R[j] << comp << L[i] << endl;
                cerr << tab[k] << " =element  swapped key= " << R[j] << endl;
                tab[k] = R[j];
                j++;
            }
            swapCount++;
            compareCount++;
        }
    } else {
        for(i=0,j=0,k=l;i<sizeL && j<sizeR;k++){
            if(L[i] > R[j]){
                cerr << L[i] << comp << R[j] << endl;
                cerr << tab[k] << " =element  swapped key= " << L[i] << endl;
                tab[k] = L[i];
                i++;
            } else {
                cerr << R[j] << comp << L[i] << endl;
                cerr << tab[k] << " =element  swapped key= " << R[j] << endl;
                tab[k] = R[j];
                j++;
            }
            swapCount++;
            compareCount++;
        }
    }

    while(i<sizeL){
        cerr << tab[k] << " =element  swapped key= " << L[i] << endl;
        swapCount++;

        tab[k] = L[i];
        i++;
        k++;
    }
    while(j<sizeR){
        cerr << tab[k] << " =element  swapped key= " << R[j] << endl;
        swapCount++;

        tab[k] = R[j];
        j++;
        k++;
    }
}

void quickSort(int tab[], int l, int r, bool asc){
    if(l < r){
        int q = partition(tab,l,r,asc);
        quickSort(tab,l,q-1,asc);
        quickSort(tab,q+1,r,asc);
    }

}

int partition(int tab[], int l, int r, bool asc) {
    int x = tab[r];
    string comp = (asc)? " <= " : " >= ";
    int i,j;
    if(asc){
        for(i = l-1, j = l; j < r ; j++){
            if(tab[j] <= x){
                cerr << tab[j] << comp << x << endl;
                cerr << tab[i] << " =element  swapped element= " << tab[j] << endl;
                swapCount++;
                compareCount++;
                i++;
                swap(tab[i],tab[j]);
            }
        }
        cerr << tab[i+1] << " =element  swapped element= " << tab[r] << endl;
        swapCount++;
        swap(tab[i+1],tab[r]);
        return i+1;
    } else {
        for(i = l-1, j = l; j < r ; j++){
            if(tab[j] >= x){
                cerr << tab[j] << comp << x << endl;
                cerr << tab[i] << " =element  swapped element= " << tab[j] << endl;
                swapCount++;
                compareCount++;
                i++;
                swap(tab[i],tab[j]);
            }
        }
        cerr << tab[i+1] << " =element  swapped element= " << tab[r] << endl;
        swapCount++;
        swap(tab[i+1],tab[r]);
        return i+1;
    }
}
