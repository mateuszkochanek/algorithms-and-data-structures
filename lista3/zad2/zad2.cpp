#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

struct Settings
{
    int data;
};

Settings setSettings(string sett[], int size);
int* create_random_permutation(int* tab,int n);
int* create_random_tab(int* tab,int n);
void mySwap(int* a, int* b);
int randomized_select(int* tab, int l, int r, int k);
int randomized_partition(int* tab,int l,int r);
int select(int* tab, int l, int r, int k);
int partition(int* tab,int l,int r,int x);
int findMedian(int* tab, int first, int last, int number_of_elements);
void insertionSort(int tab[], int first, int last);

int tab_size;
int compare_count, swap_count;
random_device rd;
mt19937 mt(rd());

int main(int argc, char *argv[]) {
    time_t tt;
    int seed = time(&tt);
    srand(seed);

    compare_count = 0, swap_count = 0;
    string sett[argc-1];
    for(int i = 1, j=0; i<argc; i++, j++){
        sett[j] = argv[i];
    }
    Settings settings = setSettings(sett, argc - 1);

    int k,*tab,kthelement;
    cout<<"Wczytaj długość danych w tablicy:";
    cin>>tab_size;
    cout<<"Wczytaj ktora z kolei liczbę chcesz znaleźć:";
    cin>>k;
    int tab_copy[tab_size],index;
    if(settings.data == 0){
        tab = create_random_tab(tab,tab_size);
        for(int i = 0; i < tab_size; i++)
            tab_copy[i] = tab[i];
        index = randomized_select(tab,0,tab_size-1,k);
        cerr << "Compare count: " << compare_count << " |  Swap count: " << swap_count<<endl;
        for(int i = 0; i < tab_size; i++){
            if(i == index)
                cout<<"["<<tab[i]<<"] ";
            else
                cout<<tab[i]<<" ";
        }
        cout<< endl;
        compare_count=0, swap_count=0;
        cerr <<"____________________________________________"<< endl;
        kthelement = select(tab_copy,0,tab_size-1,k);
        cerr << "Compare count: " << compare_count << " |  Swap count: " << swap_count<<endl;
        for(int i = 0; i < tab_size; i++){
            if(tab_copy[i] == kthelement)
                cout<<"["<<tab_copy[i]<<"] ";
            else
                cout<<tab_copy[i]<<" ";
        }
    } else if (settings.data == 1){
        tab = create_random_permutation(tab,tab_size);
        for(int i = 0; i < tab_size; i++)
            tab_copy[i] = tab[i];
        index = randomized_select(tab,0,tab_size-1,k);
        cerr << "Compare count: " << compare_count << " |  Swap count: " << swap_count<<endl;
        for(int i = 0; i < tab_size; i++){
            if(i == index)
                cout<<"["<<tab[i]<<"] ";
            else
                cout<<tab[i]<<" ";
        }
        cout<< endl;
        compare_count=0, swap_count=0;
        cerr <<"____________________________________________"<< endl;
        kthelement = select(tab_copy,0,tab_size-1,k);
        cerr << "Compare count: " << compare_count << " |  Swap count: " << swap_count<<endl;
        for(int i = 0; i < tab_size; i++){
            if(tab_copy[i] == kthelement)
                cout<<"["<<tab_copy[i]<<"] ";
            else
                cout<<tab_copy[i]<<" ";
        }

    } else {
        cout<<"Nie podano jaki tym tablicy stworzyc, w argumentach podaj -r aby dostac tablice losowych wartosci o dlugosci n, lub -p aby dostac losową permutację tablicy {1,2,3..n}";
    }



    return 0;
}

Settings setSettings(string sett[], int size) {
    Settings settings;
    settings.data = -1;

    for (int i = 0; i < size; i++) {
        if (sett[i] == "-r") {
            settings.data = 0;
        } else if (sett[i] == "-p") {
            settings.data = 1;
        }
    }

    return settings;
}

int* create_random_permutation(int* tab,int n){
    tab = (int*) malloc(sizeof(int)*n);
    for(int i = 1; i<=n; i++){
        tab[i-1] = i;
    }
    random_shuffle(tab, tab+n);
    return tab;
}

int* create_random_tab(int* tab,int n){
    tab = (int*) malloc(sizeof(int)*n);
    uniform_int_distribution<int> dist(1.0, 1000.0);
    for(int i = 0; i<n; i++){
        tab[i] = dist(mt);
    }
    return tab;
}

