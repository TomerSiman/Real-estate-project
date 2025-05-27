
#include "Header.h"


void makeEmptyList(List* lst)
{
	/* This function will create a new empty list */
	lst->head = lst->tail = NULL;
}

bool isEmptyList(List lst)
{
	/* This function will check if a list is empty */
	return (lst.head == NULL);
}


void freeList(List lst)
{
	/* This function will free a list */
	ListNode* curr = lst.head, * next;

	while (curr != NULL)
	{
		next = curr->next;
		free(curr->data);
		free(curr);
		curr = next;
	}
}


void printList(List lst)
{
	/* This function will print a whole list */
	ListNode* curr = lst.head;

	while (curr != NULL)
	{
		printf("%s ", curr->data);
		curr = curr->next;
	}
}

int listLen(List lst)
{
	/* This function will return a list length */
	ListNode* curr = lst.head;
	int len = 0;

	while (curr != NULL)
	{
		len++;
		curr = curr->next;
	}

	return len;
}


char* searchList(List* orderList, int commandNum)
{
	/* This function will search the orders history for a given number of command  */
	ListNode* curr = orderList->tail;;
	int i = 1;
	while (curr != NULL)
	{
		if (i == commandNum)
			return curr->data;
		curr = curr->prev;
		i++;
	}
	return NULL;
}
void insertDataToEndList(List* lst, char* data , int size)
{
	/* This function will insert a new data to the end of the order list */
	ListNode* newTail;
	newTail = createNewListNode(data, NULL, NULL);
	insertNodeToEndList(lst, newTail);
}
void insertNodeToEndList(List* lst, ListNode* tail)
{
	/* This function will insert a new node to the end of the order list */
	if (isEmptyList(*lst) == true)
	{
		tail->next = tail->prev = NULL;
		lst->head = lst->tail = tail;
	}
	else
	{
		tail->prev = lst->tail;
		tail->next = NULL;
		lst->tail->next = tail;
		lst->tail = tail;
	}
}
ListNode* createNewListNode(char* data, ListNode* next, ListNode* prev)
{
	/* This function will create a new list node */
	ListNode* res;
	res = (ListNode*)malloc(sizeof(ListNode));
	checkMemoryAllocation(res);
	res->data =data;
	res->next = next;
	res->prev = prev;
	return res;
}
