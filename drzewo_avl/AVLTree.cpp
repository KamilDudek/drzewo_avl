#include "AVLTree.h"

using namespace std;

void printBT(string sp, string sn, AVL_Node * v,string cr, string cp, string cl)
{
	string s;
	if (v)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		printBT(s + cp, cr, v->right, cr, cp, cl);

		s = s.substr(0, sp.length() - 2);
		cout << s << sn << v->key << ":" << v->bf << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		printBT(s + cp, cl, v->left, cr, cp, cl);
	}
}

void DFSRelease(AVL_Node * v)
{
	if (v!=NULL)
	{
		DFSRelease(v->left);   // usuwamy lewe poddrzewo
		v->left = NULL;
		DFSRelease(v->right);  // usuwamy prawe poddrzewo
		v->right = NULL;
		delete v;              // usuwamy sam w?ze?
	}
}

void RR (AVL_Node * & root, AVL_Node * A)
{
	AVL_Node * B = A->right, *p = A->parent;

	A->right = B->left;
	if (A->right) A->right->parent = A;

	B->left = A;
	B->parent = p;
	A->parent = B;

	if (p)
	{
		if (p->left == A) p->left = B; else p->right = B;
	}
	else root = B;

	if (B->bf == -1) A->bf = B->bf = 0;
	else
	{
		A->bf = -1; B->bf = 1;
	}
}
void LL(AVL_Node * & root, AVL_Node * A)
{
	AVL_Node * B = A->left, *p = A->parent;

	A->left = B->right;
	if (A->left) A->left->parent = A;

	B->right = A;
	B->parent = p;
	A->parent= B;

	if (p)
	{
		if (p->left == A) p->left = B; else p->right = B;
	}
	else root = B;

	if (B->bf == 1) A->bf = B->bf = 0;
	else
	{
		A->bf = 1; B->bf = -1;
	}
}


void height(AVL_Node *&root)
{
	int *h = new int(0);
	height(root, h, 0);
	cout << *h;

}

void height(AVL_Node *&root, int *h, int level)
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

void LR(AVL_Node *&root, AVL_Node  *A)
{
	AVL_Node * B = A->left, *C = B->right, *p = A->parent;

	B->right = C->left;
	if (B->right) B->right->parent = B;

	A->left = C->right;
	if (A->left) A->left->parent = A;

	C->right = A;
	C->left = B;
	A->parent = B->parent = C;
	C->parent = p;

	if (p != NULL)
	{
		if (p->left == A) p->left = C; else p->right = C;
	}
	else root = C;

	if (C->bf == 1) A->bf = -1; else A->bf = 0;
	if (C->bf == -1) B->bf = 1; else B->bf = 0;

	C->bf = 0;
}

void RL(AVL_Node *& root, AVL_Node * A)
{
	AVL_Node * B = A->right, *C = B->left, *p = A->parent;

	B->left = C->right;
	if (B->left) B->left->parent = B;

	A->right = C->left;
	if (A->right) A->right->parent = A;

	C->left = A;
	C->right = B;
	A->parent = B->parent = C;
	C->parent = p;

	if (p)
	{
		if (p->left == A) p->left = C; else p->right = C;
	}
	else root = C;

	if (C->bf == -1) A->bf = 1; else A->bf = 0;
	if (C->bf == 1) B->bf = -1; else B->bf = 0;

	C->bf = 0;
}

void insertAVL(AVL_Node * & root, int k)
{
	AVL_Node * w, *p, *r, *x = root;
	bool t;

	w = new AVL_Node;        
	w->left = w->right = w->parent = NULL;
	w->key = k;
	w->bf = 0;

	p = root;              // rozpoczynamy od korzenia

	if (!p) root = w;       // jesli nie ma korzenia, to element umieszczamy w korzeniu
	else
	{                      // inaczej szukamy miejsce dla w
		while (x)
			if (k <= p->key)     // por�wnujemy klucze
			{
				if (!p->left)     // jesli p nie posiada lewego syna
				{
					p->left = w;   // lewym synem p staje sie element w
					break;         
				}
				p = p->left;     // inaczej przechodzimy do lewego syna
				
			}
			
			else
			{
				if (!p->right)    // jesli p nie posiada prawego syna, to
				{
					p->right = w;  // prawym synem staje sie element w
					break;         
				}
				p = p->right;    // inaczej przechodzimy do prawego syna
			}

		w->parent = p;           // ojcem w jest p

		//sprawdzamy wspolczynniki bf, zeby wiedziec ktora rotacje nalezy wykonac

		if (p->bf) p->bf = 0; 
		else
		{
			if (p->left == w)   
				p->bf = 1;
			else
				p->bf = -1;

			r = p->parent;        // b?dziemy szli w g�r? drzewa w kierunku korzenia
								  // r i p wskazuj? ojca i syna na tej ?cie?ce
			t = false;
			while (r)
			{
				if (r->bf)
				{
					t = true;     
					break;        
				};
				
				if (r->left == p) r->bf = 1;
				else             r->bf = -1;

				p = r;          
				r = r->parent;
			}

			if (t)             
			{                 
				if (r->bf == 1)
				{
					if (r->right == p) r->bf = 0; 
					else if (p->bf == -1) LR(root, r);
					else                 LL(root, r);
				}
				else
				{             
					if (r->left == p) r->bf = 0; 
					else if (p->bf == 1) RL(root, r);
					else                RR(root, r);
				}
			}
		}
	}
}

void inorder(AVL_Node *temp)
{
	if (temp == NULL)
		return;
	inorder(temp->left);
	cout << temp->key << "  ";
	inorder(temp->right);
}

AVL_Node * preorder(AVL_Node *temp)
{
	if (temp == NULL)
		return nullptr;
	cout << temp->key << "  ";
	preorder(temp->left);
	preorder(temp->right);
	return temp;
}

AVL_Node *postorder(AVL_Node *temp)
{
	if (temp == NULL)
		return nullptr;
	postorder(temp->left);
	postorder(temp->right);
	cout << temp->key << "  ";
	return temp;

}

AVL_Node * findAVL(AVL_Node * p, int k)
{
	while (p && p->key != k)
		p = (k < p->key) ? p->left : p->right;

	return p;
}

void createTree(AVL_Node * &root, int capacity)
{
	int var = 0;
	for (int index = 0; index < capacity; index++)
	{
		var = rand() % 256;
		cout << " | " << var << " | " << endl;
		insertAVL(root, var);
	}
}

void Add(AVL_Node * &root)
{
	int var = 0;
		cin >> var;
	insertAVL(root, var);	
}
void Empty(AVL_Node *&root)
{
	if (root == NULL)
	cout << endl << "Tree is Empty" << endl;
}