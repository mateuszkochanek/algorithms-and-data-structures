//
// Created by erthax on 10.05.2020.
//
#include <iostream>
#include <iomanip>
#include "DataStructure.h"

int main(int argc, char *argv[]) {
    std::string word[10];
    double timeBst[8],timeRbt[8],timeHmap[8];
    std::string print[8] = {"load","insert","find","inorder","max","min","succesor","delete"};
    clock_t start_t, end_t;
    double timeSecInsert, timeSecFind;
    BinarySearchTree *bst = new BinarySearchTree();
    RedBlackTree *rbt = new RedBlackTree();
    HashMap *hmap = new HashMap();
    std::ifstream input("english.txt");
    std::ofstream output("results_test2.txt");
    //BST________________________________
    //LOAD_______________________________________________________________________________________
    start_t = clock(); // load time
    bst->load("sample.txt");
    end_t = clock();
    timeBst[0] = (double)(end_t - start_t) / (double)(CLOCKS_PER_SEC);
    //INSERT_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        input >> word[i];
        bst->insert(word[i]);
    }
    end_t = clock();
    timeBst[1] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //FIND_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        bst->find(word[i]);
    }
    end_t = clock();
    timeBst[2] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //INORDER_______________________________________________________________________________________
    start_t = clock(); // load time
        bst->inorder();
    end_t = clock();
    timeBst[3] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //MAX_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        bst->max();
    }
    end_t = clock();
    timeBst[4] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //Min_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        bst->min();
    }
    end_t = clock();
    timeBst[5] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //SUCCESSOR_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        bst->successor(word[i]);
    }
    end_t = clock();
    timeBst[6] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //DELETE_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        bst->del(word[i]);
    }
    end_t = clock();
    timeBst[7] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;


    //RBT________________________________
    //LOAD_______________________________________________________________________________________
    start_t = clock(); // load time
    rbt->load("sample.txt");
    end_t = clock();
    timeRbt[0] = (double)(end_t - start_t) / (double)(CLOCKS_PER_SEC);
    //INSERT_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        input >> word[i];
        rbt->insert(word[i]);
    }
    end_t = clock();
    timeRbt[1] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //FIND_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        rbt->find(word[i]);
    }
    end_t = clock();
    timeRbt[2] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //INORDER_______________________________________________________________________________________
    start_t = clock(); // load time
    rbt->inorder();
    end_t = clock();
    timeRbt[3] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //MAX_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        rbt->max();
    }
    end_t = clock();
    timeRbt[4] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //Min_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        rbt->min();
    }
    end_t = clock();
    timeRbt[5] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //SUCCESSOR_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        rbt->successor(word[i]);
    }
    end_t = clock();
    timeRbt[6] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //DELETE_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        rbt->del(word[i]);
    }
    end_t = clock();
    timeRbt[7] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //HMAP_______________________________
    //LOAD_______________________________________________________________________________________
    start_t = clock(); // load time
    hmap->load("sample.txt");
    end_t = clock();
    timeHmap[0] = (double)(end_t - start_t) / (double)(CLOCKS_PER_SEC);
    //INSERT_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        input >> word[i];
        hmap->insert(word[i]);
    }
    end_t = clock();
    timeHmap[1] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //FIND_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        hmap->find(word[i]);
    }
    end_t = clock();
    timeHmap[2] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //INORDER_______________________________________________________________________________________
    start_t = clock(); // load time
    hmap->inorder();
    end_t = clock();
    timeHmap[3] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //MAX_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        hmap->max();
    }
    end_t = clock();
    timeHmap[4] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //Min_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        hmap->min();
    }
    end_t = clock();
    timeHmap[5] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //SUCCESSOR_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        hmap->successor(word[i]);
    }
    end_t = clock();
    timeHmap[6] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;
    //DELETE_______________________________________________________________________________________
    start_t = clock(); // load time
    for(int i = 0; i <10; i++){
        hmap->del(word[i]);
    }
    end_t = clock();
    timeHmap[7] = ((double)(end_t - start_t) / (double)(CLOCKS_PER_SEC))/10.0;

    for(int i = 0; i<8; i++){
        output<<std::fixed<<std::setprecision(6) <<print[i]<<": | BST:"<<timeBst[i] << " | RBT:"<<timeRbt[i]<<" | HMAP:"<<timeHmap[i]<<std::endl;
    }

    return 0;
}