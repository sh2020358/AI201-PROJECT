#include <string.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


#define ROOT "Store"

template <class T>
struct ListNode
{
	ListNode<T>* next;
	T data;
};

template <class T>
class LinkedList
{
public:
	ListNode<T>* root = 0;
	int numItems = 0;

	void emptyList(ListNode<T>* node)
	{
		if (node == 0)
			return;

		emptyList(node->next);
		delete node;
	}

	LinkedList(){}

	void Append(T item)
	{
		ListNode<T>* temp = new ListNode<T>(); // list of pointers of node
		// it returns the pointer to us. The node contains the data and the pointer to the next so we have
		// pointer to the next node and it becomes the pointers of the structure.
		temp->next = 0;
		temp->data = item;

		if (numItems > 0)
		{
			ListNode<T>* tail = root;
			for (int i = 0; i < numItems - 1  ; i++)
				tail = tail->next;

			tail->next = temp;
		}
		else
		{
			root = temp;
		}

		numItems++; // as we are adding the node we are increasing the number of items 
	}

	bool Remove(T item)
	{
		ListNode<T>* node = root;
		ListNode<T>* prev = 0;
		for (int i = 0; i < numItems; i++)
		{
			if (node->data == item)
			{
				if (node == root)
				{
					root = root->next;
				}
				else
				{
					prev->next = node->next;
				}
				
				delete node;
				numItems--; // as we are deleting the node we are decreasing the number of items that we have

				return true;
			}

			prev = node;
			node = node->next;
		}

		return false;
	}

	int length() // just accessing the number of items via constructor deleting it won't effect our program
	{
		return numItems;
	}

	T operator[](int a)
	{
		// operetor overloading here so that we can access elements the pointers of the structs like we access in the array
		ListNode<T> *	t = root;
		for (int i = 0; i < a; i++)
			t = t->next;

		return t->data;
	}

	~LinkedList()
	{
		// here ive free the the memmory because i allocated the dyanmic memmory and now we also had to deallocate it.
		// cause i have used the pointers of structure and we dont have any actual array but a dynamic array
		// and than using the operetor overloading for it so that we can access that dynamic array like we do it in statically
		// There is a node which contain data and its telling where the next node is.
		emptyList(root);
	}
};

class TreeNode
{
public:
	TreeNode* parent = 0;
	LinkedList<TreeNode*> children;

	int numChildren = 0;
	string label;

	TreeNode(string label)
	{
		this->label = label;
	}

	~TreeNode()
	{

	}
};

class Tree
{
private:

	void _print(TreeNode* node, int depth) // here the node is the root node and the depth of the node is zero
	{
		for(int i = 0; i < depth; i++)
			cout << "|    ";	
		 cout << node->label << endl; // here printing the just root node

		for (int j = 0; j < node->numChildren; j++) // here we are going for the children and making their depth greater than
			_print(node->children[j], depth + 1); // depth +1.
	}

	TreeNode* findNode(TreeNode* node, string label) // for the parameter we have to give the node from where we have to
		// start the searching and the lable till which we have to find the node
	{
		if (node == 0) // if the node is zero return zero
			return 0;
		else if (node->label == label) // like the head if the node matches the lable return the label i-e the node
			return node;// that we are trying to find is the head you can say

		TreeNode* child;
		// now here we are moving from the root to its children first we were just finding the root now moving to its children
		// going for the children of the root 
		for (int i = 0; i < node->numChildren; i++)
		{
			child = findNode(node->children[i], label); // here the children of the store and the label that we want to find
			if (child)   // like for electronicis and its the child of root we have the smartphone as the sub_catagory. and we are searching the same.
				return child;
		}

		return 0;
	}
	// changed from stackoverflow
	void _save(TreeNode* node, string currentBranch, LinkedList<string> &Items) // node = root, curr_branch = "", item = store
	{   // we have done the string building here and in file the strings that we store are for the nth items
		if (node->numChildren == 0)
		{  // stopping condition
			string s = currentBranch + '\n';
			Items.Append(s);

		}

		if (node->label != ROOT)
			currentBranch += ":";
		for (int i = 0; i < node->numChildren; i++)// basically here we are using the recursive call
			_save(node->children[i], currentBranch + node->children[i]->label, Items);
	}
	// like the above if condition just deal with the root so we dont have to woory about it
	// but the below one we make a call to the children and in "branch string append the label of that child i-e"
	// 	write that child name like electronics in the cureent branch and move up
	
	// like we moved from the root store and made the Electronics call + its label and than the recursive call went
	// above to root and : is placed

	void emptyTree(TreeNode* node) //called by the destructor
	{  
		// here just emptying the tree with the backtracking with the help of the recursion
		// like we have the Electronics:smartphones: and deleting all of it
		// than moving to smartphone
		if (node == 0)
			return;

		for (int i = 0; i < node->numChildren; i++)
		{
			emptyTree(node->children[i]);
			delete node->children[i];	
		}
		
	}
public:
	TreeNode* root = new TreeNode(ROOT);

