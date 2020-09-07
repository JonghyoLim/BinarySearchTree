#pragma once
#include <iostream>
#include "stdafx.h"
#include <string>
using namespace std;

//search by letter as retreiveletter() is not working properly
template<class ItemType>
struct contact
{
	ItemType fName;
	ItemType lName;
	ItemType num;
};

template<class ItemType>
struct TreeNode
{
	contact<ItemType> info;
	TreeNode* left;
	TreeNode* right;
};


template<class ItemType>
struct TreeNode;

template<class ItemType>
class TreeType
{
public:
	TreeType(); 	// constructor
	~TreeType(); 	// destructor
	TreeType(const TreeType<ItemType>& originalTree); // copy constructor
	void operator=(const TreeType<ItemType>& originalTree); // important
	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	int NumberOfNodes() const;
	void RetrieveItem(ItemType& item, bool& found);
	void RetrieveLetterItem(ItemType& item, bool& found);
	void Retrieve(TreeNode<ItemType>* tree, ItemType& item, bool& found);
	void RetrieveLetter(TreeNode<ItemType>* tree, ItemType& item, bool& found);
	void Insert(TreeNode<ItemType>*& tree, ItemType item1, ItemType item2, ItemType item3);
	void InsertItem(ItemType item1, ItemType item2, ItemType item3);
	void DeleteItem(string name, string surname, string num);
	void ResetTree(); //important to create
	void GetNextItem(ItemType& item, bool& finished); //important
	void PrintTree();


private:
	TreeNode<ItemType> * root;
};


template<class ItemType>
TreeType<ItemType>::TreeType()
{
	root = NULL;
}

template<class ItemType>
TreeType<ItemType>::~TreeType()
{
	Destroy(root);
}

template<class ItemType>
TreeType<ItemType>::TreeType(const TreeType<ItemType>& originalTree)
{
	CopyTree(root, originaltree);
}



template<class ItemType>
void CopyTree(TreeNode<ItemType>*& copy, const TreeNode<ItemType>* originalTree)
{
	if (originalTree == NULL)
		copy = NULL;
	else
	{
		copy = new TreeNode;
		copy->info = originalTree->info;
		CopyTree(copy->left, originalTree->left);
		CopyTree(copy->right, originalTree->right);
	}
}



template<class ItemType>
void TreeType<ItemType>::operator=(const TreeType<ItemType>& originalTree)
{
	//call the function  CopyTree to copy originaltree into main Root!
	{
		if (&originalTree == this)
			return true;
		Destroy(root);
		CopyTree(root, originalTree.root);
	}
}


template<class ItemType>
bool TreeType<ItemType>::IsFull() const
{
	TreeNode* location;
	try
	{
		location = new TreeNode;
		delete location;
		return false;
	}
}

template<class ItemType>
void Destroy(TreeNode<ItemType>*& tree)
{
	if (tree != NULL)
	{
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}
}

template<class ItemType>
void TreeType<ItemType>::MakeEmpty()
{
	Destroy(root);
	root = NULL;
}



template<class ItemType>
bool TreeType<ItemType>::IsEmpty() const
{
	return root == NULL;
}



template<class ItemType>
int CountNodes(TreeNode<ItemType>* tree)
{
	if (tree == NULL)
		return 0;
	else
		return
		CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

template<class ItemType>
int TreeType<ItemType>::NumberOfNodes() const
{
	return CountNodes(root);
}



template<class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data1, ItemType& data2, ItemType& data3)
{
	while (tree->right != NULL)
		tree = tree->right;
	data1 = tree->info.fName;
	data2 = tree->info.lName;
	data3 = tree->info.num;
}



template<class ItemType>
void TreeType<ItemType>::Retrieve(TreeNode<ItemType>* tree, ItemType& item, bool& found)
{
	if (tree == NULL)
		found = false;

	else if (strcmp(item.c_str(), tree->info.lName.c_str()) < 0)// strcmp(p1, p2) <0
		Retrieve(tree->left, item, found);


	else if (strcmp(item.c_str(), tree->info.lName.c_str()) > 0)// strcmp(p1, p2) > 0
		Retrieve(tree->right, item, found);
	else
	{
		PrintItem(tree);
		Retrieve(tree->left, item, found);
		Retrieve(tree->right, item, found);
		found = true;
	}
}



template<class ItemType>
void TreeType<ItemType>::RetrieveLetter(TreeNode<ItemType>* tree, ItemType& item, bool& found)
{
	if (tree == NULL)
		found = false;

	else if (strncmp(item.c_str(), tree->info.lName.c_str(), 0) < 0)// strcmp(p1, p2) <0
		RetrieveLetter(tree->left, item, found);


	else if (strncmp(item.c_str(), tree->info.lName.c_str(), 0) > 0)// strcmp(p1, p2) > 0
		RetrieveLetter(tree->right, item, found);
	else
	{
		PrintItem(tree);
		Retrieve(tree->left, item, found);
		Retrieve(tree->right, item, found);
		found = true;
	}
}


