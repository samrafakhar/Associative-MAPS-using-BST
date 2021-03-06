#include "stdafx.h"
# include <iostream>
#include <fstream>
#include <string> 
#include <iomanip> 
using namespace std;

class Product;

template<class T>
class Node
{
public:
	T data;
	Node<T> * next;
	Node(T d = 0, Node* N = NULL)
	{
		data = d;
		next = N;
	}
};

template <class T>
class BNode
{
public:
	T data;
	BNode* left;
	BNode* right;

	BNode(const T& D, BNode* P = NULL, BNode* N = NULL)	//overloaded constructor
	{
		data = D;
		left = P;
		right = N;
	}

	BNode()
	{
		left = NULL;
		right = NULL;
	}

	~BNode()
	{
	}
};

template<class T>
class Stack
{
private:
	Node<T> * top;
public:
	Stack()
	{
		top = NULL;
	}

	~Stack()
	{
		Node<T>* NodeToDelete = 0;
		while (top != 0)
		{
			NodeToDelete = top;
			top = top->next;
			delete NodeToDelete;
		}
	}

	bool isEmpty()
	{
		if (top == NULL)
		{
			return true;
		}
		return false;
	}

	bool push(const T & val)
	{
		if (isEmpty())
		{
			top = new Node<T>(val, NULL);
		}
		else
		{
			Node<T> * newNode = new Node<T>(val, top);
			top = newNode;
		}
		return true;
	}

	T pop()
	{
		T el;
		if (!isEmpty())
		{
			el = top->data;
			Node<T> * temp = top;
			top = temp->next;
			delete temp;
			temp = NULL;
			return el;
		}
	}

	T get_top()
	{
		return top->data;
	}

	void Print()
	{
		for (Node<T>* temp = top; temp != 0; temp = temp->next)
		{
			cout << temp->data << "\t";
		}
		cout << endl;
	}
};

template <class T>
class BST
{
private:
	BNode<T>*root;
public:

	BST()
	{
		root = NULL;
	}

	void insert(const T &key)
	{
		insert_recursively(root, key);
		//insert_iteratively(root, key);
	}

	void search(const T &key)
	{
		int choice;
		cout << "To search recursively press 0" << endl;
		cout << "To search iteratively press 1" << endl;
		cout << "enter choice :\t";
		cin >> choice;
		cout << endl;
		if (choice == 0)
		{
			if (search_recursively(root, key) == true)
				cout << "yes, this item is present" << endl;
			else
				cout << "not found" << endl;
		}
		else
		{
			if (search_iteratively(root, key) == true)
				cout << "yes, this item is present" << endl;
			else
				cout << "not found" << endl;
		}
	}

	void Delete(const T &key)
	{
		int choice;
		cout << "To delete recursively press 0" << endl;
		cout << "To delete iteratively press 1" << endl;
		cout << "enter choice :\t";
		cin >> choice;
		cout << endl;
		if (choice == 0)
			delete_recursively(root, key);
		else
			delete_iteratively(root, key);
	}

	void print()
	{
		if (root == NULL)
		{
			cout << "empty tree" << endl;
			return;
		}
		else
		{
			int choice;
			cout << "To print recursively press 0" << endl;
			cout << "To print iteratively press 1" << endl;
			cout << "enter choice :\t";
			cin >> choice;
			cout << endl;
			if (choice == 0)
				inorder_recursively(root);
			else
				inorder_iteratively(root);
		}
	}

	void Destroy()
	{
		destroy(root);
	}

	int count()
	{
		int count = 1;
		if (root != NULL) 
		{
			count = node_count(root, count);
		}
		return count;
	}

	void lValues(T* &arr, const T &key)
	{
		arr = new T[count()];
		int p=LargerValues(arr,root, key);
		cout << endl;
		for (int i = 0; i<p; i++)
			cout << arr[i];
	}

	bool insert_recursively(BNode<T>*& tree, T key)
	{
		if (tree == nullptr)
		{
			tree = new BNode<T>(key);
			return true;
		}
		else if (key < tree->data)
			return insert_recursively(tree->left, key);
		else if (key > tree->data)
			return insert_recursively(tree->right, key);
	}

	bool insert_iteratively(BNode<T>* & tree, const T& key)
	{
		BNode<T> *newBNode = new BNode<T>(key);

		BNode<T> *ptr = nullptr;
		BNode<T> *ptr_parent = nullptr;

		if (tree == NULL)
		{
			tree = newBNode;
			ptr = tree;
		}
		else
		{
			ptr = tree;
			while (ptr != NULL)
			{
				if ((ptr->data) == key)
					return false;

				if ((ptr->data)>key)
				{
					ptr_parent = ptr;
					ptr = ptr->left;
				}
				else
				{
					ptr_parent = ptr;
					ptr = ptr->right;
				}
			}

			if ((ptr_parent->data) < key)
				ptr_parent->left = newBNode;
			else
				ptr_parent->right = newBNode;
		}

		return true;

	}

