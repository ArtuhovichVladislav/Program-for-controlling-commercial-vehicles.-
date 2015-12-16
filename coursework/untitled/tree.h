#ifndef TREE_H
#define TREE_H
#include <QString>
#include <iostream>

using namespace std;

template <class Type>
struct tree
{
	Type info;			
	int repeats;	
	int index;
    bool hidden = false;
    struct tree<Type> *left;
    struct tree<Type> *right;
    struct tree<Type> *parent;
};

template <class Type>
class Tree
{
	private:
        tree<Type> *root;
		int index;
        void createTree(Type, tree<Type> *);
	public:

		Tree();
		void showTree();
		
		void createTree(Type);
        void deleteNode(QString data);
		void deleteTree();
		void deleteTree(tree<Type> *);
        Type *search(QString data);
		bool emptyTree();
        tree<Type> *getRoot()
        {
            return root;
        }

		~Tree();
		
		Tree<Type> operator = (tree<Type> *temp)
		{
			root = temp;
			
			return *this;
		}

		int size()
		{
			return size(root);
		}

		int size(tree<Type>* node)
		{
			if (node == NULL)
			{
				return 0;
			}
			else
			{
				return(size(node->left) + 1 + size(node->right));
			}
		}
		
		void setIndex()
		{
			if (!root)
				return;
			index = 0;
			if (root->left)
			{
				indexLeft(root->left);
				index++;
			}
			root->index = index;
			if (root->right)
			{
				indexRight(root->right);
			}
			
		}

		void indexLeft(tree<Type> *tr)
		{
			if (tr->left)
			{
				indexLeft(tr->left);
				index++;
			}
			tr->index = index;
			if (tr->right)
			{
				indexRight(tr->right);
			}
		}

		void indexRight(tree<Type> *tr)
		{
			index++;
			if (tr->left)
			{
				indexLeft(tr->left);
				index++;
			}
			tr->index = index;
			if (tr->right)
			{
				indexRight(tr->right);
			}
		}

        tree<Type> *searchNode(QString data)
        {
            tree<Type>* p = root;
            while (p != NULL)
            {
                if (data < p->info.getModel())
                    p = p->left;
                else if (data > p->info.getModel())
                    p = p->right;
                else
                    return p;
            }
            return NULL;
        }

        void setNodeHidden(QString data)
        {
            tree<Type> *temp = searchNode(data);
            temp->hidden = true;
        }

        void unsetNodeHidden(QString data)
        {
            tree<Type> *temp = searchNode(data);
            if(temp->hidden)
                temp->hidden = false;
        }

		class iterator
		{
			friend class Tree<Type>;
		private:
			tree<Type> *nodePtr;
			Tree<Type> *tr;
			iterator() :nodePtr(NULL)
			{}
			iterator(tree<Type> *p) : nodePtr(p)
			{}
		public:
            tree<Type> *getNodeptr()
            {
                return nodePtr;
            }

			bool operator ==(iterator& item)
			{
				return nodePtr == item.nodePtr;
			}

			bool operator != (iterator& item)
			{
				return nodePtr != item.nodePtr;
			}

			bool operator <=(iterator& item)
			{
				return nodePtr <= item.nodePtr;
			}

			Type& operator *() const
			{
				return nodePtr->info;
			}

            iterator& operator++ ()
            {
                tree<Type> *p;
                if (nodePtr == NULL)
                {
                    nodePtr = tr->root;

                    while (nodePtr->left != NULL)
                    {
                        nodePtr = nodePtr->left;
                    }
                }
                else
                    if (nodePtr->right != NULL)
                    {
                        nodePtr = nodePtr->right;

                        while (nodePtr->left != NULL)
                        {
                            nodePtr = nodePtr->left;
                        }
                    }
                else
                {
                    p = nodePtr->parent;
                    while (p != NULL && nodePtr == p->right)
                    {
                        nodePtr = p;
                        p = p->parent;
                    }
                    nodePtr = p;
                }
                return *this;
            }
            /*iterator& operator++()
			{
				int index = nodePtr->index + 1;
				tree<Type>* curr = nodePtr;

                if (curr->parent)
					while (curr->parent)
						curr = curr->parent;
				while (1)
				{
					if (curr->index > index)
					{
						if (curr->left)
							curr = curr->left;
						else return *this;
					}
					else
					{
						if (curr->index != index)
						{
							if (curr->right)
								curr = curr->right;
							else return *this;
						}
						else  break;
					}
				}
				nodePtr = curr;
				return *this;
            }*/

			iterator& operator--()
			{
				int index = nodePtr->index - 1;
				tree<Type>* curr = nodePtr;

				if (curr->parent)
					while (curr->parent)
						curr = curr->parent;
				while (1)
				{
					if (curr->index > index)
					{
						if (curr->left)
							curr = curr->left;
						else return *this;
					}
					else
					{
						if (curr->index != index)
						{
							if (curr->right)
								curr = curr->right;
							else return *this;
						}
						else  break;
					}
				}
				nodePtr = curr;
				return *this;
			}

			Type& operator[](int i)
			{
				int index = nodePtr->index;
				while (index != i)
				{
					(*this)++;
					index++;
				}
				return nodePtr->info;
			}
		};

		iterator begin()
		{
			tree<Type> *curr = root;
			if (curr != NULL)
			while (curr->left != NULL)
				curr = curr->left;
			return iterator(curr);
		}

		iterator end()
		{
			tree<Type> *curr = root;
			if (curr != NULL)
			while (curr->right != NULL)
				curr = curr->right;
			return iterator(curr);
		}
};
#endif