template<class ItemType>
void TreeType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
	Retrieve(root, item, found);
}

template<class ItemType>
void TreeType<ItemType>::RetrieveLetterItem(ItemType& item, bool& found)
{
	RetrieveLetter(root, item, found);
}
template<class ItemType>
void TreeType<ItemType>::Insert(TreeNode<ItemType>*& tree, ItemType item1, ItemType item2, ItemType item3)
{
	if (tree == NULL)
	{			// Insertion place found.
		tree = new TreeNode<ItemType>;
		tree->right = NULL;
		tree->left = NULL;
		tree->info.fName = item1;
		tree->info.lName = item2;
		tree->info.num = item3;
	}
	else if (strcmp(item2.c_str(), tree->info.lName.c_str()) < 0)
		Insert(tree->left, item1, item2, item3);  // Insert in left subtree.
	else
		Insert(tree->right, item1, item2, item3); // Insert in right subtree.
}

template<class ItemType>
void TreeType<ItemType>::InsertItem(ItemType item1, ItemType item2, ItemType item3)
{
	Insert(root, item1, item2, item3);
}

template<class ItemType>
void Delete(TreeNode<ItemType>*& tree, string name, string surname, string num)
{
	if (strcmp(surname.c_str(), tree->info.lName.c_str()) == 0)
	{
		if (strcmp(name.c_str(), tree->info.fName.c_str()) == 0
			&& strcmp(surname.c_str(), tree->info.lName.c_str()) == 0
			&& strcmp(num.c_str(), tree->info.num.c_str()) == 0)
			DeleteNode(tree);
		else
			cout << " Details are incorrect." << endl;
	}

	else if (strcmp(surname.c_str(), tree->info.lName.c_str()) < 0)
		Delete(tree->left, name, surname, num);
	else if (strcmp(surname.c_str(), tree->info.lName.c_str()) > 0)
		Delete(tree->right, name, surname, num);
	else
		DeleteNode(tree);// node found
}

template<class ItemType>
void TreeType<ItemType>::DeleteItem(string name, string surname, string num)
{
	Delete(root, name, surname, num);
}



template<class ItemType>
void DeleteNode(TreeNode<ItemType>*& tree)
{
	TreeNode<ItemType>* tempPtr;
	ItemType data1, data2, data3;
	tempPtr = tree;

	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
	}
	else
	{
		GetPredecessor(tree->left, data1, data2, data3);
		tree->info.fName = data1;
		tree->info.lName = data2;
		tree->info.num = data3;
		Delete(tree->left, data1, data2, data3);
	}
}




template<class ItemType>
void TreeType<ItemType>::ResetTree()
{
	// Function: Initializes current position for an
	// iteration through the tree in order specified.
	// Post: Current position is prior to root of the tree.
}


template<class ItemType>
void TreeType<ItemType>::GetNextItem(ItemType& item, bool& finished)
{
	// Function: Gets the next element in the tree in order.
	// Pre: Current position is defined.Item at current position is not last in the tree.
	// Post: Current position is one position beyond current position at entry to GetNextItem.	  
	// finished = (current position is last in tree) item is a copy of element at current position.
	finished = false;
}




template<class ItemType>
void TreeType<ItemType>::PrintTree()
{
	Print(root);
}


template<class ItemType>
void Print(TreeNode<ItemType>* tree)

{
	if (tree != NULL)
	{
		Print(tree->left);
		//outFile << tree->info;
		PrintItem(tree);
		Print(tree->right);
	}
}

template<class ItemType>
void InPrint(TreeNode<ItemType>* tree)
{
	if (tree != NULL)
	{
		InPrint(tree->left);
		//outFile << tree->info;
		PrintItem(tree);
		InPrint(tree->right);
	}
}

template<class ItemType>
void PrePrint(TreeNode<ItemType>* tree)
{
	if (tree != NULL)
	{
		//outFile << tree->info;
		PrintItem(tree);
		PrePrint(tree->left);
		PrePrint(tree->right);
	}
}

template<class ItemType>
void PostPrint(TreeNode<ItemType>* tree)
{
	if (tree != NULL)
	{
		PostPrint(tree->left);
		PostPrint(tree->right);
		//outFile << tree->info;
		PrintItem(tree);
	}
}


template<class ItemType>
void PrintItem(TreeNode<ItemType>* tree)

{
	cout << "\t " << tree->info.fName << " " << tree->info.lName << " " << tree->info.num << endl;
}



