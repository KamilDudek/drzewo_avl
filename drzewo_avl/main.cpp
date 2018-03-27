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
		cout << "1.Tworzenie drzewa losowego drzewa" << endl;
		cout << "2.Wyswietlanie" << endl;
		cout << "3.Metoda InOrder" << endl;
		cout << "4.Metoda PreOrder" << endl;
		cout << "5.Metoda PostOrder" << endl;
		cout << "6.Czyszczenie ekranu" << endl;
		cout << "7.Wysokosc" << endl;
		cout << "8. Kasowanie drzewa" << endl;
		cout << "9. Dodawanie argumentu" << endl;
		cout << "10. Wyjscie z programu" << endl;
		cout << "Wpisz odpowiednia cyfre: ";
		//cin >> choice;
		string tmp;
		getline(cin,tmp);
		choice = atoi(tmp.c_str());
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
				cout <<endl<< "Tree is Empty" << endl;
				continue;
			}
			system("cls");
			printBT("", "", root,cr,cp,cl);      
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
			cout << endl<<"Wysokosc: ";
			height(root);
			break;
		case 8:
			DFSRelease(root);
			root = NULL;
			cout <<endl<< "Drzewo zostalo usuniete!" << endl;
			break;
		case 9:
			cout << endl<< "Wprowadz liczbe:";
			Add(root);
			break;
		case 10:
			exit(1);
		default:
			cout << endl<<"Bledna komenda!!" << endl;

			/*getchar();
			exit(1);*/
		}
	}
	getchar();
return 0;
}