	bool search_iteratively(BNode<T>* & tree, const T& key)
	{
		while (tree != NULL)
		{
			if (tree->data < key)
				tree = tree->right;

			else if (tree->data > key)
				tree = tree->left;
			else
				return true;
		}
		return false;
	}

	bool search_recursively(BNode<T>* & tree, const T& key)
	{
		if (tree == NULL)
			return false;
		else if (tree->data == key)
			return tree;
		else if (tree->data < key)
			return search_recursively(tree->right, key);
		else if (tree->data > key)
			return search_recursively(tree->left, key);
	}

	void inorder_recursively(BNode<T>*tree)
	{
		if (tree)
		{
			inorder_recursively(tree->left);
			cout << tree->data << " ";
			inorder_recursively(tree->right);
		}
	}

	void inorder_iteratively(BNode<T>*tree)
	{
		Stack<BNode<T>*> stack;
		BNode<T> *ptr = tree;

		while (ptr != NULL || stack.isEmpty() == false)
		{
			while (ptr != NULL)
			{
				stack.push(ptr);
				ptr = ptr->left;
			}

			ptr = stack.get_top();
			stack.pop();

			cout << ptr->data << " ";
			ptr = ptr->right;
		}
	}

	void delete_BNode(BNode<T>* & tree, const T& key)
	{
		BNode<T>*temp = tree;
		if (tree->left == NULL)
		{
			tree = tree->right;
			delete temp;
		}
		else if (tree->right == NULL)
		{
			tree = tree->left;
			delete temp;
		}
		else
		{
			T val = Find_Max(tree->left);
			tree->data = val;
			delete_recursively(tree->left, val);
		}
	}

	T Find_Max(BNode<T>* & tree)
	{
		while (tree->right != NULL)
			tree = tree->right;
		return tree->data;
	}

	void delete_recursively(BNode<T>* & tree, const T& key)
	{
		if (tree)
		{
			if (tree->data > key)
				delete_recursively(tree->left, key);
			else if (tree->data < key)
				delete_recursively(tree->right, key);
			if (tree->data == key)
				delete_BNode(tree, key);
		}
	}

	void delete_iteratively(BNode<T>* & tree, const T& key)
	{
		BNode<T> *curr, *prev, *new_parent, *new_n, *child;

		bool check = false;

		prev = NULL;
		curr = tree;
		while (curr != NULL)
		{
			if (curr->data == key)
				break;
			else if (curr->data > key)
			{
				prev = curr;
				check = true;
				curr = curr->left;
			}
			else
			{
				prev = curr;
				check = false;
				curr = curr->right;
			}
		}

		if (curr == NULL)
		{
			cout << "not found. cant be deleted" << endl;
			return;
		}

		if ((curr->left == NULL) && (curr->right == NULL))
		{
			if (prev == NULL)
			{
				if (curr == tree)
				{
					delete curr;
					tree = NULL;
				}
			}
			else
			{
				delete curr;
				if (check)
					prev->left = NULL;
				else
					prev->right = NULL;
			}
		}
		else
			if ((curr->left == NULL) || (curr->right == NULL))
			{
				if (curr->left != NULL)
					child = curr->left;
				else
					child = curr->right;

				if (prev == NULL)
				{
					if (curr == tree)
					{
						tree = child;
						delete curr;
						curr = NULL;
					}
				}
				else
				{
					if (check)
						prev->left = child;
					else
						prev->right = child;
					delete curr;
					curr = NULL;
				}
			}
			else
			{
				new_parent = curr;
				new_n = curr->left;
				check = true;
				while (new_n->right != NULL)
				{
					new_parent = new_n;
					new_n = new_n->right;
					check = false;
				}

				curr->data = new_n->data;

				if (check)
				{
					if (new_n->right == NULL)
					{
						curr->left = new_n->left;
						delete new_n;
						new_n = NULL;
					}
				}
				else
				{
					new_parent->right = new_n->left;
					delete new_n;
					new_n = NULL;
				}
			}
	}

	void duplicate(BST<T> &rhs)
	{
		if (rhs.root == NULL)
			root = NULL;
		else
			copy_nodes(this->root, rhs.root);
	}

	void copy_nodes(BNode<T>* &a, BNode<T>* &b)
	{
		if (b == NULL)
			a = NULL;
		else
		{
			a = new BNode<T>;
			a->data = b->data;
			copy_nodes(a->left, b->left);
			copy_nodes(a->right, b->right);
		}
	}

	void destroy(BNode<T>*&tree)
	{
		if (tree)
		{
			destroy(tree->left);
			destroy(tree->right);
			delete tree;
			tree = NULL;
		}
	}

	int node_count(BNode<T>* &tree, int &count)
	{
		if (tree->left != NULL)
		{
			count = count + 1;
			node_count(tree->left, count);
		}
		if (tree->right != NULL)
		{
			count = count + 1;
			node_count(tree->right, count);
		}
		return count;
	}

	int LargerValues(T* &arr, BNode<T>* &tree, T value)
	{
		static int i = 0;
		if (tree)
		{
			LargerValues(arr,tree->left, value);
			if (tree->data > value)
			{
				arr[i] = tree->data;
				i = i + 1;
			}
			LargerValues(arr,tree->right, value);
		}
		return i;
	}
};

