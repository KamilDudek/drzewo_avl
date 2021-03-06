#pragma once

#ifndef AVLTree_H
#define AVLTree_H
#include "Node.h"

using namespace std;

void printBT(string, string, AVL_Node *, string cr, string cp, string cl);
void DFSRelease(AVL_Node *);
AVL_Node *postorder(AVL_Node *);
AVL_Node *preorder(AVL_Node *);
void inorder(AVL_Node *);
void insertAVL(AVL_Node *&, int);
void RL(AVL_Node *&, AVL_Node *);
void LR(AVL_Node *&, AVL_Node *);
void LL(AVL_Node *&, AVL_Node *);
void RR(AVL_Node *&, AVL_Node *);
void height(AVL_Node *&);
void height(AVL_Node *&, int *, int);
void createTree(AVL_Node *&, int);
void Add(AVL_Node *&);
void Empty(AVL_Node *&);
#endif