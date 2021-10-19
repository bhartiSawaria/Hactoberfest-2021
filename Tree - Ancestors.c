#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
}node;

node* create (int val, char *dir);
void traverse (node *root);
node* search (node *root, int val);
void ancestors (node *root, int val);

int main(void)
{
	node *root;
	int choice,val;
	
	root = NULL;
	
	do
	{
		printf("\n1. Create a tree \n");
		printf("2. Traverse\n");
		printf("3. Find ancestors of a node\n");
		printf("4. Exit\n");
		
		printf("\nEnter your choice : ");
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1:
				root = create (-1, "top");
				printf("\n");
				break;
				
			case 2:
				printf("\n");
				traverse (root);
				printf("\n\n");
				break;
				
			case 3:
				printf("Enter the value whose ancestors are to be printed : ");
				scanf("%d", &val);
				printf("\n");
				ancestors(root, val);
				printf("\n");
				break;
				
			case 4:
				break;
				
			default:
				printf("Invalid choice !! \n");
		}
		
	}
	while (choice != 4);
	
	printf("\n\n<<< Thank you !! >>>\n\n");
	
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
			root->parent = NULL;
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
				root->left->parent = root;
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
				root->right->parent = root;
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

node* search (node *root, int val)
{
	node *temp;
	
	if (root != NULL)
	{
		if (root->data == val)
			return root;
		
		temp = search (root->left, val);
		if (temp != NULL)
			return temp;
			
		return search (root->right, val);
	}
	return NULL;
}

void ancestors (node *root, int val)
{
	node *target, *temp;
	
	target = search (root, val);
	
	if(target != NULL)
	{
		temp = target->parent;
		while (temp != NULL)
		{
			printf("%d ", temp->data);
			temp = temp->parent;
		}
	}
	else
		printf("%d does not exist in the tree\n", val);
}




