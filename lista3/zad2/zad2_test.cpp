#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

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
int comparecount, swapcount;
random_device rd;
mt19937 mt(rd());

int main(int argc, char *argv[]) {
    clock_t start_t, end_t;
    long double randTimeSec=0,medianTimeSec=0;
    vector <int> randSelect;
    vector <int> medianSelect;
    int k,n=100,*tab,kthelement[3];
    double randMin,randMax,medianMin,medianMax,randMid,medianMid,randVar=0,medianVar=0,medianStd,randStd;
    for(n=100; n < 10000;n+=100){
        tab = create_random_permutation(tab,n);
        kthelement[0] = 2;
        kthelement[1] = n/2;
        kthelement[2] = n-1;
        for(int i = 0 ; i<3; i++){
            int tab_copy[n];
            for(int i = 0; i < n; i++)
                tab_copy[i] = tab[i];
            comparecount=0, swapcount=0;
            start_t = clock();
            randomized_select(tab,0,n-1,kthelement[i]);
            end_t = clock();
            randTimeSec += (double)(end_t - start_t) / CLOCKS_PER_SEC;
            randSelect.push_back(comparecount);
            randMid+=comparecount;
            for(int i = 0; i < n; i++)
                tab_copy[i] = tab[i];
            comparecount=0, swapcount=0;
            start_t = clock();
            select(tab_copy,0,n-1,kthelement[i]);
            end_t = clock();
            medianTimeSec += (double)(end_t - start_t) / CLOCKS_PER_SEC;
            select(tab_copy,0,n-1,kthelement[i]);
            medianSelect.push_back(comparecount);
            medianMid+=comparecount;
        }
    }
    randMin = *min_element(randSelect.begin(), randSelect.end());
    randMax = *max_element(randSelect.begin(), randSelect.end());
    medianMin = *min_element(medianSelect.begin(), medianSelect.end());
    medianMax = *max_element(medianSelect.begin(), medianSelect.end());
    randMid= randMid / randSelect.size();
    medianMid = medianMid / medianSelect.size();
    randTimeSec = randTimeSec / randSelect.size();
    medianTimeSec = medianTimeSec / medianSelect.size();
    for( n = 0; n < randSelect.size(); n++ )
    {
        randVar += (randSelect[n] - randMid) * (randSelect[n] - randMid);
    }
    randVar /= randSelect.size();
    randStd = sqrt(randVar);

    for( n = 0; n < medianSelect.size(); n++ )
    {
        medianVar += (medianSelect[n] - medianMid) * (medianSelect[n] - medianMid);
    }
    medianVar /= medianSelect.size();
    medianStd = sqrt(medianVar);
    cout<<"Dla RANDOM_SELECT | min: "<<randMin<<" | "<<"max: "<<randMax<<" | "<<"średnia: "<<randMid<<" | "<<"odchylenie: "<<randStd<<" | "<<"średnni czas w ms: "<<randTimeSec*1000<<endl;
    cout<<"Dla SELECT | min: "<<medianMin<<" | "<<"max: "<<medianMax<<" | "<<"średnia: "<<medianMid<<" | "<<"odchylenie: "<<medianStd<<" | "<<"średni czas w ms: "<<medianTimeSec*1000<<endl;
    return 0;
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
    swapcount++;
    int t = *a;
    *a = *b;
    *b = t;
}

int randomized_select(int* tab, int l, int r, int k){
    if(l == r){
        return l;
    }

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
        comparecount++;
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
        comparecount++;
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
                    comparecount++;
                    break;
                } else {
                    comparecount++;
                }
                swapcount++;
                tab[j + 1] = tab[j];
            }
            swapcount++;
            tab[j + 1] = val;
        }
    } else {
        cout<<"w insertion sort podano zly zakres"<<endl;
    }
}