class Product 
{
	friend ostream& operator<<(ostream& out, const Product &);
private:
	int ProductID;
	string name;
	int quantity;
public:  
	bool operator<(const Product& obj )	//less than operator
	{
		if (ProductID < obj.ProductID)
			return true;
		return false;
	}

	bool operator>(const Product& obj)	//greater than operator
	{
		if (ProductID > obj.ProductID)
			return true;
		return false;
	}

	bool operator==(const Product& obj)	//greater than operator
	{
		if (ProductID == obj.ProductID)
			return true;
		return false;
	}

	bool operator!=(const Product& obj)	//greater than operator
	{
		if (ProductID == obj.ProductID)
			return true;
		return false;
	}

	Product(string n =" ", int id = 0, int q = 0)
	{
		name = n;
		ProductID = id;
		quantity = q;
	}
}; 

void LoadBST(ifstream &fin, BST<Product> &ProductMap)
{
	char buffer[200];
	for (int i = 0; i < 3; i++)
		fin >> buffer;
	fin.getline(buffer, 200);

	char i[180];
	char n[180];
	char q[180];
	int len = 0;
	char*Name = nullptr;
	int id;
	int quant;

	while (!fin.eof())
	{
		fin.getline(buffer, 180);				//inputs a whole line
		strcpy(i, strtok(buffer, "\t"));		//tokenizes the line
		strcpy(n, strtok(NULL, "\t"));			//stores tokens in different variable
		strcpy(q, strtok(NULL, "\n"));

		id = atoi(i);
		quant = atoi(q);

		len = strlen(n);						//allocation and copy to char*
		Name = new char[len + 1];
		strcpy(Name, n);
		Name[len + 1] = '\0';

		Product obj(Name, id, quant);
		ProductMap.insert(obj);
	}
}

ostream& operator<<(ostream& out, const Product &obj)
{
	out << obj.ProductID << "\t" << setw(20) << left << obj.name << "\t" << setw(20) << left << obj.quantity << endl;
	return out;
}

int  menu()
{
	int i = 1;
	int choice;
	cout << endl;
	cout << "--------------------------MENU--------------------------" << endl;
	cout << i++ << ". Insert" << endl;
	cout << i++ << ". Delete" << endl;
	cout << i++ << ". Search" << endl;
	cout << i++ << ". Print" << endl;
	cout << i++ << ". Duplicate" << endl;
	cout << i++ << ". Node Count" << endl;
	cout << i++ << ". Large Values" << endl;
	cout << i++ << ". Destroy" << endl;
	cout << i++ << ". Exit" << endl;

	cout << "enter choice :\t";
	cin >> choice;
	cout << endl;
	return choice;
}

int main()
{
	BST<Product> ProductMap;
	Product p;

	string filename;
	cout << "enter the name of the data file: ";
	cin >> filename;
	ifstream fin(filename.c_str());
	if (fin) 
	{
		LoadBST(fin, ProductMap);
		fin.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	int choice;
	choice = menu();
	
	while (choice < 10)
	{
		if (choice == 1)
		{
			string name;
			int id;
			int quantity;
			cout << "Name :\t";
			cin >> name;
			cout << "Product ID:\t";
			cin >> id;
			cout << "Quantity:\t";
			cin >> quantity;
			Product q(name,id,quantity);
			ProductMap.insert(q);
		}
		if (choice == 2)
		{
			string name = " ";
			int id = 0;
			int quantity = 0;
			cout << "Product ID:\t";
			cin >> id;
			Product q(" ", id, 0);
			ProductMap.Delete(q);
		}
		if (choice == 3)
		{
			string name=" ";
			int id = 0;
			int quantity = 0;
			cout << "Product ID:\t";
			cin >> id;
			Product q(" ", id, 0);
			ProductMap.search(q);
		}
		if (choice == 4)
		{
			ProductMap.print();
		}
		if (choice == 5)
		{
			BST<Product> ProductMap2;
			char ch;
			ProductMap2.duplicate(ProductMap);
			cout << "Duplicate of ProductMap is made with the name ProductMap2" << endl;
			cout << "print the duplicate product map 1/0 " << endl;
			cout << "enter choice :\t";
			cin >> ch;
			cout << endl;
			if (ch == '1')
				ProductMap2.print();
			else
				choice = menu();
		}
		if (choice == 6)
		{
			cout << "number of nodes in the tree are " << ProductMap.count() << endl;
		}
		if (choice == 7)
		{
			int num;
			Product*product_array = nullptr;
			cout << "find product IDs with values greater than ";
			cin >> num;
			Product q(" ", num, 0);
			ProductMap.lValues(product_array, q);
		}
		if (choice == 8)
		{
			ProductMap.Destroy();
			cout << "the product map has been destroyed" << endl;
		}
		if (choice == 9)
		{
			cout << "--------------------------Exiting----------------------";
			return 0;
		}

		choice = menu();
	}

	if(choice>=10)
	{
		cout << "invalid choice" << endl;
		choice = menu();
	}

	return 0;
}


