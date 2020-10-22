//
// Created by erthax on 08.05.2020.
//
#include <typeinfo>
#include "DataStructure.h"

HashMap::HashMap() {
    this->size = 0;
}


void HashMap::insert(std::string val){
    int i;
    for(i = 0; i < val.size()-1; i++){
        if((val[i] >= 'a' && val[i] <= 'z') || (val[i] >= 'A' && val[i] <= 'Z')){
            break;
        }
    }
    val.std::string::erase(0,i);
    for(i = val.size()-1; i >= 0; i--){
        if((val[i] >= 'a' && val[i] <= 'z') || (val[i] >= 'A' && val[i] <= 'Z')){
            break;
        }
    }
    val = val.std::string::erase(i+1,val.size()-(i+1));
    insertHash(val);
}

int HashMap::load(std::string fileName){
    int inserts = 0;
    std::ifstream inputFile(fileName);
    std::string inputString;
    while(inputFile >> inputString){
        this->insert(inputString);
        inserts++;
    }
    inputFile.close();
    return inserts;
}

void HashMap::find(std::string val) {
    unsigned long hash = makeHash(val);
    this->map[hash]->find(val);
}

void HashMap::min() {
    std::cout<<std::endl;
}

void HashMap::max() {
    std::cout<<std::endl;
}

void HashMap::successor(std::string val) {
    std::cout<<std::endl;
}

void HashMap::del(std::string val) {
    unsigned long hash = makeHash(val);
    this->map[hash]->del(val);
}

void HashMap::inorder() {
    std::cout<<std::endl;
}

void HashMap::pprint() {
    std::cout<<std::endl;
}

void HashMap::insertHash(std::string val) {
    unsigned long hash = makeHash(val);
    std::map<unsigned long, DataStructure*>::iterator it = this->map.find(hash);
    if ( it == map.end() ) {
        this->map[hash] = new LinkedList();
        this->map[hash]->insert(val);
    } else {
        if((this->map[hash])->isLinkedList() && this->map[hash]->getSize() >= 32){ //to jest nasze n dla ktorego przechodzimy na drzewo
            RedBlackTree* rbt = this->transformToRbt(this->map[hash]);
            rbt->insert(val);
            (this->map[hash]) = rbt;
        } else {
            this->map[hash]->insert(val);
        }
    }
}

unsigned long HashMap::makeHash(std::string val){
    return (this->myHash(val))%827;
}

int HashMap::getSize() {
    int size = 0;
    std::map<unsigned long, DataStructure*>::iterator it;
    for(it = this->map.begin(); it != this->map.end(); it++){
        size+= (it->second)->getSize();
    }
    return size;
}

RedBlackTree* HashMap::transformToRbt(DataStructure* list){
    std::vector<std::string> result = list->getValues();
    RedBlackTree* rbt = new RedBlackTree();
    for(int i = 0; i < result.size(); i++){
        rbt->insert(result[i]);
    }
    return rbt;
}