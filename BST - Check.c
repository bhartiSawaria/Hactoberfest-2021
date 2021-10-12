#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}node;

node* create (int val, char *dir);
void traverse (node *root);
int checkBST (node *root, int low, int high);

int main()
{
	node *root;
	int choice;
	
	root = NULL;
	
	do
	{
		printf("\n\nWant to enter a test case (1/0) : ");
		scanf("%d", &choice);
	
		switch (choice)
		{
			case 1:
				printf("\nEnter the tree \n");
				root = create (-1,"top");
				traverse (root);
			
				if ( checkBST (root, INT_MIN, INT_MAX) )
					printf("The tree is BST \n");
				else
					printf("The tree is not a BST \n");
				break;
			
			case 0:
				break;
				
			default:
				printf("Invalid choice !! \n");
		}
	}
	while (choice != 0);
	
	printf("\n\nThank you !! \n\n");
	
	return 0;
}

node* create (int val, char* dir)
{
	node *root;
	int choice;
	
	root = (node*) malloc (sizeof (node));
	
	if (root != NULL)
	{
		if (val == -1)
		{
			printf("Enter the data at top : ");
			scanf("%d", &(root->data));
		}
		else
		{
			printf("Enter the data in the %s branch of %d : ", dir, val);
			scanf("%d", &(root->data));
		}

		printf("Is there a left branch of %d ? (1=Yes, 0=No): ", root->data);
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1:
				root->left = create (root->data, "left");
				break;
				
			case 0:
				root->left = NULL;
				break;
				
			default:
				printf("Invalid choice !! \n");
				root->left = NULL;
		}
		
		printf("Is there a right branch of %d ? (1=Yes, 0=No): ", root->data);
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1:
				root->right = create (root->data, "right");
				break;
				
			case 0:
				root->right = NULL;
				break;
				
			default:
				printf("Invalid choice !! \n");
				root->right = NULL;
		}
		
	}
	else
		printf("Memory allocation not possible !! \n");
		
	return root;
}


void traverse (node *root)
{
	node *temp;
	
	if(root != NULL)
	{
		traverse (root->left);
		printf("%d ", root->data);
		traverse (root->right);
	}
}

int checkBST (node *root, int low, int high)
{
	if (root == NULL)
		return 1;
	
	if (!(root->data > low && root->data < high))
		return 0;

	if ( checkBST (root->left, low, root->data) == 0)
		return 0;
		
	if ( checkBST (root->right, root->data, high) == 0)
		return 0;

	return 1;
}


