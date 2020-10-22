//
// Created by erthax on 10.05.2020.
//
#include <iostream>
#include <iomanip>
#include "DataStructure.h"

int main(int argc, char *argv[]) {
    std::string word;
    clock_t start_t, end_t;
    double timeSecInsert, timeSecFind;
    RedBlackTree *rbt;
    LinkedList *list;
    std::ifstream input("english.txt");
    std::ofstream output("results_test1.txt");
    for(int n = 1; n<=200; n++){
        std::string firstword;
        rbt = new RedBlackTree();
        list = new LinkedList();
        start_t = clock();
        for(int i = 0; i <n; i++){
            input >> word;
            if(i == 0)
                firstword = word;
            rbt->insert(word);
        }
        end_t = clock();
        timeSecInsert = (double)(end_t - start_t) / (double)(CLOCKS_PER_SEC);

        start_t = clock();
        rbt->find(firstword);
        end_t = clock();
        timeSecFind = (double)(end_t - start_t) / (double)(CLOCKS_PER_SEC);
        output <<std::fixed<<std::setprecision(6) <<"For n = "<< n <<" | Insert time in rbt: " << timeSecInsert << " | Find time in rbt: " << timeSecFind << std::endl;

        start_t = clock();
        for(int i = 0; i <n; i++){
            input >> word;
            if(i == 0)
                firstword = word;
            list->insert(word);
        }
        end_t = clock();
        timeSecInsert = (double)(end_t - start_t) / (double)(CLOCKS_PER_SEC);

        start_t = clock();
        list->find(firstword);
        end_t = clock();
        timeSecFind = (double)(end_t - start_t) / (double)(CLOCKS_PER_SEC);
        output <<"For n = "<< n <<" | Insert time in list: " << timeSecInsert << " | Find time in list: " << timeSecFind << std::endl;
    }


    return 0;
}