//
// Created by erthax on 06.06.2020.
//
#include "Structures.h"

Queue::Queue(){

}

int Queue::parent(int i) {
    return floor((i-1)/2);
}

int Queue::left(int i) {
    return 2*i+1;
}

int Queue::right(int i) {
    return 2*i+2;
}

void Queue::heapify(int i) {
    int smallest;
    int l = left(i);
    int r = right(i);
    if (l <= this->heap.size()-1 && this->heap[l]->p < this->heap[i]->p){
        smallest = l;
    } else {
        smallest = i;
    }

    if (r <= this->heap.size()-1 && this->heap[r]->p < this->heap[smallest]->p){
        smallest = r;
    }

    if(smallest != i){
        Element* e = this->heap[i];
        this->heap[i] = this->heap[smallest];
        this->heap[smallest] = e;
        heapify(smallest);
    }
}

void Queue::insert(int x, int p) {
    int i;
    Element* e = new Element(x,p);
    this->heap.push_back(e);
    i = this->heap.size()-1;
    while(i > 0 && this->heap[parent(i)]->p > p){
        this->heap[i] = this->heap[parent(i)];
        i = parent(i);
    }
    this->heap[i] = e;
}

bool Queue::empty() {
    if(this->heap.empty()){
        std::cout<<"1"<<std::endl;
        return true;
    } else {
        std::cout<<"0"<<std::endl;
        return false;
    }
}

void Queue::top() {
    if(this->heap.empty()){
        std::cout<<std::endl;
    } else {
        std::cout<<this->heap[0]->value<<std::endl;
    }
}

void Queue::pop() {
    if(this->heap.empty()){
        std::cout<<std::endl;
    } else {
        std::cout<<this->heap[0]->value<<std::endl;
        Element* min = this->heap[0];
        this->heap[0] = this->heap[this->heap.size()-1];
        this->heap.pop_back();
        if(!this->heap.empty())
            heapify(0);
    }
}

void Queue::priority(int value, int p) {
    for (int i = 0; i < this->heap.size(); i++) {
        if (this->heap[i]->value == value && this->heap[i]->p > p) {
            this->heap[i]->p = p;
            this->decreaseKey(i);
        }
    }
}

void Queue::decreaseKey(int i) {
    if (i >= this->heap.size())
        return;
    Element* temp = this->heap[i];
    while (i > 0 && this->heap[i / 2]->p > temp->p) {
        this->heap[i] = this->heap[i / 2];
        i /= 2;
    }
    this->heap[i] = temp;
}
void Queue::print() {
    int size = this->heap.size();
    for(int i = 0; i<size; i++)
        std::cout<<"("<<this->heap[i]->value<<", "<<this->heap[i]->p<<")"<<std::endl;
}

