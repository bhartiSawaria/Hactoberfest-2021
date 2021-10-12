#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *left, *right;
}node;


node* create (int val, char *dir);
void traverse (node *root);
int checkSkewed (node *root);


int main()
{
	int choice, temp;
	
	node *root;
	
	root = NULL;
	
	do
	{
		printf("\n\n1. Create\n");
		printf("2. Traverse\n");
		printf("3. Check skewed\n");
		printf("4. Exit\n");
		
		printf("Enter your choice : ");
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1:
				root = create (-1, "top");
				break;
				
			case 2:
				printf("\n The elements are \n");
				traverse (root);
				printf("\n");
				break;
				
			case 3:
				temp = checkSkewed (root);
				
				if (temp )
					printf("The tree is skewed ... \n");
				else
					printf("Ooo !! The tree is not skewed !! \n");
					
				break;
				
			case 4:
				break;
				
			default:
				printf("Invalid choice !! \n");
				
		}
	}
	while (choice != 4);
	
	
	return 0;
}

node* create (int val, char *dir)
{
	int choice;
	node *root;
	
	root = (node*) malloc (sizeof (node));
	if (root != NULL)
	{
		if (val == -1)
		{
			printf("Enter the value at top : ");
			scanf("%d", &(root->data));
		}
		else
		{
			printf("Enter the value at %s branch of %d : ", dir, val);
			scanf("%d", &(root->data));
		}
		
		printf("Is there a left branch of %d (1/0) : ", root->data);
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
				printf("Invalid choice\n");
				root->left = NULL;
		}
		
		printf("Is there a right branch of %d (1/0) : ", root->data);
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
				printf("Invalid choice\n");
				root->right = NULL;
		}
		
	}
	else
		printf("Memory allocation not possible !\n");
	
	return root;
}

void traverse (node *root)
{
	if (root != NULL)
	{
		traverse (root->left);
		printf("%d ", root->data);
		traverse (root->right);
	}
}

int checkSkewed (node *root)
{
	if (root == NULL)
		return 1;
	
	if (root->left == NULL)
		return checkSkewed (root->right);
	
	if (root->right == NULL)
		return checkSkewed (root->left);
	
	return 0;
}




