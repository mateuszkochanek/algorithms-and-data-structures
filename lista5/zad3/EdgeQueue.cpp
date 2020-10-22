//
// Created by erthax on 06.06.2020.
//
#include "Structures.h"

EdgeQueue::EdgeQueue(){

}

int EdgeQueue::parent(int i) {
    return floor((i-1)/2);
}

int EdgeQueue::left(int i) {
    return 2*i+1;
}

int EdgeQueue::right(int i) {
    return 2*i+2;
}

void EdgeQueue::heapify(int i) {
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
        EdgeElement* e = this->heap[i];
        this->heap[i] = this->heap[smallest];
        this->heap[smallest] = e;
        heapify(smallest);
    }
}

void EdgeQueue::insert(Edge* x, double p) {
    int i;
    EdgeElement* e = new EdgeElement(x,p);
    this->heap.push_back(e);
    i = this->heap.size()-1;
    while(i > 0 && this->heap[parent(i)]->p > p){
        this->heap[i] = this->heap[parent(i)];
        i = parent(i);
    }
    this->heap[i] = e;
}

bool EdgeQueue::empty() {
    if(this->heap.empty()){
        return true;
    } else {
        return false;
    }
}

Edge* EdgeQueue::pop() {
    if(this->heap.empty()){
        std::cout<<std::endl;
    } else {
        EdgeElement* min = this->heap[0];
        this->heap[0] = this->heap[this->heap.size()-1];
        this->heap.pop_back();
        if(!this->empty())
            heapify(0);
        return min->v;
    }
}

void EdgeQueue::priority(Edge* v, double p) {
    for (int i = 0; i < this->heap.size(); i++) {
        if (this->heap[i]->v == v && this->heap[i]->p > p) {
            this->heap[i]->p = p;
            this->decreaseKey(i);
        }
    }
}

void EdgeQueue::decreaseKey(int i) {
    if (i >= this->heap.size())
        return;
    EdgeElement* temp = this->heap[i];
    while (i > 0 && this->heap[i / 2]->p > temp->p) {
        this->heap[i] = this->heap[i / 2];
        i /= 2;
    }
    this->heap[i] = temp;
}


