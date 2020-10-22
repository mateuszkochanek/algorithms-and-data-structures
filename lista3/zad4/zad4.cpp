#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <random>

using namespace std;

struct Settings
{
    int sortType; // 1 - quick, 2 - dualquick, 3 - quick z selectem, 4 - dual quick z selectem, -1 - wrong
    bool asc;  //>= false, <= true, if not set set to <=
    bool stat;  // true use random arrays, false input array
    string fileName;
    int k;
};


Settings setSettings(string sett[], int i);
int* create_tab(int* tab,int n);
int* create_random_tab(int* tab,int n);
void printTab(int *tab, int size);
void swap(int* a, int* b);

void quickSort(int tab[], int l, int r, bool asc);
int partition(int tab[], int l, int r, bool asc);

void dualQuickSort(int *tab, int l, int r, bool asc);
int dualPartition(int *tab, int l, int r, int* lq, bool asc);

void quickSortv2(int tab[], int l, int r, bool asc);
int partitionv2(int tab[], int l, int r, int median, bool asc);

void dualQuickSortv2(int *tab, int l, int r, bool asc);
int dualPartitionv2(int *tab, int l, int r,int median_one_third, int median_two_thirds, int* lq, bool asc);

int select(int* tab, int l, int r, int k);
int select_partition(int* tab,int l,int r,int x);
int findMedian(int* tab, int first, int last, int number_of_elements);
void insertionSort(int tab[], int first, int last);

void runTest(const Settings settings, int tab[], int n);
bool checkIfSorted(const int* tab, int size, bool asc);
void runStatTest(const Settings settings, int *tab, int n,ofstream& outfile);

unsigned long long compareCount, swapCount;

int main(int argc, char *argv[]) {
    time_t tt;
    int seed = time(&tt);
    srand(seed);

    compareCount = 0, swapCount = 0;
    string sett[argc-1];
    for(int i = 1, j=0; i<argc; i++, j++){
        sett[j] = argv[i];
    }
    Settings settings = setSettings(sett, argc - 1);

    if(settings.stat){
        ofstream outfile;
        outfile.open(settings.fileName, ios::out);
        int* tab,a=10,b=5;
        while(a<=100000) {
            for (int i = 0; i < settings.k && b >= 50; i++) {
                compareCount = 0, swapCount = 0;
                tab = create_random_tab(tab,b);
                runStatTest(settings,tab,b,outfile);
            }
            b*=10;
            for (int i = 0; i < settings.k; i++) {
                compareCount = 0, swapCount = 0;
                tab = create_random_tab(tab,a);
                runStatTest(settings,tab,a,outfile);
            }
            a*=10;
        }
    } else {
        int n;
        cout << "Podaj ilość elementów do posortowania"<< endl;
        cin>>n;
        cout << "Podaj elementy do posortowania"<< endl;
        int* tab = create_tab(tab,n);
        runTest(settings, tab, n);
    }


    return 0;
}

void runStatTest(const Settings settings, int *tab, int n, ofstream& outfile) {
    clock_t start_t, end_t;
    unsigned long ramBefore, ramAfter;
    double timeSec;
    switch ( settings.sortType )
    {
        case 1:
            compareCount = 0, swapCount = 0;
            start_t = clock();
            quickSort(tab, 0, n - 1, settings.asc);
            end_t = clock();
            timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;
            outfile << n << " " << compareCount << " " << swapCount << " " << fixed << setprecision(10) << timeSec << endl;
            break;
        case 2:
            compareCount = 0, swapCount = 0;
            start_t = clock();
            dualQuickSort(tab, 0, n - 1, settings.asc);
            end_t = clock();
            timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;
            outfile << n << " " << compareCount << " " << swapCount << " " << fixed << setprecision(10) << timeSec << endl;
            break;
        case 3:
            compareCount = 0, swapCount = 0;
            start_t = clock();
            quickSortv2(tab, 0, n - 1, settings.asc);
            end_t = clock();
            timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;
            outfile << n << " " << compareCount << " " << swapCount << " " << fixed << setprecision(10) << timeSec << endl;
            break;
        case 4:
            compareCount = 0, swapCount = 0;
            start_t = clock();
            dualQuickSortv2(tab, 0, n - 1, settings.asc);
            end_t = clock();
            timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;
            outfile << n << " " << compareCount << " " << swapCount << " " << fixed << setprecision(10) << timeSec << endl;
            break;
        default:
            cout << "Zły typ sortowania! " << endl;
    }
}

