////#include "AVLTree.h"
//
//using namespace std;
//string cr, cl, cp;
//
//void printBT(string sp, string sn, AVL_Node * v)
//{
//	string s;
//
//	if (v)
//	{
//		s = sp;
//		if (sn == cr) s[s.length() - 2] = ' ';
//		printBT(s + cp, cr, v->right);
//
//		s = s.substr(0, sp.length() - 2);
//		cout << s << sn << v->key << ":" << v->bf << endl;
//
//		s = sp;
//		if (sn == cl) s[s.length() - 2] = ' ';
//		printBT(s + cp, cl, v->left);
//	}
//}
//
//void DFSRelease(AVL_Node * v)
//{
//	if (v)
//	{
//		DFSRelease(v->left);   // usuwamy lewe poddrzewo
//		DFSRelease(v->right);  // usuwamy prawe poddrzewo
//		delete v;              // usuwamy sam w?ze?
//	}
//}
//
//
//int makeEmpty(AVL_Node * temp)
//{
//	if (temp == NULL)
//		return 0;
//	makeEmpty(temp->left);
//	makeEmpty(temp->right);
//	delete temp; //zwalnianie pamieci przydzielonej dynamicznie
//	return 0;
//}
//
//void RR(AVL_Node *&root, AVL_Node * A)
//{
//	AVL_Node * B, *p; //p - przodek
//	B = A->right;
//	p = A->parent;
//	if (A != NULL && A->right != NULL)
//	{
//		A->parent = B;
//		B->parent = p;
//		A->right = B->left;
//		B->left = A;
//	}
//
//	if (p != NULL) {
//		if (p->left == A) p->left = B;
//		else p->right = B;
//	}
//	else root = B;
//
//	if (B->bf == -1) A->bf = B->bf = 0;
//	else
//	{
//		A->bf = -1; B->bf = 1;
//	}
//}
//
//
//
//void LL(AVL_Node *&root, AVL_Node * A)
//{
//	AVL_Node *B, *p; //p - przodek
//	B = A->left;
//	p = A->parent;
//
//	if (A != NULL && A->left != NULL)
//	{
//		A->parent = B;
//		B->parent = p;
//		A->left = B->right;
//		B->right = A;
//	}
//	if (p != NULL)
//	{
//		if (p->left == A) //sprawdzamy czy A jest lewym badz prawym dzieckiem
//			p->left = B;
//		else p->right = B;
//	}
//	else
//		root = B;
//
//	if (B->bf == 1) A->bf = B->bf = 0;
//	else
//	{
//		A->bf = 1; B->bf = -1;
//	}
//}
//
//void height(AVL_Node *&root)
//{
//	int *h = new int(0);
//	height(root, h, 0);
//	cout << *h;
//
//}
//void height(AVL_Node *&root, int *h, int level)
//{
//	if (root)
//	{
//		if (root->right)
//		{
//			level++;
//			height(root->right, h, level);
//			level--;
//		}
//		if (level>*h) *h = level;
//
//		if (root->left)
//		{
//			level++;
//			height(root->left, h, level);
//			level--;
//		}
//	}
//}
//
//void Bf(AVL_Node *temp)
//{
//	int iL = 0;		//lewa galaz
//	int iR = 0;		// prawa galaz
//
//	AVL_Node *A = temp, *y = A->left, *z = A->right;
//
//	if (y != NULL)
//		height(y, &iL, 1);
//	if (z != NULL)
//		height(z, &iR, 1);
//
//	A->bf = iL - iR; //obliczanie bf
//}
//
//void LR(AVL_Node *&root, AVL_Node  *A)
//{
//	AVL_Node * B = A->left, *C = B->right, *p = A->parent;
//
//	B->right = C->left;
//	if (B->right) B->right->parent = B;
//
//	A->left = C->right;
//	if (A->left) A->left->parent = A;
//
//	C->right = A;
//	C->left = B;
//	A->parent = B->parent = C;
//	C->parent = p;
//
//	if (p != NULL)
//	{
//		if (p->left == A) p->left = C; else p->right = C;
//	}
//	else root = C;
//
//	if (C->bf == 1) A->bf = -1; else A->bf = 0;
//	if (C->bf == -1) B->bf = 1; else B->bf = 0;
//
//	C->bf = 0;
//}
//
//void RL(AVL_Node *& root, AVL_Node * A)
//{
//	AVL_Node * B = A->right, *C = B->left, *p = A->parent;
//
//	B->left = C->right;
//	if (B->left) B->left->parent = B;
//
//	A->right = C->left;
//	if (A->right) A->right->parent = A;
//
//	C->left = A;
//	C->right = B;
//	A->parent = B->parent = C;
//	C->parent = p;
//
//	if (p)
//	{
//		if (p->left == A) p->left = C; else p->right = C;
//	}
//	else root = C;
//
//	if (C->bf == -1) A->bf = 1; else A->bf = 0;
//	if (C->bf == 1) B->bf = -1; else B->bf = 0;
//
//	C->bf = 0;
//}
//
//
//
//
////---------------------------------
//void insertAVL(AVL_Node * & root, int k)
//{
//	AVL_Node * w, *p, *r;
//	bool t;
//
//	w = new AVL_Node;        // tworzymy dynamicznie nowy w?ze?
//	w->left = w->right = w->parent = NULL;
//	w->key = k;
//	w->bf = 0;
//
//	//----------------------------------------
//	// FAZA 1 - wstawienie w?z?a do drzewa AVL
//	//----------------------------------------
//
//	p = root;              // rozpoczynamy od korzenia
//
//	if (!p) root = w;       // je?li drzewo jest puste, to w?ze? w umieszczamy w korzeniu
//	else
//	{                      // inaczej szukamy miejsce dla w
//		while (true)
//			if (k < p->key)     // porównujemy klucze
//			{
//				if (!p->left)     // je?li p nie posiada lewego syna, to
//				{
//					p->left = w;   // lewym synem p staje si? w?ze? w
//					break;         // wychodzimy z p?tli
//				}
//				p = p->left;     // inaczej przechodzimy do lewego syna
//			}
//			else
//			{
//				if (!p->right)    // je?li p nie posiada prawego syna, to
//				{
//					p->right = w;  // prawym synem staje si? w?ze? w
//					break;         // wychodzimy z p?tli
//				}
//				p = p->right;    // inaczej przechodzimy do prawego syna
//			}
//
//		w->parent = p;           // ojcem w jest p
//
//								 //---------------------------------
//								 // FAZA 2 - równowa?enie drzewa AVL
//								 //---------------------------------
//
//		if (p->bf) p->bf = 0; // UWAGA NR 1
//		else
//		{
//			if (p->left == w)   // UWAGA NR 2
//				p->bf = 1;
//			else
//				p->bf = -1;
//
//			r = p->parent;        // b?dziemy szli w gór? drzewa w kierunku korzenia
//								  // r i p wskazuj? ojca i syna na tej ?cie?ce
//			t = false;
//			while (r)
//			{
//				if (r->bf)
//				{
//					t = true;     // ustalamy wynik p?tli
//					break;        // przerywamy p?tl?
//				};
//				// inaczej modyfikujemy r.bf
//				if (r->left == p) r->bf = 1;
//				else             r->bf = -1;
//
//				p = r;          // przechodzimy w gór? na wy?szy poziom
//				r = r->parent;
//			}
//
//			if (t)             // je?li r.bf = +/- 1, to musimy
//			{                 // równowa?y? drzewo
//				if (r->bf == 1)
//				{
//					if (r->right == p) r->bf = 0;  // ga??zie si? równowa??
//					else if (p->bf == -1) LR(root, r);
//					else                 LL(root, r);
//				}
//				else
//				{              // r.bf = -1
//					if (r->left == p) r->bf = 0;  // ga??zie si? równowa??
//					else if (p->bf == 1) RL(root, r);
//					else                RR(root, r);
//				}
//			}
//		}
//	}
//}
//
//void inorder(AVL_Node *temp)
//{
//	if (temp == NULL)
//		return;
//	inorder(temp->left);
//	cout << temp->key << "  ";
//	inorder(temp->right);
//}
//
//AVL_Node * preorder(AVL_Node *temp)
//{
//	if (temp == NULL)
//		return nullptr;
//	cout << temp->key << "  ";
//	preorder(temp->left);
//	preorder(temp->right);
//	return temp;
//}
//
//AVL_Node *postorder(AVL_Node *temp)
//{
//	if (temp == NULL)
//		return nullptr;
//	postorder(temp->left);
//	postorder(temp->right);
//	cout << temp->key << "  ";
//	return temp;
//
//}
//
//AVL_Node * findAVL(AVL_Node * p, int k)
//{
//	while (p && p->key != k)
//		p = (k < p->key) ? p->left : p->right;
//
//	return p;
//}
//
//AVL_Node * removeAVL(AVL_Node * & root, AVL_Node * A)
//{
//	AVL_Node  *t, *y, *z;
//	bool nest;
//
//	if (A->left && A->right)
//	{
//		y = removeAVL(root, preorder(A));
//		nest = false;
//	}
//	else
//	{
//		if (A->left)
//		{
//			y = A->left; A->left = NULL;
//		}
//		else
//		{
//			y = A->right; A->right = NULL;
//		}
//		A->bf = 0;
//		nest = true;
//	}
//
//	if (y)
//	{
//		y->parent = A->parent;
//		y->left = A->left;  if (y->left)  y->left->parent = y;
//		y->right = A->right; if (y->right)  y->right->parent = y;
//		y->bf = A->bf;
//	}
//	if (A->parent)
//	{
//		if (A->parent->left == A) A->parent->left = y; else A->parent->right = y;
//	}
//	else root = y;
//
//	if (nest)
//	{
//		z = y;
//		y = A->parent;
//		while (y)
//		{
//			if (!y->bf)
//			{              // Przypadek nr 1
//				if (y->left == z)  y->bf = -1; else y->bf = 1;
//				break;
//			}
//			else
//			{
//				if (((y->bf == 1) && (y->left == z)) || ((y->bf == -1) && (y->right == z)))
//				{           // Przypadek nr 2
//					y->bf = 0;
//					z = y; y = y->parent;
//				}
//				else
//				{
//					if (y->left == z)  t = y->right; else t = y->left;
//					if (!t->bf)
//					{         // Przypadek 3A
//						if (y->bf == 1) LL(root, y); else RR(root, y);
//						break;
//					}
//					else if (y->bf == t->bf)
//					{         // Przypadek 3B
//						if (y->bf == 1) LL(root, y); else RR(root, y);
//						z = t; y = t->parent;
//					}
//					else
//					{         // Przypadek 3C
//						if (y->bf == 1) LR(root, y); else RL(root, y);
//						z = y->parent; y = z->parent;
//					}
//				}
//			}
//		}
//	}
//	return A;
//}
//
//void createTree(AVL_Node * &root, int capacity)
//{
//	int var = 0;
//	for (int index = 0; index < capacity; index++)
//	{
//		var = rand() % 256;
//		cout << " | " << var << " | " << endl;
//		insertAVL(root, var);
//	}
//}