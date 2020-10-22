//
// Created by erthax on 09.05.2020.
//

#include "DataStructure.h"

struct listNode {
    listNode(std::string value): key(value), prev(nullptr), next(nullptr){}
    std::string key;
    listNode *prev, *next;
};

listNode* LinkedList::newNodeList(std::string val)
{
    listNode *n = new listNode(val);
    return n;
}

LinkedList::LinkedList() {
    this->size = 0;
    this->head = nullptr;
}
LinkedList::~LinkedList() {
    listNode* node = this->head;
    listNode* next;
    while(node != nullptr){
        next = node->next;
        delete node;
        node = next;
    }
}

void LinkedList::insert(std::string val){
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
    insertList(val);
    this->size++;
}

int LinkedList::load(std::string fileName){
    int inputs = 0;
    std::ifstream inputFile(fileName);
    std::string inputString;
    while(inputFile >> inputString){
        this->insert(inputString);
        inputs++;
    }
    inputFile.close();
    return inputs;
}

int LinkedList::find(std::string val) {
    int comp = findList(val);
    return comp;
}

void LinkedList::del(std::string val) {

}

void LinkedList::min() {
        std::cout<<std::endl;
}

void LinkedList::max() {
        std::cout<<std::endl;
}

void LinkedList::successor(std::string val) {
        std::cout<<std::endl;
}

void LinkedList::inorder() {
    std::cout<<std::endl;
}

void LinkedList::insertList(std::string val) {

    if(this->head == nullptr){
        listNode* node = new listNode(val);
        this->head = node;
    } else {
        listNode* node = new listNode(val);
        node->next = this->head;
        this->head->prev = node;
        this->head = node;
    }
}

int LinkedList::findList(std::string val) {
    int comp = 0;
    if(this->head == nullptr){
        return 0;
    } else {
        listNode* node = this->head;
        while(node != nullptr){
            comp++;
            if(node->key == val){
                return comp;
            }
            node = node->next;
        }
        return comp;
    }
}

void LinkedList::pprint() {
    if(this->head == nullptr){
        std::cout<<"NULL";
    } else {
        listNode* node = this->head;
        while(node != nullptr){
            std::cout<<node->key<<" ";
            node = node->next;
        }
        std::cout<<std::endl;
    }
}

std::vector<std::string> LinkedList::getValues(){
    std::vector<std::string> result;
    listNode* node = this->head;
    while(node != nullptr){
        result.push_back(node->key);
        node = node->next;
    }
    return result;
}