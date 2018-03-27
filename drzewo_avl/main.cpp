#include <ctime>
#include "AVLTree.h"

using namespace std;

int main()
{
	srand(time(NULL));

	string cr, cl, cp;
	int b;
	AVL_Node * root = NULL;
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	int choice;
	while (1)
	{
		cout << "\n---------------------" << endl;
		cout << "Drzewo AVL";
		cout << "\n---------------------" << endl;
		cout << "1.Tworzenie drzewa (dodawanie)" << endl;
		cout << "2.Wyswietlanie" << endl;
		cout << "3.Metoda InOrder" << endl;
		cout << "4.Metoda PreOrder" << endl;
		cout << "5.Metoda PostOrder" << endl;
		cout << "6.Czyszczenie ekranu" << endl;
		cout << "7.Wysokosc" << endl;
		cout << "8. Kasowanie drzewa" << endl;
		cout << "9. Wyjscie z programu" << endl;
		cout << "Wpisz odpowiednia cyfre: ";
		cin >> choice;
		

		switch (choice)
		{
		case 1:
			cout << "Wprowadz ilosc: ";
			cin >> b;
			createTree(root,b);
			break;
		case 2:
			if (root == NULL)
			{
				cout << "Tree is Empty" << endl;
				continue;
			}
			system("cls");
			printBT("", "", root,cr,cp,cl);      // Wy?wietlamy zawarto?? drzewa AVL
			break;
		case 3:
			cout << "Inorder:" << endl;
			inorder(root);
			cout << endl;
			break;
		case 4:
			cout << "Preorder:" << endl;
			preorder(root);
			cout << endl;
			break;
		case 5:
			cout << "Postorder:" << endl;
			postorder(root);
			cout << endl;
			break;
		case 6:
			system("cls");
			break;
		case 7:
			cout << "Wysokosc: ";
			height(root);
			break;
		case 8:
			DFSRelease(root);
			root = NULL;
			cout << "Drzewo zostalo usuniete!" << endl;
			break;
		case 9:
			exit(1);
			break;
		default:
			cout << "Bledna komenda!!" << endl;
		}
	}
	getchar();
return 0;
}