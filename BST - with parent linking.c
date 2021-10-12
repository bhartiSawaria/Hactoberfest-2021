// Binary search tree with parent linking

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
}node;

node* create ();
void traverseInOrder (node *root);
node* insert (node *root, int val);
node* search (node *root, int val);
node* deleteNode (node* root, int val);
node* successor (node *x);

int main()
{
	int choice,val,temp;
	node *root;
	
	root = NULL;
	
	do
	{
		printf("\n 1.Create\n");
		printf(" 2.Traverse in-order\n");
		printf(" 3.Insert\n");
		printf(" 4.Delete\n");
		printf(" 5.Exit\n");
		printf(" Enter your choice : ");
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1:
				root = create();
				break;
				
			case 2:
				printf("The list in-order is \n");
				traverseInOrder(root);
				printf("\n");
				break;
			
			case 3:
				printf("Enter the value to be inserted : ");
				scanf("%d", &val);
				root = insert(root, val);
				printf("Successfully inserted ... \n");
				break;
				
			case 4:
				printf("Enter the value to be deleted : ");
				scanf("%d", &val);
				root = deleteNode (root, val);	
				break;
			
			case 5:
				break;
				
			default:
				printf("Invalid choice !! \n");
		}
	}
	while (choice != 5);
	
	printf("Thank you ... \n");
	
	return 0;
}

node* create ()
{
	node *root;
	int choice,val;
	
	root = NULL;
	
	do
	{
		printf("Want to enter a node (1/0): ");
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1:
				printf("Enter the new value : ");
				scanf("%d", &val);
				root = insert (root, val);
				break;
			
			case 0:
				break;
				
			default:
				printf("Invalid choice !! \n");
		}
	}
	while (choice != 0);
	
	return root;
}

void traverseInOrder (node *root)
{
	if (root != NULL)
	{
		traverseInOrder (root->left);
		printf("%d ", root->data);
		traverseInOrder (root->right);
	}
}


node* insert (node *root, int val)
{
	node *newNode;
	
	if (root == NULL)
	{
		newNode = (node*) malloc (sizeof (node));
		if (newNode != NULL)
		{
			newNode->data = val;
			newNode->left = NULL;
			newNode->right = NULL;
			newNode->parent = NULL;
			root = newNode;
		}
		else
			printf("Memory allocation not possible !! \n");
	}
		
	else
	{
		if (val < root->data)
		{
			newNode = insert (root->left, val);
			root->left = newNode;
		}
			
		else if (val > root->data)
		{
			newNode = insert (root->right, val);
			root->right = newNode;
		}
		newNode->parent = root;
	}
	
	return root;
}

node* search (node *root, int val)
{
	if (root == NULL)
		return NULL;
		
	if (val == root->data)
		return root;
		
	if (val < root->data)
		return search (root->left, val);
	
	//if (val > root->data)
	return search (root->right, val);
}

node* deleteNode (node* root, int val)
{
	node *delNode, *parentNode, *s;
	
	delNode = search(root, val);
	
	if (delNode != NULL)
	{
		parentNode = delNode->parent;
		
		if (delNode->left == NULL && delNode->right == NULL) // if delNode is a leaf node
		{
			if (parentNode != NULL)
			{
				if (parentNode->left == delNode)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;
			}
		 	
			if(root == delNode)
				root = NULL;
				
			free (delNode);
		}
		
		else if (delNode->left == NULL || delNode->right == NULL) // if delNode is a single child node
		{
			if(delNode->left != NULL)
			{
				if (parentNode != NULL)
				{
					if (parentNode->left == delNode)
						parentNode->left = delNode->left;
					else
						parentNode->right = delNode->left;
				}
					
				delNode->left->parent = parentNode;
				
				if (root == delNode)
					root = delNode->left;
			}
			 
			else                                                      // if delNode->right != NULL
			{
				if (parentNode != NULL)
				{
					if (parentNode->left == delNode)
						parentNode->left = delNode->right;
					else
						parentNode->right = delNode->right;
				}
				delNode->right->parent = parentNode;
			
				if (root == delNode)
					root = delNode->right;
					
			}

			free (delNode);
		}
		
		else // if delNode is a two child node
		{
			s = successor (delNode);
			delNode->data = s->data;
			s = deleteNode (s ,s->data);
		}
		
		
		printf("Successfully deleted ... \n");
	}
	else
		printf("Value does not exist in the list !! \n");
		
	return root;
}

node* successor (node *x)  // find the value which is printed just after x value in inOrder traversal
{
	node *y;
	
	if (x->right != NULL)
	{
		y = x->right;
		while (y->left != NULL)
			y = y->left;
	}
	else
	{
		y = x->parent;
		
		while (y != NULL && y->right==x)
		{
			x = y;
			y = y->parent;
		}
	}
	return y;
}
