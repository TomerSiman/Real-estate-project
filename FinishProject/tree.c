#include "Header.h"
void makeEmptyTree(APTree* tree)
{
	/* This function will make an empty tree*/
	tree->root = NULL;
} 

APTreeNode* createNewTreeNode(APPARTMENT data, APTreeNode* left, APTreeNode* right)
{
	/* This function will create new tree node */
	APTreeNode* node = (APTreeNode*)malloc(sizeof(APTreeNode));
	checkMemoryAllocation(node);
	node->data = data;
	node->left = left;
	node->right = right;

	return node;
}

void freeTree(APTree tr)
{
	/* This function will free the tree*/
	freeTreeRec(tr.root);
}

void freeTreeRec(APTreeNode* root)
{
	/* This function will free the tree*/
	if (root == NULL)
		return;
	else
	{
		freeTreeRec(root->left);
		freeTreeRec(root->right);
		free(root->data.adrees);
		free(root);
	}
}
void printAppartments(APTree* aptTree)
{
	/* This function will print the appartment tree in-order */
	int i = 1;
	if (aptTree->root == NULL)
	{
		printf("No appartments in database\n");
		return;

	}
	else {
		printf("Apartments in database:\n");
		printAppartmentsHelper(aptTree->root , &i);
	}
}
void printAppartmentsHelper(APTreeNode* root , int* i)
{
	if (root == NULL)
		return;
	else
	{
		printAppartmentsHelper(root->left , i);
		printf("%d. ID: %d Adress: %s Price: %d Number of rooms: %d Date: %d %d %d\n",*i, root->data.code , root->data.adrees, root->data.price, root->data.rooms_number, root->data.entry_date.day, root->data.entry_date.month, root->data.entry_date.year);
		*i = *i + 1;
		printAppartmentsHelper(root->right , i);
	}
}
void insertNodeToTree(APTreeNode* node, APTree* tree)
{
	/* This function will insert a new node to the tree */
	insertNodeToTreeHelper(&(tree->root), node);
}
void insertNodeToTreeHelper(APTreeNode** root, APTreeNode* node)
{
	if (*root == NULL)
		*root = node;
	else if ((*root)->left == NULL && ((*root)->right) == NULL)
	{
		if ((*root)->data.price >= node->data.price)
		{
			(*root)->left = node;
		}
		else
			(*root)->right = node;
	}
	else
	{
		if ((*root)->data.price >= node->data.price)
			insertNodeToTreeHelper(&((*root)->left),node);
		else
			insertNodeToTreeHelper(&((*root)->right),node);
	}
}
bool isEmptyTree(APTreeNode* root)
{
	/* This function will check if a tree is empty */
	if (root == NULL)
		return true;
	else
		return false;
}
void removeAptFromTree(APTree* tr, int price, int code)
{
	/* This function will remove an apartment from the tree */
	removeAptFromTreeHelper(&((*tr).root), price, code);
}
void removeAptFromTreeHelper(APTreeNode** root, int price, int code)
{
	if (*root == NULL)
		return;
	else if ((*root)->data.price < price) // if price bigger then the root price
		removeAptFromTreeHelper(&((*root)->right), price, code);
	else if ((*root)->data.price > price || (*root)->data.code != code) // if price is smaller the the root price or the code is different
		removeAptFromTreeHelper(&((*root)->left), price, code);
	else { // if the root is the right node to delete
		if ((*root)->left == NULL && (*root)->right == NULL) { // leaf
			free((*root)->data.adrees);
			free(*root);
			*root = NULL;
		}
		else if ((*root)->right == NULL) { // left child
			APTreeNode* temp = *root;
			*root = (*root)->left;
			free(temp->data.adrees);
			free(temp);
		}
		else if ((*root)->left == NULL) {
			APTreeNode* temp = *root;
			*root = (*root)->right;
			free(temp->data.adrees);
			free(temp);
		}
		else { // 2 children
			APTreeNode** temp = FindNodeRight(&(*root)->right);
			(*root)->data = (*temp)->data;
			removeAptFromTreeHelper(&(*root)->right, (*temp)->data.price, (*temp)->data.code);
		}
	}
}
APTreeNode** FindNodeRight(APTreeNode** node)
{
	/* This function will find the minimum node in the right sub-tree*/
	if ((*node)->left == NULL) {
		return node;
	}
	else {
		APTreeNode** curr = FindNodeRight(&((*node)->left));
		return curr;
	}
}