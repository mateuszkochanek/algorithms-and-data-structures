//
// Created by erthax on 08.05.2020.
//

#include "DataStructure.h"

struct bstNode {
    bstNode(std::string value): key(value), left(NULL), right(NULL), p(NULL) {}
    std::string key;
    bstNode *p;
    bstNode *left;
    bstNode *right;
};

bstNode* BinarySearchTree::newNodeBst(std::string val){
    bstNode* node = new bstNode(val);
    node->p = this->NIL;
    node->left = this->NIL;
    node->right = this->NIL;
    return node;
}

BinarySearchTree::BinarySearchTree(){
    this->size = 0;
    bstNode* NIL = new bstNode("\0");
    NIL->p = NIL;
    NIL->left = NIL;
    NIL->right = NIL;
    this->NIL = NIL;
    this->root = this->NIL;
}

BinarySearchTree::~BinarySearchTree(){

}

void BinarySearchTree::insert(std::string val){
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
    insertBst(val);
    this->size++;
}

int BinarySearchTree::load(std::string fileName){
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

int BinarySearchTree::find(std::string val) {
    int comps = findBst(this->root,val);
    return comps;
}

void BinarySearchTree::min() {
    bstNode* y = minBst(this->root);
    if(y == this->NIL)
        std::cout<<std::endl;
    else
        std::cout<<y->key<<std::endl;
}

void BinarySearchTree::max() {
    bstNode* y = maxBst(this->root);
    if(y == this->NIL)
        std::cout<<std::endl;
    else
        std::cout<<y->key<<std::endl;
}

void BinarySearchTree::successor(std::string val) {

}

void BinarySearchTree::del(std::string val) {

}

void BinarySearchTree::inorder() {
    inorderBst(this->root);
    std::cout << std::endl;
}

void BinarySearchTree::pprint() {
    prettyPrint("", this->root, false);
}

void BinarySearchTree::insertBst(std::string val){
    bstNode* node = newNodeBst(val);
    bstNode* x = this->root;
    bstNode* y = this->NIL;
    while(x != this->NIL){
        y = x;
        if(node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    node->p = y;
    if(y == this->NIL)
        this->root = node;
    else if(node->key < y->key)
        y->left = node;
    else
        y->right = node;
}


void BinarySearchTree::transplantBst(bstNode* u, bstNode* v){
    if(u->p == this->NIL)
        this->root = v;
    else if(u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    if(v != this->NIL)
        v->p = u->p;
}

int BinarySearchTree::findBst(bstNode* x, std::string val){
    int comp = 1;
    while(x != this->NIL && val != x->key){
        if(val < x->key)
            x = x->left;
        else
            x = x->right;
        comp++;
    }
    return comp;
}

bstNode* BinarySearchTree::minBst(bstNode* x){
    while(x->left != this->NIL)
        x = x->left;
    return x;
}

bstNode* BinarySearchTree::maxBst(bstNode* x){
    while(x->right != this->NIL)
        x = x->right;
    return x;
}

bstNode* BinarySearchTree::successorBst(bstNode* x){
    if(x->right != this->NIL)
        return minBst(x->right);
    bstNode* y = x->p;
    while(y != this->NIL && x == y->right){
        x = y;
        y = y->p;
    }
    return y;
}

void BinarySearchTree::inorderBst(bstNode* x){
    if(x != this->NIL){
        inorderBst(x->left);
        std::cout << x->key << " ";
        inorderBst(x->right);
    }
}

void BinarySearchTree::prettyPrint(const std::string &prefix, const bstNode *node, bool isLeft){
    if (node != this->NIL)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::cout << node->key << std::endl;

        // enter the next tree level - left and right branch
        prettyPrint(prefix + (isLeft ? "│   " : "    "), node->left, true);
        prettyPrint(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}
