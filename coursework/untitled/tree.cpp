#ifndef TREE_CPP
#define TREE_CPP

#define MAX_LEN 20

#include "tree.h"

using namespace std;

template <class Type>
Tree<Type>::Tree()
{
	root = NULL;
}

template <class Type>
void Tree<Type>::createTree(Type key, tree<Type> *leaf)
{
	if (key< leaf->info)
	{
		if (leaf->left != NULL)
			createTree(key, leaf->left);
		else
		{
			leaf->left = new tree<Type>;
			leaf->left->parent = leaf;
			leaf->left->info = key;
			leaf->left->repeats = 1;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	}
	else if (key > leaf->info)
	{
		if (leaf->right != NULL)
			createTree(key, leaf->right);
		else
		{
			leaf->right = new tree<Type>;
			leaf->right->parent = leaf;
			leaf->right->info = key;
			leaf->right->repeats = 1;
			leaf->right->left = NULL;
			leaf->right->right = NULL;
		}
	}
	else if (key == leaf->info)
		leaf->repeats++;
}

template <class Type>
void Tree<Type>::createTree(Type key)
{
	if (root != NULL)
		createTree(key, root);
	else
	{
		root = new tree<Type>;
		root->info = key;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		root->repeats = 1;
	}
	setIndex();
}

template <class Type>
void Tree<Type>::deleteNode(QString data)
{
	tree<Type> *parentNode, *currentNode, *tempNode;
	int flag, find = 0;
    Type ptr;
	if (!root)
	{
		return;
	}

	currentNode = parentNode = root;
	flag = 0;
	do
	{
        if (parentNode->info.getModel() == data)
		{
			flag = 1;
			find = 1;
		}

        if (parentNode->info.getModel() < data)
		{
			if (parentNode->right)
			{
				currentNode = parentNode;
				parentNode = parentNode->right;
			}
			else
				flag = 1;
		}

        if (parentNode->info.getModel() > data)
		{
			if (parentNode->left)
			{
				currentNode = parentNode;
				parentNode = parentNode->left;
			}
			else
				flag = 1;
		}
	} while (!flag);

	if (!find)
	{
		return;
	}
    else
	{
		tempNode = parentNode;
        if (parentNode->info.getModel() < currentNode->info.getModel())
		{
			tempNode = parentNode->right;
			if (!tempNode)
			{
				if(!parentNode->left)
					currentNode->left = NULL;
				else
					currentNode->left = parentNode->left;
			}
			else
			{
				currentNode->left = parentNode->right;
				tempNode->parent = currentNode;
				while (tempNode->left)
					tempNode = tempNode->left;
				tempNode->left = parentNode->left;
                if (parentNode->left)
					parentNode->left->parent = tempNode;
			}
		}
        else if (parentNode->info.getModel() > currentNode->info.getModel())
		{
			tempNode = parentNode->left;
			if (!tempNode)
			{
				if(!parentNode->right)
					currentNode->right = NULL;
				else
					currentNode->right = parentNode->right;
			}
			else
			{
				currentNode->right = parentNode->left;
				tempNode->parent = currentNode;
				while (tempNode->right)
					tempNode = tempNode->right;
				tempNode->right = parentNode->right;
                if (parentNode->right)
					parentNode->right->parent = tempNode;
			}
		}
		else
		{
			if (root->right)
			{
				tempNode = root->right;
				while (tempNode->left)
					tempNode = tempNode->left;
				tempNode->left = root->left;
				root = root->right;
                root->parent = NULL;
			}
			else if (root->left)
			{
				root = root->left;
                root->parent = NULL;
			}
			else
            {
                root = NULL;
			}
		}
	}
    delete parentNode;
	setIndex();
}

template <class Type>
void Tree<Type>::deleteTree()
{
	tree<Type> * tr = root;
	if (tr != NULL)
	{
		deleteTree(tr->left);
		deleteTree(tr->right);
		delete tr;
	}
}

template <class Type>
void Tree<Type>::deleteTree(tree<Type> * tr)
{
	if (tr != NULL)
	{
		deleteTree(tr->left);
		deleteTree(tr->right);
		delete tr;
	}
}

template <class Type>
Tree<Type>::~Tree()
{
}

template <class Type>
Type* Tree<Type>::search(QString data)
{
	tree<Type>* p = root;   
    while (p != NULL)
	{
        if (data < p->info.getModel())
			p = p->left;  
        else if (data > p->info.getModel())
			p = p->right; 
		else       
			return &p->info; 
    }
	return NULL;
}


template <class Type>
bool Tree<Type>::emptyTree()
{
    if (root == NULL)
        return true;
    else return  false;
}
#endif

