#pragma once
#ifndef Node_H
#define Node_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct AVL_Node
{
	AVL_Node * parent;
	AVL_Node * left;
	AVL_Node * right;
	int key;
	int bf;
};
#endif
