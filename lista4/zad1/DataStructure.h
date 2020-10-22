//
// Created by erthax on 09.05.2020.
//

#ifndef ZAD1_DATASTRUCTURE_H
#define ZAD1_DATASTRUCTURE_H
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <vector>

class DataStructure {
public:
    virtual void insert(std::string val)=0;
    virtual void find(std::string val)=0;
    virtual void min()=0;
    virtual void max()=0;
    virtual void successor(std::string val)=0;
    virtual int load(std::string fileName)=0;
    virtual void del(std::string val)=0;
    virtual void inorder()=0;
    virtual void pprint()=0;
    virtual int getSize()=0;
    virtual bool isLinkedList()=0;
    virtual std::vector<std::string> getValues()=0;

protected:
    int size;
};

struct bstNode;
class BinarySearchTree: public DataStructure {
private:
    bstNode* root;
    bstNode* NIL;
    bstNode *newNodeBst(std::string val);
    void insertBst(std::string val);
    void transplantBst(bstNode* u, bstNode* v);
    bstNode* findBst(bstNode* x, std::string val);
    bstNode * minBst(bstNode* x);
    bstNode * maxBst(bstNode* x);
    void inorderBst(bstNode* x);
    bstNode * successorBst(bstNode* x);
    void prettyPrint(const std::string &prefix, const bstNode *node, bool isLeft);
public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insert(std::string val);
    void find(std::string val);
    void min();
    void max();
    void successor(std::string val);
    int load(std::string fileName);
    void del(std::string val);
    void inorder();
    void pprint();
    int getSize(){ return size; }
    bool isLinkedList(){ return false; }
    std::vector<std::string> getValues(){ return std::vector<std::string> (0); };

    void deleteBst(std::string val);
};

enum Color
{
    RED,
    BLACK
};
struct rbtNode;
class RedBlackTree: public DataStructure {
private:
    rbtNode* root;
    rbtNode* NIL;
    rbtNode* newNodeRbt(std::string val);
    void left_rotate(rbtNode *x);
    void right_rotate(rbtNode *y);
    rbtNode *searchRbt(std::string k);
    void fix_after_insert(rbtNode *z);
    void insertRbt(std::string val);
    void transplant(rbtNode *u, rbtNode *v);
    rbtNode *tree_min(rbtNode *n);
    void fix_after_delete(rbtNode *x);
    void inorderRbt(rbtNode *x);
    void printRbt(const std::string &prefix, const rbtNode *node, bool isLeft);
    rbtNode* minRbt(rbtNode* x);
    rbtNode* maxRbt(rbtNode* x);
    void deleteRbt(std::string val);
public:
    RedBlackTree();
    ~RedBlackTree();
    void insert(std::string val);
    void find(std::string val);
    void min();
    void max();
    void successor(std::string val);
    int load(std::string fileName);
    void del(std::string val);
    void inorder();
    void pprint();
    int getSize(){ return size; }
    bool isLinkedList(){ return false; }
    std::vector<std::string> getValues(){ return std::vector<std::string> (0); };
};

struct listNode;
class LinkedList: public DataStructure {
public:
    LinkedList();
    ~LinkedList();
    void insert(std::string val);
    void find(std::string val);
    void min();
    void max();
    void successor(std::string val);
    int load(std::string fileName);
    void del(std::string val);
    void inorder();
    void pprint();
    bool isLinkedList(){ return true; }
    std::vector<std::string> getValues();

private:
    listNode* head;
    listNode* newNodeList(std::string val);
    void insertList(std::string val);
    void deleteList(std::string val);
    listNode* findList(std::string val);
    int getSize(){ return size; }
};

class HashMap: public DataStructure {
public:
    HashMap();
    void insert(std::string val);
    void find(std::string val);
    void min();
    void max();
    void successor(std::string val);
    int load(std::string fileName);
    void del(std::string val);
    void inorder();
    void pprint();
    int getSize();
    bool isLinkedList(){ return false; }
    std::vector<std::string> getValues(){ return std::vector<std::string> (0); };
private:
    std::hash<std::string> myHash;
    std::map<unsigned long,DataStructure*> map;
    void insertHash(std::string val);
    unsigned long makeHash(std::string val);
    RedBlackTree* transformToRbt(DataStructure* list);
};
#endif //ZAD1_DATASTRUCTURE_H
