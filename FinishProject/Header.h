#ifndef _A_H
#define _A_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define N 7
#define numBytes 3

typedef struct
{
	short int day;
	short int month;
	short int year;
} DATE;
typedef struct
{
	int code;
	char* adrees;
	int price;
	short int rooms_number;
	DATE entry_date;
} APPARTMENT;
typedef struct
{
	int min_rooms_flag , max_rooms_flag , date_flag;
	int min_price;
	int max_price;
	short int min_rooms_number, max_rooms_num;
	DATE entry_date;
} SEARCH_APPARTMENT; // This struct will help find apartments according to the user's demands
typedef struct listNode
{
	char* data;
	struct listNode* next;
	struct listNode* prev;
} ListNode;
typedef struct 
{
	ListNode* head;
	ListNode* tail;
} List;
typedef struct aptreeNode
{
	APPARTMENT data;
	struct aptreeNode* left;
	struct aptreeNode* right;
}APTreeNode;
typedef struct
{

	APTreeNode* root;

}APTree;
typedef unsigned char BYTE;

//etc

char* getInput(int* size, char* input);
void CommandsOperator(char* input, APTreeNode*** APTnodeArr, APTree* aptTree, char** short_term_history, List* orderList, int* node_arr_phys_size, int* node_arr_log_size, int* short_term_history_size, int input_size);
void updateHistory(char** short_term_history, List* orderList, char* input, int size, int* short_term_history_size);
void addAppertment(APTreeNode*** APTnodeArr, APTree* aptTree, char* input, int* node_arr_phys_size, int* node_arr_log_size);
void findAppartment(APTreeNode** APTnodeArr, APTree* aptTree, char* input, int* node_arr_size);
int findCommand(char* command);
APPARTMENT getData(char* input);
void insertNodeToArr(APTreeNode*** APTnodeArr, APTreeNode* node, int* log_size, int* physSize);
void checkMemoryAllocation(void* ptr);
SEARCH_APPARTMENT getSearchData(char* input);
void searchApt(SEARCH_APPARTMENT apt, APTree* tr);
void searchAptHelper(SEARCH_APPARTMENT apt, APTreeNode* root, int** res, int* logSize, int* physSize);
bool aptFound(APPARTMENT apt, SEARCH_APPARTMENT criteria);
void printShortTermHistory(char** short_term_history, int* short_term_history_size);
void printHistory(List* history, char** short_term_history, int* short_term_history_size);
void buyAppartment(APTreeNode*** APTnodeArr, APTree* aptTree, char* input, int* node_arr_size);
bool isAppartment(APTreeNode*** APTnodeArr, int arr_size, int asked_code, int* code, int* deletePrice);
void removeAptFromArray(APTreeNode*** APTnodeArr,int node_arr_size,int asked_code);
void createCommandsTextFile(char** short_term_history, int short_term_history_size, List orderList);
void createAppartmentsBinFile(APTreeNode** APTnodeArr,int  node_arr_log_size);
void convertToBytes(DATE date, short int roomsNum, BYTE** roomsNum_date);
void myFree(char* input, APTreeNode** APTnodeArr, List orderList, char** short_term_history, APTree tree, int short_term_history_size);

// tree functions

void makeEmptyTree(APTree* tree);
APTreeNode* createNewTreeNode(APPARTMENT data, APTreeNode* left, APTreeNode* right);
void freeTree(APTree tr);
bool isEmptyTree(APTreeNode* root);
void freeTreeRec(APTreeNode* root);
void printAppartments(APTree* aptTree);
void printAppartmentsHelper(APTreeNode* root, int* i);
void insertNodeToTree(APTreeNode* node, APTree* tree);
void insertNodeToTreeHelper(APTreeNode** root, APTreeNode* node);
void searchAptHelper(SEARCH_APPARTMENT apt, APTreeNode* root, int** res, int* logSize, int* physSize);
void removeAptFromTree(APTree* tr, int price, int code);
void removeAptFromTreeHelper(APTreeNode** root, int price, int code);
APTreeNode** FindNodeRight(APTreeNode** node);


// List Functions


ListNode* createNewListNode(char* data, ListNode* next, ListNode* prev);
void makeEmptyList(List* lst);
bool isEmptyList(List lst);
void insertDataToEndList(List* lst, char* data, int size);
void insertNodeToEndList(List* lst, ListNode* newTail);
void freeList(List lst);
void printList(List lst);
int listLen(List lst);
char* searchList(List* orderList, int commandNum);




#endif