void runTest(const Settings settings, int tab[], int n){

    clock_t start_t, end_t;
    double timeSec;
    switch ( settings.sortType )
    {
        case 1:
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
        case 2:
            start_t = clock();
            dualQuickSort(tab,0,n-1,settings.asc);
            end_t = clock();
            timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;

            cerr << "Compare count: " << compareCount << " |  Swap count: " << swapCount << " |  Time: "<< fixed << setprecision(10) << timeSec << endl;
            if(checkIfSorted(tab,n,settings.asc)){
                cout << "Ilość elementów: " << n << endl;
                printTab(tab,n);
            } else {
                cout << "Błąd sortowania!"<< endl;
            }
            break;
        case 3:
            start_t = clock();
            quickSortv2(tab, 0, n-1, settings.asc);
            end_t = clock();
            timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;

            cerr << "Compare count: " << compareCount << " |  Swap count: " << swapCount << " |  Time: "<< fixed << setprecision(10) << timeSec << endl;
            if(checkIfSorted(tab,n,settings.asc)){
                cout << "Ilość elementów: " << n << endl;
                printTab(tab,n);
            } else {
                cout << "Błąd sortowania!"<< endl;
            }
            break;
        case 4:
            start_t = clock();
            dualQuickSortv2(tab,0,n-1,settings.asc);
            end_t = clock();
            timeSec = (double)(end_t - start_t) / CLOCKS_PER_SEC;

            cerr << "Compare count: " << compareCount << " |  Swap count: " << swapCount << " |  Time: "<< fixed << setprecision(10) << timeSec << endl;
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
}

Settings setSettings(string sett[], int size) {
    Settings settings;
    settings.sortType = -1;
    settings.asc = true;

    for (int i = 0; i < size; i++) {
        if (sett[i] == "--type" && i + 1 < size) {
            if (sett[i + 1] == "quick") {
                settings.sortType = 1;
            } else if (sett[i + 1] == "dual") {
                settings.sortType = 2;
            } else if (sett[i + 1] == "quickv2") {
                settings.sortType = 3;
            } else if (sett[i + 1] == "dualv2") {
                settings.sortType = 4;
            } else {
                settings.sortType = -1;
                cout << "Nie podano właściwego formatu w jak sortować.";
            }
        } else if (sett[i] == "--comp" && i + 1 < size) {
            if (sett[i + 1] == ">=") {
                settings.asc = false;
            } else if (sett[i + 1] == "<=") {
                settings.asc = true;
            } else {
                settings.asc = true;
                cout << "Nie podano właściwego formatu w którą stronę sortować.";
            }
        } else if (sett[i] == "--stat" && i+2 < size) {
            settings.stat=true;
            settings.fileName = sett[i+1];
            try {
                settings.k = std::stoi(sett[i+2]);
            } catch (std::invalid_argument const &e) {
                std::cout << "Zły input dla ilosci powtorzen" << '\n';
            } catch (std::out_of_range const &e) {
                std::cout << "Za duza ilosc powt" << '\n';
            }
        }
    }

    return settings;
}

int* create_tab(int* tab,int n){
    tab = (int*) malloc(sizeof(int)*n);
    for(int i = 0; i<n; i++){
        cin >> tab[i];
    }
    return tab;
}

int* create_random_tab(int* tab,int n){
    tab = (int*) malloc(sizeof(int)*n);
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1.0, 9.0);
    for(int i = 0; i<n; i++){
        tab[i] = dist(mt);
    }
    return tab;
}


void printTab(int *tab, int size){
    for(int i = 0; i < size; i++){
        cout << tab[i] << ", ";
    }
    cout << endl;
}

bool checkIfSorted(const int* tab, int size, bool asc){
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

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
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
                swapCount++;
                compareCount++;
                i++;
                swap(tab[i],tab[j]);
            }
        }
        swapCount++;
        swap(tab[i+1],tab[r]);
        return i+1;
    } else {
        for(i = l-1, j = l; j < r ; j++){
            if(tab[j] >= x){
                swapCount++;
                compareCount++;
                i++;
                swap(tab[i],tab[j]);
            }
        }
        swapCount++;
        swap(tab[i+1],tab[r]);
        return i+1;
    }
}

void dualQuickSort(int *tab, int l, int r, bool asc){
    if(l < r){
        int lq, rq;
        rq = dualPartition(tab, l, r, &lq, asc);
        dualQuickSort(tab,l,lq-1,asc);
        dualQuickSort(tab,lq+1,rq-1,asc);
        dualQuickSort(tab,rq,r,asc);
    }

}

