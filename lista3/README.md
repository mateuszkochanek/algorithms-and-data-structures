1.Zadanie1
Ma zrobione 6 algorytmów sortujących, insert, merge, quick, hybrid, dual oraz radix sort. Aby je uruchomić należy wpisać:
a) g++ zad1.cpp
b) ./a.out --type ${rodzaj sortowania:(insert;quick;merge;hybrid;dual;radix)} --comp ${comparator:("<=";">=")} --stat ${nazwa_pliku} ${liczba_k}
    ./a.out --type radix --comp "<=" --stat Radix_k1000 1000
c) W trakcie działania programu wpisać liczbę całkowitą n czyli ilość elementów w tablicy, i podać liczby całkowite do
posortowania. Jeżeli użyto --stat nie ma potrzeby podawania żadnych danych
Implementacja radix sorta jest na dole pliku.

Łatwo zauważyć, że radix sort ma w odpowiednim przedziale danych mniejszy czas działania i wykonuje mniej operacji niż inne
sortowania w programie. Jednak przedział danych w tablicy ma bardzo duży wplyw na to jak szybko sortuje radix sort, im mniej cyfr
ma największa liczba w tablicy którą sortujemy tym stosunkowo mniejszy będzie czas sortowania. Dlatego uważam że radix sort jest
dużo mniej uniwersalnym sortowaniem.
Warto wspomnieć też, że radix sort jako jedyny z zaimplementowanych nie jest sortowaniem w miejscu, a dystrybucyjnym, dlatego używa
więcej pamięci niż pozostałe.
____________________________________________________________________
2.Zadanie2
Zaimplementowany algorytm SELECT oraz RANDOMIZED SELECT. Aby je uruchomić należy wpisać:
a) g++ zad2.cpp
b) ./a.out ${rodzaj danych:(-r;-p)} (-r oznacza losowe dane, -p oznacza losową permutację {1,2,3...n}
    ./a.out -r
c) W trakcie działania programu wpisać liczbę całkowitą n czyli ilość elementów w tablicy i liczbę całkowitą k, czyli ktora liczbę
z kolei chcemy znaleźć. Wybrana liczba będzie oznaczona dwoma nawiasami np. [10].

Kilka przykładowych wywołań programu testującego, liczącego min i max liczbę porównan, a takze srędnią i odchylenie standardowe dla
tablic o dlugosci n = {100,200,...,10000}:

Dla RANDOM_SELECT | min: 120 | max: 54826 | średnia: 12165.4 | odchylenie: 9402.56 | średnni czas w ms: 0.0658114
Dla SELECT | min: 996 | max: 150439 | średnia: 73631.9 | odchylenie: 43244.4 | średni czas w ms: 0.292566

Dla RANDOM_SELECT | min: 102 | max: 49769 | średnia: 12233.8 | odchylenie: 8978.17 | średnni czas w ms: 0.074468
Dla SELECT | min: 931 | max: 152842 | średnia: 73983.5 | odchylenie: 43721 | średni czas w ms: 0.334165

Widać że RANDOM_SELECT ma średnio lepsze wyniki niż SELECT. Natomiast pesymistyczny czas wykonania randomized selecta jest rzędu
kwadratowego a w selecie liniowego. To którego algorytmu powinniśmy użyć zależy więc od informacji jakie mamy o danych.RANDOMIZED
SELECT jest bardziej uniwersalny.
____________________________________________________________________
3.Zadanie3
Zaimplementowany algorytm Binary search. Aby go uruchomić należy wpisać:
a) g++ zad3.cpp
b) ./a.out
c) W trakcie działania programu wpisać liczbę całkowitą n czyli ilość elementów w tablicy, liczbę całkowitą k, czyli ktorą liczbę
chcemy znaleźć i niemalejącą tablicę elementów wielkości n.
Program wypisze czy tą liczbę znaleziono w tabilcy, a nstępnie przeprowadzi testy dla n ∈ {1000, 2000, . . . , 100000} i wypisze
ich wyniki, dlatego wyniku wyszukania należy szukać na górze programu zaraz pod wywołaniem.

Używając Master Theorem wiem, że złożoność czasowa i porównań wyszukiwania binarnego to O(log_2 n). Jeżeli każde przejscie po
fukcji binary search liczymy jako jedno porównanie, to wyniki są bardzo zbliżone do właśnie log_2 n tzn. że rzeczywista liczba
porownań tak liczonych jest bardzo podobna do log_2 n. Jednak porównań w funkcji jest wiecej, konkretniej 3, jeżeli tak policzymy
liczbę porównań rząd oczywiście się nie zmieni, natomiast stała O(1) to 3 zamiast 1 więc liczba porownań będzie zdecydowanie
większa niż log_2 n, jednak wciąż tego samego rzędu.
____________________________________________________________________
4.Zadanie4
Ma zaprogramowane 4 algorytmy sortujących, quick sort, dual quick sort, quick sort z selectem i dual quick sort z selectem.
a) g++ zad4.cpp
b) ./a.out --type ${rodzaj sortowania:(quick;dual;quickv2;dualv2)} --comp ${comparator:("<=";">=")} --stat ${nazwa_pliku} ${liczba_k}
    ./a.out --type dual --comp "<=" --stat Dual_k1000 1000
c) W trakcie działania programu wpisać liczbę całkowitą n czyli ilość elementów w tablicy, i podać liczby całkowite do
posortowania. Jeżeli użyto --stat nie ma potrzeby podawania żadnych danych, testy zostaną wpisane do podanego pliku.

Quicksort używa SELECTA do wyznaczenia mediany_median i używa jej jako pivota. Dual Quicksort używa selecta do wyznaczenia median
dzielących tablicę na w miarę równe trzy części, i ich używa jako pivotów.
Tego typu implementacje tych sortowań zabezpieczają nas przed najgorszym przypadkiem sortowania który w normalnym quicksorcie
powoduje czas wykonania rzędu O(n^2) u nas będzie rzędu O(nlog_2 n). Niestety tego typu rozwiązanie jest mało praktyczne, bo mimo,
że w rozważaniach teoretycznych licząc rzędy funkcji nie widać problemu, to w rzeczywistości stałe jakie dodaje nam liczenie median
są tak duże, że to rozwiązanie jest zazwyczaj nieoptymalne w praktyce.

