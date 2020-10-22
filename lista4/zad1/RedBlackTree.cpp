//
// Created by erthax on 08.05.2020.
//

#include "DataStructure.h"

struct rbtNode
{
    rbtNode(std::string value): key(value), left(NULL), right(NULL), p(NULL), color(RED) {}
    ~rbtNode() {
        delete left;
        delete right;
    }
    std::string key;
    Color color; // 1 - red, 2 - black
    rbtNode *p, *left, *right;
};

rbtNode* RedBlackTree::newNodeRbt(std::string val)
{
    rbtNode *n = new rbtNode(val);
    n->p = this->NIL;
    n->left = this->NIL;
    n->right = this->NIL;
    return n;
}

RedBlackTree::RedBlackTree() {
    this->size = 0;
    rbtNode* NIL = new rbtNode("\0");
    NIL->color = BLACK;
    NIL->p = NIL;
    NIL->left = NIL;
    NIL->right = NIL;
    this->NIL = NIL;
    this->root = this->NIL;
}
RedBlackTree::~RedBlackTree() {
    delete this->root;
    delete this->NIL;
}

void RedBlackTree::insert(std::string val){
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
    insertRbt(val);
    this->size++;
}

int RedBlackTree::load(std::string fileName){
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

void RedBlackTree::find(std::string val) {
    rbtNode* node = searchRbt(val);
    if(node->key == val)
        std::cout<<"1"<<std::endl;
    else
        std::cout<<"0"<<std::endl;
}

void RedBlackTree::min() {
    rbtNode* y = minRbt(this->root);
    if(y == this->NIL)
        std::cout<<std::endl;
    else
        std::cout<<y->key<<std::endl;
}

void RedBlackTree::max() {
    rbtNode* y = maxRbt(this->root);
    if(y == this->NIL)
        std::cout<<std::endl;
    else
        std::cout<<y->key<<std::endl;
}

void RedBlackTree::successor(std::string val) {
    rbtNode* x = searchRbt(val);
    if(x == this->NIL)
        std::cout<<std::endl;
    else
        std::cout<<x->key<<std::endl;
}

void RedBlackTree::del(std::string val) {
    this->deleteRbt(val);
}

void RedBlackTree::inorder() {
    inorderRbt(this->root);
    std::cout << std::endl;
}

void RedBlackTree::pprint() {
    printRbt("", this->root, false);
}

void RedBlackTree::left_rotate(rbtNode *x)
{
    rbtNode *y = x->right;
    x->right = y->left;
    if (y->left != this->NIL)
        y->left->p = x;
    y->p = x->p;
    if (x->p == this->NIL)
        this->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void RedBlackTree::right_rotate(rbtNode *y)
{
    rbtNode *x = y->left;
    y->left = x->right;
    if (x->right != this->NIL)
        x->right->p = y;
    x->p = y->p;
    if (y->p == this->NIL)
        this->root = x;
    else if (y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;
    x->right = y;
    y->p = x;
}

rbtNode *RedBlackTree::searchRbt(std::string k)
{
    rbtNode *x = this->root;
    while (x != this->NIL && k != x->key)
    {
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

void RedBlackTree::fix_after_insert(rbtNode *z)
{
    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            rbtNode *y = z->p->p->right;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->right)
                {
                    z = z->p;
                    left_rotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(z->p->p);
            }
        }
        else
        {
            rbtNode *y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;
                    right_rotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(z->p->p);
            }
        }
    }
    this->root->color = BLACK;
}

void RedBlackTree::insertRbt(std::string val)
{
    rbtNode *z = newNodeRbt(val);
    rbtNode *y = this->NIL;
    rbtNode *x = this->root;
    while (x != this->NIL)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if (y == this->NIL)
        this->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = this->NIL;
    z->right = this->NIL;
    z->color = RED;
    fix_after_insert(z);
}

void RedBlackTree::transplant(rbtNode *u, rbtNode *v)
{
    if (u->p == this->NIL)
        this->root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    v->p = u->p;
}

rbtNode *RedBlackTree::tree_min(rbtNode *n)
{
    while (n->left != this->NIL)
        n = n->left;
    return n;
}

void RedBlackTree::fix_after_delete(rbtNode *x)
{
    while (x != this->root && x->color == BLACK)
    {
        if (x == x->p->left)
        {
            rbtNode *w = x->p->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(x->p);
                x = this->root;
            }
        }
        else
        {
            rbtNode *w = x->p->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(x->p);
                w = x->p->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(x->p);
                x = this->root;
            }
        }
    }
    x->color = BLACK;
}

void RedBlackTree::deleteRbt(std::string val)
{
    rbtNode* z = searchRbt(val);
    if(z != this->NIL)
        this->size--;
    rbtNode *y = z, *x, *deleted_node_p = z->p;
    Color y_color = y->color;
    if (z->left == this->NIL)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == this->NIL)
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = tree_min(z->right);
        y_color = y->color;
        x = y->right;
        if (y->p == z)
        {
            x->p = y;
        }
        else
        {
            deleted_node_p = y->p;
            transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
        deleted_node_p = y;
    }
    if (y_color == BLACK)
        fix_after_delete(x);
}

void RedBlackTree::printRbt(const std::string &prefix, const rbtNode *node, bool isLeft)
{
    if (node != this->NIL)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::cout << node->key << (node->color ? "B" : "R")<< std::endl;

        // enter the next tree level - left and right branch
        printRbt(prefix + (isLeft ? "│   " : "    "),node->left, true);
        printRbt(prefix + (isLeft ? "│   " : "    "),node->right, false);
    }
}

void RedBlackTree::inorderRbt(rbtNode *x) {
    if(x != this->NIL){
        inorderRbt(x->left);
        std::cout << x->key << " ";
        inorderRbt(x->right);
    }
}


rbtNode* RedBlackTree::minRbt(rbtNode* x){
    while(x->left != this->NIL)
        x = x->left;
    return x;
}

rbtNode* RedBlackTree::maxRbt(rbtNode* x){
    while(x->right != this->NIL)
        x = x->right;
    return x;
}