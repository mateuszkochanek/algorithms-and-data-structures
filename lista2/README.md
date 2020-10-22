Proszę używać "" dookoła komparatorów, inaczej bash może uznać > jako przekierowanie i nie wyświetlić informacji


### Zadanie1
Ma zrobione 3 algorytmy sortujące, insert, merge i quick sort. Aby je uruchomić należy wpisać:
1. g++ zad1.c 
2. ./a.out --type ${rodzaj sortowania:(insert;quick;merge)} --comp ${comparator:("<=";">=")}
   ./a.out --comp "<=" --type quick
3. W trakcie działania programu wpisać liczbę całkowitą n czyli ilość elementów w tablicy, i podać liczby całkowite do posortowania.
Łatwo zauważyć, że radix sort ma mniejszy czas działania i wykonuje mniej operacji niż inne sortowania w programie. Dodatkowo przedział ma duży wplyw na to jak szybko sortuje radix sort, im mniej cyfr ma największa liczba w tablicy którą sortujemy tym stosunkowo mniejszy będzie czas sortowania.
Z drugiej strony radix sort jako jedyny nie jest sortowaniem w miejscu a dystrybucyjnym, dlatego używa więcej pamięci niż pozostałe.
_______________________________________________________

### Zadanie2
Działa tak samo jak zad1, ale ma dodatkowy parametr --stat ${nazwa_pliku} ${liczba_k}, jeżeli go użyjemy to dane sortowanie wykona się dla n = 100,200 ... 10000, dla każdego n po k razy i zostanie zapisane do ${nazwa_pliku}
1. g++ zad2.c 
2. ./a.out --type ${rodzaj sortowania:(insert;quick;merge)} --comp ${comparator:("<=";">=")} --stat ${nazwa_pliku} ${liczba_k}
    ./a.out --type merge --comp ">=" --stat statystyki 10
3. W trakcie działania programu wpisać liczbę całkowitą n czyli ilość elementów w tablicy, i podać liczby całkowite do posortowania. Jeżeli użyto --stat nie ma potrzeby podawania żadnych danych.

_______________________________________________________

### Zadanie3
Działa tak samo jak zad2 ale w parametrze --type można użyć parametru dual uruchamiającego Dual Pivot QuickSort i hybrid uruchamiającego hybrydowego Merge Sort-a.
1. g++ zad3.c 
2. ./a.out --type ${rodzaj sortowania:(insert;quick;merge;hybrid;dual)} --comp ${comparator:("<=";">=")} --stat ${nazwa_pliku} ${liczba_k}
    ./a.out --type hybrid --comp "<=" --stat HybridMerge_k1000 1000
3. W trakcie działania programu wpisać liczbę całkowitą n czyli ilość elementów w tablicy, i podać liczby całkowite do posortowania. Jeżeli użyto --stat nie ma potrzeby podawania żadnych danych.

Stała przed O(n*log(n)) dla QuickSort: 1,37; dla DualPivotQuicksort: 1,05

_______________________________________________________

### Zadanie4
Działa tak samo jak zad3, ale ma dodatkowy parametr --data ${typ danych:(int;float;double;char)}
Algorytm hybrydowy jest połączeniem MergeSort-a i InsertionSort-a. Działa szybciej od wszyskich algorytmów poza DualPivotQuickSort-em.
1. g++ zad4.c 
2. ./a.out --type ${rodzaj sortowania:(insert;quick;merge;hybrid;dual)} --comp ${comparator:("<=";">=")} --stat ${nazwa_pliku} ${liczba_k} --data ${typ danych:(int;float;double;char)}
    ./a.out --type hybrid --comp "<=" --stat HybridMerge_k1000 1000 --data int
3. W trakcie działania programu wpisać liczbę całkowitą n czyli ilość elementów w tablicy, i podać liczby całkowite do posortowania. Jeżeli użyto --stat nie ma potrzeby podawania żadnych danych. Jeżeli nie poda się typu danych program ustawi typ na int.

W folderze wykresy jest kilka wykresów wygenerowanych programem napisanym w pythonie.
