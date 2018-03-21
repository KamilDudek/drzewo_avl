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

string cr, cl, cp;

void printBT(string sp, string sn, AVL_Node * v)
{
	string s;

	if (v)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		printBT(s + cp, cr, v->right);

		s = s.substr(0, sp.length() - 2);
		cout << s << sn << v->key << ":" << v->bf << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		printBT(s + cp, cl, v->left);
	}
}

void DFSRelease(AVL_Node * v)
{
	if (v)
	{
		DFSRelease(v->left);   // usuwamy lewe poddrzewo
		DFSRelease(v->right);  // usuwamy prawe poddrzewo
		delete v;              // usuwamy sam wêze³
	}
}


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

	if (B->bf == -1) A->bf = B->bf = 0;
	else
	{
		A->bf = -1; B->bf = 1;
	}
}



void LL(AVL_Node *&root, AVL_Node * A)
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

	if (B->bf == 1) A->bf = B->bf = 0;
	else
	{
		A->bf = 1; B->bf = -1;
	}
}
void height(AVL_Node * &root, int *h, int level)
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

void LR(AVL_Node * & root, AVL_Node * A)
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

	void RL(AVL_Node * & root, AVL_Node * A)
	{
		AVL_Node * B = A->right, *C = B->left, *p = A->parent;

		B->left = C->right;
		if (B->left) B->left->parent = B;

		A->right = C->left;
		if (A->right) A->right->parent = A;

		C->left = A;
		C->right = B;
		A->parent = B->parent = C;
		C->parent= p;

		if (p)
		{
			if (p->left == A) p->left = C; else p->right = C;
		}
		else root = C;

		if (C->bf == -1) A->bf = 1; else A->bf = 0;
		if (C->bf == 1) B->bf = -1; else B->bf = 0;

		C->bf = 0;
}




//---------------------------------
	void insertAVL(AVL_Node * & root, int k)
	{
		AVL_Node * w, *p, *r;
		bool t;

		w = new AVL_Node;        // tworzymy dynamicznie nowy wêze³
		w->left = w->right = w->parent = NULL;
		w->key = k;
		w->bf = 0;

		//----------------------------------------
		// FAZA 1 - wstawienie wêz³a do drzewa AVL
		//----------------------------------------

		p = root;              // rozpoczynamy od korzenia

		if (!p) root = w;       // jeœli drzewo jest puste, to wêze³ w umieszczamy w korzeniu
		else
		{                      // inaczej szukamy miejsce dla w
			while (true)
				if (k < p->key)     // porównujemy klucze
				{
					if (!p->left)     // jeœli p nie posiada lewego syna, to
					{
						p->left = w;   // lewym synem p staje siê wêze³ w
						break;         // wychodzimy z pêtli
					}
					p = p->left;     // inaczej przechodzimy do lewego syna
				}
				else
				{
					if (!p->right)    // jeœli p nie posiada prawego syna, to
					{
						p->right = w;  // prawym synem staje siê wêze³ w
						break;         // wychodzimy z pêtli
					}
					p = p->right;    // inaczej przechodzimy do prawego syna
				}

			w->parent = p;           // ojcem w jest p

								 //---------------------------------
								 // FAZA 2 - równowa¿enie drzewa AVL
								 //---------------------------------

			if (p->bf) p->bf = 0; // UWAGA NR 1
			else
			{
				if (p->left == w)   // UWAGA NR 2
					p->bf = 1;
				else
					p->bf = -1;

				r = p->parent;        // bêdziemy szli w górê drzewa w kierunku korzenia
								  // r i p wskazuj¹ ojca i syna na tej œcie¿ce
				t = false;
				while (r)
				{
					if (r->bf)
					{
						t = true;     // ustalamy wynik pêtli
						break;        // przerywamy pêtlê
					};
					// inaczej modyfikujemy r.bf
					if (r->left == p) r->bf = 1;
					else             r->bf = -1;

					p = r;          // przechodzimy w górê na wy¿szy poziom
					r = r->parent;
				}

				if (t)             // jeœli r.bf = +/- 1, to musimy
				{                 // równowa¿yæ drzewo
					if (r->bf == 1)
					{
						if (r->right == p) r->bf = 0;  // ga³êzie siê równowa¿¹
						else if (p->bf == -1) LR(root, r);
						else                 LL(root, r);
					}
					else
					{              // r.bf = -1
						if (r->left == p) r->bf = 0;  // ga³êzie siê równowa¿¹
						else if (p->bf == 1) RL(root, r);
						else                RR(root, r);
					}
				}
			}
		}
	}
int main()
{


	
		int Tk[32];   // tablica kluczy wêz³ów
		int i, x, i1, i2;
		AVL_Node * root = NULL;

		// ustawiamy ³añcuchy znakowe, poniewa¿ nie wszystkie edytory pozwalaj¹
		// wstawiaæ znaki konsoli do tworzenia ramek.
		// cr = +--
		//      |

		// cl = |
		//      +--

		// cp = |
		//      |

		cr = cl = cp = "  ";
		cr[0] = 218; cr[1] = 196;
		cl[0] = 192; cl[1] = 196;
		cp[0] = 179;

		srand(time(NULL));        // inicjujemy generator pseudolosowy

		for (i = 0; i < 32; i++)   // Tablicê wype³niamy wartoœciami kluczy
			Tk[i] = i + 1;

		for (i = 0; i < 300; i++)  // Mieszamy tablicê
		{
			i1 = rand() % 32;       // Losujemy 2 indeksy
			i2 = rand() % 32;

			x = Tk[i1];             // Wymieniamy Tk[i1] <--> Tk[i2]
			Tk[i1] = Tk[i2];
			Tk[i2] = x;
		}

		for (i = 0; i < 32; i++)   // Na podstawie tablicy tworzymy drzewo AVL
		{
			cout << Tk[i] << " ";
			insertAVL(root, Tk[i]);
		}

		cout << endl << endl;

		printBT("", "", root);      // Wyœwietlamy zawartoœæ drzewa AVL

		cout << endl << endl;

		for (i = 0; i < 300; i++)  // Ponownie mieszamy tablicê
		{
			i1 = rand() % 32; i2 = rand() % 32;
			x = Tk[i1]; Tk[i1] = Tk[i2]; Tk[i2] = x;
		}

		//for (i = 0; i < 15; i++)    // Usuwamy 15 wêz³ów
		//{
		//	cout << Tk[i] << " ";
		//	removeAVL(root, findAVL(root, Tk[i]));
		//}

		cout << endl << endl;

		printBT("", "", root);      // Wyœwietlamy zawartoœæ drzewa AVL

		DFSRelease(root);         // Usuwamy drzewo AVL z pamiêci
		getchar();
		return 0;
		
}