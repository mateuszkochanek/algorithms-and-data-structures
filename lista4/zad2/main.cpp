#include <iostream>
#include <time.h>
#include <iomanip>
#include <vector>
#include "DataStructure.h"

using namespace std;


int main(int argc, char *argv[]) {
    clock_t start_t, end_t;
    unsigned long minComp, maxComp, medComp = 0, currComp;
    std::string word;
    std::string fileName = "english.txt"; //ts1.txt < test dla lotra | english.txt < test dla slownika
    int n = 0;
    BinarySearchTree *bst = new BinarySearchTree();
    RedBlackTree *rbt = new RedBlackTree();
    HashMap *hmap = new HashMap;
    ifstream input(fileName); //lotr
    ofstream output("zad2_results.txt");

    //BST
    bst->load(fileName);
    input >> word;
    currComp = bst->find(word);
    minComp = currComp;
    maxComp = currComp;
    medComp += currComp;
    n++;
    while(input >> word){
        currComp = bst->find(word);
        minComp = min(currComp,minComp);
        maxComp = max(currComp,maxComp);
        medComp += currComp;
        n++;
    }
    output << std::fixed << std::setprecision(6) << "Ograniczenia dla drzewa Bst | Dolne: " << minComp << " | Średnie: " << medComp/(n) << " | Górne: " << maxComp << std::endl;
    input.close();
    //RBT
    input.open(fileName);
    medComp = 0;
    n=0;
    rbt->load(fileName);
    input >> word;
    currComp = rbt->find(word);
    minComp = currComp;
    maxComp = currComp;
    medComp += currComp;
    n++;
    while(input >> word){
        currComp = rbt->find(word);
        minComp = min(currComp,minComp);
        maxComp = max(currComp,maxComp);
        medComp += currComp;
        n++;
    }
    output << std::fixed << std::setprecision(6) << "Ograniczenia dla drzewa Rbt | Dolne: " << minComp << " | Średnie: " << medComp/(n) << " | Górne: " << maxComp << std::endl;
    input.close();
    //HMAP
    medComp = 0;
    input.open(fileName);
    hmap->load(fileName);
    input >> word;
    currComp = hmap->find(word);
    minComp = currComp;
    maxComp = currComp;
    medComp += currComp;
    n++;
    while(input >> word){
        currComp = hmap->find(word);
        minComp = min(currComp,minComp);
        maxComp = max(currComp,maxComp);
        medComp += currComp;
        n++;
    }
    output << std::fixed << std::setprecision(6) << "Ograniczenia dla Hash Mapy | Dolne: " << minComp << " | Średnie: " << medComp/(n) << " | Górne: " << maxComp << std::endl;
    input.close();
    output.close();
    return 0;
}