	Tree(){}
	// in this function after declaring the root node we are going to add the children of the root
	void Add(string line)
	{
		LinkedList<string> cats;
		// here i have done the string parsing 
		// by reading the file and taking out the names 
		int lastInd = 0;
		for (int i = 0; i < line.length(); i++) // read the string character by character 
		{
			if (line[i] == ':') // where we have the semi colon stop there 
			{   // from the 0th index to current index - 1 we have the first word
				string s = line.substr(lastInd, i - lastInd); // here substr takes out the particular word
				// last index is the last word than take out that word + the charcters that we have counted [i] - last index
				lastInd = i + 1;// start after the colon
				cats.Append(s); // and than append that to cats which is the list of strings
			}
			else if (i == (line.length() - 1)) //it means we have the last char so take total string from last index
			{
				cats.Append(line.substr(lastInd));
			}
		}

		TreeNode* node = root;
		// here is the recursive call for the adding the node in the particular sub catagory of the store
		for (int i = 0; i < cats.numItems; i++) // here in the num items actually i am transversing through
		{  // the whole words that I have read from one line
			
			
			TreeNode* n = findNode(node, cats[i]); // here actually you are finding the particular node.
			// we start from the particular sequence like the electronics is at 0 position and if electronics is 
			// found update it at node = n and go for its other children in a sequence and update it in the
			if (!n)
			{ // now here if the node is not found.....

				TreeNode* newNode = new TreeNode(cats[i]); // it will make the new node
				newNode->parent = node;
				node->children.Append(newNode); // it will add the new node i-e append it to the children node
				node->numChildren++;

				// cout << "here for " << node->label << endl;

				node = newNode; // and than here set the newNode to the current node
			}
			else
				node = n;
		}
		cout << "Added Successfully\n";
	}

	void Delete(string line)
	{
		LinkedList<string> cats;
		// same string parsing that we have done in add function
		int lastInd = 0;
		for (int i = 0; i < line.length(); i++)
		{

			if (line[i] == ':')
			{
				string s = line.substr(lastInd, i - lastInd);
				lastInd = i + 1;
				cats.Append(s);
			}
			else if (i == (line.length() - 1))
			{
				cats.Append(line.substr(lastInd));
			}
		}

		TreeNode* node = root;
		// here again finding the node via recursive call updating the node in the else portion and deleting it
		for (int i = 0; i < cats.numItems; i++)
		{
			TreeNode* n = findNode(node, cats[i]);
			if (!n)
			{
				cout << "node not found\n";
				return;
			}
			else
				node = n;
		}

		// at this point we have the node we want to remove.
		node->parent->numChildren--;
		node->parent->children.Remove(node);
		emptyTree(node);

		cout << "Deleted Successfully\n";
	}

	void printTree()
	{
		_print(root, 0);// here printing the tree the internal function is above and took from internect
		// we passed the root and the depth to it. if depth is 0 no spaces before it and if depth is 1 than 4 spaces 
	}

	void Save(string filepath)
	{
		// here we have given the file path to the save because we have to overwrite the file that we have written 
		LinkedList<string> Items; // items are basically list of strings
		_save(root, "", Items);
		
		ofstream file(filepath, ios::trunc); // after that we have written everything than open the file and every string
		for (int i = 0; i < Items.numItems; i++) // that we have write it on the file
			file << Items[i];
		file.close();

		cout << "Changes Saved Successfully\n";
	}

	~Tree()
	{
		emptyTree(root);
		delete root;
	}
};

bool LoadData(string filepath, Tree& tree)
{
	ifstream file(filepath);
	string line;

	if (!file)
	{
		cout << "File not found \n";
		return false;
	}

	while (getline(file, line))
	{
		if (line != "")
			tree.Add(line);
	}

	file.close();
	return true;
}

void PrintMenu()
{
	cout << "Please Select an Option\n";
	cout << "1- Add\n";
	cout << "2- Delete\n";
	cout << "3- Print\n";
	cout << "4- Save Changes\n";
	cout << "0- Quit\n";
}

int main()
{
	string filepath = "Store.txt";

	Tree tree;
	if (!LoadData(filepath, tree))
		return 0;

	string option;
	string line;

	line = "";
	system("cls");
	PrintMenu();

	getline(cin, option);

	while (true)
	{		
		if (option == "1")
		{
			cout << "Please enter the item to add: ";
			getline(cin, line);
			if (line == "")
				continue;
			tree.Add(line);
		}
		else if (option == "2")
		{
			cout << "Please enter the item to delete: ";
			getline(cin, line);
			if (line == "")
				continue;
			tree.Delete(line);
		}
		else if (option == "3")
			tree.printTree();
		else if (option == "4")
		{
			tree.Save(filepath);
		}
		else if (option == "0")
			break;

		if (option == "1" || option == "2" || option == "3" || option == "4")
			system("pause");
		
		line = "";
		system("cls");
		PrintMenu();

		getline(cin, option);
	}

	return 0;
}