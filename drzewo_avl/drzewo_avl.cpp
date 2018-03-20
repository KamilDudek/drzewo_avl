#include <iostream>

using namespace std;

struct AVL_Node
{
	AVL_Node * parent;
	AVL_Node * left;
	AVL_Node * right;
	int key;
	int bf;
};

int makeEmpty(AVL_Node * temp)
{
	if (temp == NULL)
		return 0;
	makeEmpty(temp->left);
	makeEmpty(temp->right);
	delete temp; //zwalnianie pamieci przydzielonej dynamicznie
	return 0;
}

void RR(AVL_Node * root, AVL_Node * A)
{
	AVL_Node * B, *p; //p - przodek
	B = A->right;
	p = A->parent;
	if (A != NULL && A->right != NULL)
	{
		A->parent = B;
		B->parent = p;
		A->right = B->left;
		B->left = A;
	}

	if (p != NULL) {
		if (p->left == A) p->left = B;
		else p->right = B;
	}
	else root = B;
}



void LL(AVL_Node * root, AVL_Node * A)
{
	AVL_Node *B, *p; //p - przodek
	B = A->left;
	p = A->parent;

	if (A != NULL && A->left != NULL)
	{
		A->parent = B;
		B->parent = p;
		A->left = B->right;
		B->right = A;
	}
	if (p != NULL)
	{
		if (p->left == A) //sprawdzamy czy A jest lewym badz prawym dzieckiem
			p->left = B;
		else p->right = B;
	}
	else
		root = B;
}
void height(AVL_Node *root, int *h, int level)
{
	if (root)
	{
		if (root->right)
		{
			level++;
			height(root->right, h, level);
			level--;
		}
		if (level>*h) *h = level;

		if (root->left)
		{
			level++;
			height(root->left, h, level);
			level--;
		}
	}
}

void Bf(AVL_Node *temp)
{
	int iL = 0;		//lewa galaz
	int iR = 0;		// prawa galaz

	AVL_Node *x = temp, *y = x->left, *z = x->right;

	if (y != NULL)
		height(y, &iL, 1);
	if (z != NULL)
		height(z, &iR, 1);

	x->bf = iL - iR; //obliczanie bf
}

//void AVL_Node(AVL_Node *root,AVL_Node*temp)
//{
//	avl_node *temp;
//	temp = parent->left;
//	parent->left = RR(temp);
//	return LL(parent);
//}1

/*
void RL(AVL_Node *root, *A)
{
AVL_Node *p, *B;


}
*/
int main()
{
	cout << "hello world" << endl;
	getchar();
	return 0;
}