void mySwap(int* a, int* b) {
    cerr << *a << " = swapped = " << *b << endl;
    swap_count++;
    int t = *a;
    *a = *b;
    *b = t;
}

int randomized_select(int* tab, int l, int r, int k){
    if(l == r){
        return l;
    }

    for(int i = 0; i < tab_size; i++)
        cerr<<tab[i]<<" ";
    cerr<<endl;
    cerr<<"pivot: "<<r<<"  k: "<<k<<endl;

    int q = randomized_partition(tab,l,r);
    int down_element_count = q-l+1;
    if(k == down_element_count){
        return q;
    } else if (k < down_element_count){
        return randomized_select(tab,l,q-1,k);
    }else{
        return randomized_select(tab,q+1,r,k-down_element_count);
    }
}

int randomized_partition(int* tab,int l,int r){
    uniform_int_distribution<int> dist(l, r);
    int i = dist(mt),j;
    mySwap(&tab[r],&tab[i]);
    int x = tab[r];
    for(i = l-1, j = l; j < r ; j++){
        cerr << tab[j] << " =compared= " << x << endl;
        compare_count++;
        if(tab[j] <= x){
            i++;
            mySwap(&tab[i],&tab[j]);
        }
    }
    mySwap(&tab[i+1],&tab[r]);
    return i+1;
}

int select(int* tab, int l, int r, int k){
    if(l == r)
        return tab[l];
    if (k > 0 && k <= r - l + 1)
    {
        int i, j, number_of_elements = r-l+1, number_of_last_elements = (r-l+1)%5,median_of_medians;
        int number_of_medians = (int)floor(number_of_elements/5);
        if(number_of_medians == 0)
            number_of_medians = 1;
        int medians[number_of_medians];
        for(i=0,j=l;i<number_of_medians && j+4<=r;i++,j+=5){
            medians[i] = findMedian(tab,j,j+4,5);
        }
        if(j<=r){
            medians[i] = findMedian(tab,j,j+number_of_last_elements-1,number_of_last_elements);
        }

        median_of_medians = (number_of_medians == 1)? medians[0] : select(medians, 0, number_of_medians-1, number_of_medians/2);
        for(int i = 0; i < tab_size; i++)
            cerr<<tab[i]<<" ";
        cerr<<endl;
        cerr<<"pivot: "<<median_of_medians<<"  k: "<<k<<endl;
        int q = partition(tab,l,r,median_of_medians);
        int down_element_count = q-l+1;
        if(k == down_element_count){
            return tab[q];
        }else if (k < down_element_count){
            return select(tab,l,q-1,k);
        }else{
            return select(tab,q+1,r,k-down_element_count);
        }
    }
    cout<<"Podano k większe niż ilosc elementow w tablicy!"<<endl;
    return -1;
}

int partition(int* tab,int l,int r, int x){
    int i;
    for (i=l; i<r; i++)
        if (tab[i] == x)
            break;
    mySwap(&tab[i], &tab[r]);
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        compare_count++;
        cerr << tab[j] << " =compared= " << x << endl;
        if (tab[j] <= x)
        {
            mySwap(&tab[i], &tab[j]);
            i++;
        }
    }
    mySwap(&tab[i], &tab[r]);
    return i;
}

int findMedian(int* tab, int first, int last, int number_of_elements){
    if(first == last)
        return tab[first];
    insertionSort(tab,first,last);
    return tab[first+((int)floor((number_of_elements-1)/2))];
}

void insertionSort(int tab[], int first, int last){ // sorts tab from [first, last]
    if(last - first > 0) {
        int val=0;
        int i=0, j=0;
        for (i = first + 1; i <= last; i++) {
            val = tab[i];
            for (j = i - 1; j >= first; j--) {
                if (tab[j] <= val) {
                    cerr << tab[j] << " =compared= " << val << endl;
                    compare_count++;
                    break;
                } else {
                    cerr << tab[j] << " =compared= " << val << endl;
                    compare_count++;
                }
                cerr << tab[j+1] << " =swapped= " << tab[j] << endl;
                swap_count++;
                tab[j + 1] = tab[j];
            }
            cerr << tab[j+1] << " =swapped= " << val << endl;
            swap_count++;
            tab[j + 1] = val;
        }
    } else {
        cout<<"w insertion sort podano zly zakres"<<endl;
    }
}