int dualPartition(int *tab, int l, int r, int* lq, bool asc) {
    if(asc){
        if (tab[l] > tab[r])
            swap(&tab[l], &tab[r]);
        swapCount++;
        compareCount++;

        int i = l + 1;
        int currCheckingHigh = r - 1, currCheckingLow = l + 1;
        int llq = tab[l], rrq = tab[r];
        while (currCheckingLow <= currCheckingHigh) {
            if (tab[currCheckingLow] < llq) {
                swap(&tab[currCheckingLow], &tab[i]);
                swapCount++;
                i++;
            } else if (tab[currCheckingLow] >= rrq) {
                compareCount++;
                while (tab[currCheckingHigh] > rrq && currCheckingLow < currCheckingHigh){
                    compareCount++;
                    currCheckingHigh--;
                }

                if(tab[currCheckingHigh] <= rrq)
                    compareCount++;

                swap(&tab[currCheckingLow], &tab[currCheckingHigh]);
                swapCount++;
                currCheckingHigh--;
                if (tab[currCheckingLow] < llq) {
                    swap(&tab[currCheckingLow], &tab[i]);
                    swapCount++;
                    i++;
                }
                compareCount++;
            }
            compareCount++;
            currCheckingLow++;
        }
        i--;
        currCheckingHigh++;

        swap(&tab[l], &tab[i]);
        swap(&tab[r], &tab[currCheckingHigh]);
        swapCount+=2;
        *lq = i;

        return currCheckingHigh;

    } else {
        if (tab[l] < tab[r])
            swap(&tab[l], &tab[r]);
        swapCount++;
        compareCount++;

        int i = l + 1;
        int currCheckingHigh = r - 1, currCheckingLow = l + 1;
        int llq = tab[l], rrq = tab[r];//llq to większy
        while (currCheckingLow <= currCheckingHigh) {
            if (tab[currCheckingLow] > llq) {
                swap(&tab[currCheckingLow], &tab[i]);
                swapCount++;
                i++;
            } else if (tab[currCheckingLow] <= rrq) {
                compareCount++;
                while (tab[currCheckingHigh] < rrq && currCheckingLow < currCheckingHigh){
                    compareCount++;
                    currCheckingHigh--;
                }
                if(tab[currCheckingHigh] >= rrq)
                    compareCount++;

                swap(&tab[currCheckingLow], &tab[currCheckingHigh]);
                swapCount++;
                currCheckingHigh--;
                if (tab[currCheckingLow] > llq) {
                    swap(&tab[currCheckingLow], &tab[i]);
                    swapCount++;
                    i++;
                }
                compareCount++;
            }
            compareCount++;
            currCheckingLow++;
        }
        i--;
        currCheckingHigh++;

        swap(&tab[l], &tab[i]);
        swap(&tab[r], &tab[currCheckingHigh]);
        swapCount+=2;
        *lq = i;

        return currCheckingHigh;
    }
}

void quickSortv2(int tab[], int l, int r, bool asc){
    if(l < r){
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
        int q = partitionv2(tab,l,r,median_of_medians,asc);
        quickSort(tab,l,q-1,asc);
        quickSort(tab,q+1,r,asc);
    }

}

int partitionv2(int tab[], int l, int r, int median, bool asc) {
    int i,j;
    for (i=l; i<r; i++)
        if (tab[i] == median)
            break;
    swap(&tab[i], &tab[r]);

    if(asc){
        for(i = l-1, j = l; j < r ; j++){
            if(tab[j] <= median){
                swapCount++;
                compareCount++;
                i++;
                swap(tab[i],tab[j]);
            }
        }
        swapCount++;
        swap(tab[i+1],tab[r]);
        return i+1;
    } else {
        for(i = l-1, j = l; j < r ; j++){
            if(tab[j] >= median){
                swapCount++;
                compareCount++;
                i++;
                swap(tab[i],tab[j]);
            }
        }
        swapCount++;
        swap(tab[i+1],tab[r]);
        return i+1;
    }
}

void dualQuickSortv2(int *tab, int l, int r, bool asc){
    if(l < r){
        int i, j, number_of_elements = r-l+1, number_of_last_elements = (r-l+1)%5, median_one_third,median_two_thirds;
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

        if(number_of_medians == 1){
            median_one_third = medians[0];
            median_two_thirds = medians[0];
        } else if (number_of_medians == 2){
            median_one_third = medians[0];
            median_two_thirds = medians[1];
        } else {
            median_one_third = select(medians, 0, number_of_medians-1, number_of_medians/3);
            median_two_thirds = select(medians, 0, number_of_medians-1, (number_of_medians/3)*2);
        }

        int lq, rq;
        rq = dualPartitionv2(tab, l, r,median_one_third,median_two_thirds, &lq, asc);
        dualQuickSortv2(tab,l,lq-1,asc);
        dualQuickSortv2(tab,lq+1,rq-1,asc);
        dualQuickSortv2(tab,rq,r,asc);
    }

}

