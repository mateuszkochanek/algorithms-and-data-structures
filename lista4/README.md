1.Zadanie1
Ma zrobione 3 struktury danych opisane w liście 4 razem z operacjami insert, find, min, max, successor, load, delete, inorder 
działającymi jak sprecyzowane w zadaniu. Aby uruchomić zadanie należy je skompilować (polecam użyć stworzonego przezemnie pliku
make. (dodałem dodatkową strukturę LinkedList bo jest wykorzystywana prze z hmap). W struktórach zachowujących kolejność,
stosuję kolejność leksykograficzną C++, czyli znaki [A...Z,a...z]. (plik main w lini 127 ma zakomentowaną instrukcje pprint,
czyli Pretty print, po odkomentowaniu dla bst i rbt zostanie wyświetlone w konsoli drzewo w łatwy do interpretacji sposób)

a) make
b) ./main --type ${rodzaj struktury:(bst;rbt;hmap;list)}
c) W trakcie działania programu wpisać liczbę całkowitą n czyli ilość instrukcji, i po kolei podawać instrukcje.

a) n dla HMAP:
w pliku results_test1.txt są wszystkie wyniki testu z pliku test1.cpp, ale po przeanalizowaniu ich moment dla n = 32;
For n = 32 | Insert time in rbt: 0.000044 | Find time in rbt: 0.000005
For n = 32 | Insert time in list: 0.000029 | Find time in list: 0.000006
Jest momentem po którym  drzewo czerwono czarne praktycznie zawsze daje lepszy lub taki sam wynik przy wyszukiwaniu. Długość
inserta zawsze jest większa niż w liście, miedzy innymi też przez dane (jest to słownik więc drzewo musi się często zmieniać). Natomiast operacji wstawiania w trakcie pracy programu używamy tylko raz, operacji find zazwyczaj używamy na strukturze
wielokrotnie. Dlatego uważam, że już dla wielkości danych w komórce równych 32 możemy zacząć używać RBT.

Jeżeli chodzi o m to w moim przypadku nie jest to problem bo używam mapy jako kontenera, więc nie rezerwuje od razu pamięci dla
wszystkich wartości hasha. Natomiast warto zwrócić uwagę że przy hashowaniu modularnym którego używam trzeba unikać pewnych wartości
dla m. Dobrymi wartościami dla m są liczby pierwsze dalekie potęgom 2. Założyłem sobie, że w mojej hash mapie rozwiązującej
konflikty metodą łańcuchową chce przechowywać okolo 900 komórek. Dlatego na m wybrałem 827.


b) Średnie czasy działania: (generowane przez plik test2.cpp)
load: | BST:0.000070 | RBT:0.000080 | HMAP:0.000130
insert: | BST:0.000002 | RBT:0.000001 | HMAP:0.000002
find: | BST:0.000005 | RBT:0.000003 | HMAP:0.000003
inorder: | BST:0.000001 | RBT:0.000001 | HMAP:0.000000
max: | BST:0.000002 | RBT:0.000002 | HMAP:0.000002
min: | BST:0.000002 | RBT:0.000002 | HMAP:0.000002
succesor: | BST:0.000003 | RBT:0.000003 | HMAP:0.000002
delete: | BST:0.000001 | RBT:0.000001 | HMAP:0.000001


____________________________________________________________________
2.Zadanie2
Mam zrobione 3 struktury danych opisane w liście 4 razem z operacjami find i load (inne mogą niedziałać bo zostały dopasowane aby
zwracać ilość porównań). Aby uruchomić zadanie należy je skompilować (polecam użyć stworzonego przezemnie pliku make.
(dodałem dodatkową strukturę LinkedList bo jest wykorzystywana prze z hmap).

W programie jest zmienna fileName, określa z którego pliku wczytujemy dane. Plik "english.txt" ma słownik, plik "ts1.txt"
ma książke Lord Of The Rings.
Wyniki są zapisywane w pliku "zad2_results.txt".

a) make
b) ./main
c) Program może pracować długo bo pliki są dość duże.

Wyniki dla słownika które analizowalem są w pliku "zad2_results_slownik.txt" a dla książki "zad2_results_ksiazka.txt", wyniki:
Slownik, 65197 słów: (brak powtórzeń, konkretna kolejność)
Ograniczenia dla drzewa Bst | Dolne: 1 | Średnie: 32599 | Górne: 65197
Ograniczenia dla drzewa Rbt | Dolne: 1 | Średnie: 15 | Górne: 29
Ograniczenia dla Hash Mapy | Dolne: 1 | Średnie: 2 | Górne: 32
Książka, 575230 słów: (dużo powtórzen, brak kolejności)
Ograniczenia dla drzewa Bst | Dolne: 2 | Średnie: 112 | Górne: 32519
Ograniczenia dla drzewa Rbt | Dolne: 1 | Średnie: 12 | Górne: 31
Ograniczenia dla Hash Mapy | Dolne: 1 | Średnie: 1 | Górne: 28

Łatwo z tego wywniąskować że:
Bst: Dolne ograniczenie to: O(1); Średnio n porównań; Górne ograniczenie to: O(n)
Rbt: Dolne ograniczenie to: O(1); Średnio log n porównań; Górne ograniczenie to: O(log n)
HashMap: Dolne ograniczenie to: O(1); Średnio 1 porównań; Górne ograniczenie to: O(log n)
(chociaż dla wystaczajaco dużego m górne ograniczenie HashMap-y moglo by być również O(1), natomiast wymaga to dużej ilości pamięci)
____________________________________________________________________