int dualPartitionv2(int *tab, int l, int r,int median_one_third, int median_two_thirds, int* lq, bool asc) {
    int i;
    for (i=l; i<r; i++)
        if (tab[i] == median_one_third)
            break;
    swap(&tab[i], &tab[l]);
    for (i=l; i<r; i++)
        if (tab[i] == median_two_thirds)
            break;
    swap(&tab[i], &tab[r]);

    if(asc){
        if (tab[l] > tab[r])
            swap(&tab[l], &tab[r]);
        swapCount++;
        compareCount++;

        i = l + 1;
        int currCheckingHigh = r - 1, currCheckingLow = l + 1;
        int llq = tab[l], rrq = tab[r];
        while (currCheckingLow <= currCheckingHigh) {
            if (tab[currCheckingLow] < llq) {
                swap(&tab[currCheckingLow], &tab[i]);
                swapCount++;
                i++;
            } else if (tab[currCheckingLow] >= rrq) {
                compareCount++;
                while (tab[currCheckingHigh] > rrq && currCheckingLow < currCheckingHigh){
                    compareCount++;
                    currCheckingHigh--;
                }

                if(tab[currCheckingHigh] <= rrq)
                    compareCount++;

                swap(&tab[currCheckingLow], &tab[currCheckingHigh]);
                swapCount++;
                currCheckingHigh--;
                if (tab[currCheckingLow] < llq) {
                    swap(&tab[currCheckingLow], &tab[i]);
                    swapCount++;
                    i++;
                }
                compareCount++;
            }
            compareCount++;
            currCheckingLow++;
        }
        i--;
        currCheckingHigh++;

        swap(&tab[l], &tab[i]);
        swap(&tab[r], &tab[currCheckingHigh]);
        swapCount+=2;
        *lq = i;

        return currCheckingHigh;

    } else {
        if (tab[l] < tab[r])
            swap(&tab[l], &tab[r]);
        swapCount++;
        compareCount++;

        i = l + 1;
        int currCheckingHigh = r - 1, currCheckingLow = l + 1;
        int llq = tab[l], rrq = tab[r];//llq to większy
        while (currCheckingLow <= currCheckingHigh) {
            if (tab[currCheckingLow] > llq) {
                swap(&tab[currCheckingLow], &tab[i]);
                swapCount++;
                i++;
            } else if (tab[currCheckingLow] <= rrq) {
                compareCount++;
                while (tab[currCheckingHigh] < rrq && currCheckingLow < currCheckingHigh){
                    compareCount++;
                    currCheckingHigh--;
                }
                if(tab[currCheckingHigh] >= rrq)
                    compareCount++;

                swap(&tab[currCheckingLow], &tab[currCheckingHigh]);
                swapCount++;
                currCheckingHigh--;
                if (tab[currCheckingLow] > llq) {
                    swap(&tab[currCheckingLow], &tab[i]);
                    swapCount++;
                    i++;
                }
                compareCount++;
            }
            compareCount++;
            currCheckingLow++;
        }
        i--;
        currCheckingHigh++;

        swap(&tab[l], &tab[i]);
        swap(&tab[r], &tab[currCheckingHigh]);
        swapCount+=2;
        *lq = i;

        return currCheckingHigh;
    }
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

        int q = select_partition(tab,l,r,median_of_medians);
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
    cout<<l<<" "<<r<<" "<<k<<endl;
    return -1;
}

int select_partition(int* tab,int l,int r, int x){
    int i;
    for (i=l; i<r; i++)
        if (tab[i] == x)
            break;
    swap(&tab[i], &tab[r]);
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        compareCount++;
        if (tab[j] <= x)
        {
            swap(&tab[i], &tab[j]);
            i++;
        }
    }
    swap(&tab[i], &tab[r]);
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
                    compareCount++;
                    break;
                } else {
                    compareCount++;
                }
                swapCount++;
                tab[j + 1] = tab[j];
            }
            swapCount++;
            tab[j + 1] = val;
        }
    } else {
        cout<<"w insertion sort podano zly zakres"<<endl;
    }
}