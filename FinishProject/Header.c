#include "Header.h"

char* getInput(int* size, char* input)
{
	/* This function will get the input from the user */
	
	int logSize = 0, physSize = 1;
	char* res = (char*)malloc(sizeof(char));
	checkMemoryAllocation(res);
	int c;
	c = getchar();
	while (c != '\n')
	{
		if (logSize == physSize)
		{
			physSize *= 2;
			res = realloc(res, physSize * sizeof(char));
			checkMemoryAllocation(res);
		}
		res[logSize] = c;
		logSize++;
		c = getchar();
	}
	res = (char*)realloc(res, (logSize + 1) * sizeof(char));
	checkMemoryAllocation(res);
	res[logSize] = '\0';
	*size = (logSize + 1);
	return res;
}
void CommandsOperator(char* input, APTreeNode*** APTnodeArr, APTree* aptTree, char** short_term_history, List* orderList, int* node_arr_phys_size, int* node_arr_log_size, int* short_term_history_size, int input_size)
{
	/* This function will get the input command from the user and will work out the command*/
	char* command = strtok(input, " ");
	int command_num = findCommand(command);
	if(command_num == 1)
		addAppertment(APTnodeArr, aptTree, NULL, node_arr_phys_size, node_arr_log_size);
	else if(command_num == 2)
		findAppartment(*APTnodeArr, aptTree, NULL, node_arr_log_size);
	else if(command_num == 3)
		printAppartments(aptTree);
	else if (command_num == 4)
		buyAppartment(APTnodeArr, aptTree, NULL, node_arr_log_size);
	else if (command_num == 5)
		strcpy(input, command);
	else if(command_num == 6)
		printShortTermHistory(short_term_history, short_term_history_size);
	else if(command_num ==7)
	{
		if (isEmptyList(*orderList))
		{
			printf("\nNo commands in database\n");
		}
		else
		{
			printHistory(orderList, short_term_history, short_term_history_size);
		}
	}
	else if (command_num == 8)
	{
		char* copy = (char*)malloc((strlen(short_term_history[N - 1]) + 1) * sizeof(char));
		checkMemoryAllocation(copy);
		strcpy(copy, short_term_history[N - 1]);
		updateHistory(short_term_history, orderList, copy, strlen(copy) + 1, short_term_history_size);
		CommandsOperator(copy, APTnodeArr, aptTree, short_term_history, orderList, node_arr_phys_size, node_arr_log_size, short_term_history_size, (strlen(copy) + 1));
	}
	else if (command_num == 9)
	{
		char c;
		char* new_command, *copy;
		int q;
		sscanf(command, "%c%d", &c, &q);
		if (q > N)
		{
			new_command = searchList(orderList, (q - N));
		}
		else
		{
			new_command = short_term_history[N - q];
		}
		if(new_command == NULL)
			printf("\nCould not retrieve command: command index out of range\n");
		else
		{
			copy = (char*)malloc((strlen(new_command) + 1) * sizeof(char));
			checkMemoryAllocation(copy);
			strcpy(copy, new_command);
			updateHistory(short_term_history, orderList, copy, strlen(copy) + 1, short_term_history_size);
			CommandsOperator(copy, APTnodeArr, aptTree, short_term_history, orderList, node_arr_phys_size, node_arr_log_size, short_term_history_size, strlen(copy) + 1);
		}
	}
	free(command);
}
int findCommand(char* command)
{
	/* This function return a value for each command */
	if (strcmp(command, "add-apt") == 0)
		return 1;
	else if (strcmp(command, "find-apt") == 0)
		return 2;
	else if (strcmp(command, "print-apts") == 0)
		return 3;
	else if (strcmp(command, "buy-apt") == 0)
		return 4;
	else if (strcmp(command, "exit") == 0)
		return 5;
	else if (strcmp(command, "short_history") == 0)
		return 6;
	else if (strcmp(command, "history") == 0)
		return 7;
	else if (strcmp(command, "!!") == 0)
		return 8;
	else
		return 9;


}
void updateHistory(char** short_term_history, List* orderList, char* input, int size, int* short_term_history_size)
{
	/* This function will update the commands history */
	char* copy = (char*)malloc(size * sizeof(char));
	checkMemoryAllocation(copy);
	strcpy(copy, input);
	if (*short_term_history_size < N)
	{
		short_term_history[*short_term_history_size] = copy;
		*short_term_history_size += 1;
	}
	else
	{
		insertDataToEndList(orderList, short_term_history[0], size);
		int i;
		for (i = 0; i < N - 1; i++)
		{
			short_term_history[i] = short_term_history[i + 1];
		}
		short_term_history[N - 1] = copy;
	}
}
void addAppertment(APTreeNode*** APTnodeArr, APTree* aptTree, char* input, int* node_arr_phys_size, int* node_arr_log_size)
{
	/* This function will add a new appartment to the tree and array */
	APPARTMENT data = getData(input);
	data.code = *node_arr_log_size + 1;
	APTreeNode* newNode = createNewTreeNode(data, NULL, NULL);
	insertNodeToArr(APTnodeArr, newNode, node_arr_log_size, node_arr_phys_size);
	insertNodeToTree(newNode, aptTree);
	printf("\nAppartment added succesfully with I.D %d\n\n", newNode->data.code);
}
APPARTMENT getData(char* input)
{
	/* This function will get the appertment data from strtok */
	APPARTMENT res;
	char* adress = strtok(input, "\"");
	res.adrees = (char*)malloc((strlen(adress) + 1) * sizeof(char));
	checkMemoryAllocation(res.adrees);
	strcpy(res.adrees, adress);
	res.price = atoi(strtok(input, " "));
	res.rooms_number = atoi(strtok(input, " "));
	res.entry_date.day = atoi(strtok(input, " "));
	res.entry_date.month = atoi(strtok(input, " "));
	res.entry_date.year = atoi(strtok(input, " "));
	return res;

}
void insertNodeToArr(APTreeNode*** APTnodeArr, APTreeNode* node, int* log_size, int* physSize)
{
	/* This function will insert a new node to the treeNodes array */

	if (*log_size == *physSize)
	{
		*physSize *= 2;
		(*APTnodeArr) = (APTreeNode**)realloc((*APTnodeArr), (*physSize) * sizeof(APTreeNode*));
		checkMemoryAllocation(*APTnodeArr);
	}
	(*APTnodeArr)[*log_size] = node;
	*log_size += 1;
	 
}
void checkMemoryAllocation(void* ptr)
{
	/* This function will check if a memory allocation has succeded */
	if (ptr == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}
}
void findAppartment(APTreeNode** APTnodeArr, APTree* aptTree, char* input, int* node_arr_size)
{
	/* This function will get find the appartment asked by the users cyteria */
	if (isEmptyTree(aptTree->root))
	{
		printf("\nNo appartments in database\n");
		return;
	}
	SEARCH_APPARTMENT apt = getSearchData(input);
	searchApt(apt, aptTree);

}
SEARCH_APPARTMENT getSearchData(char* input)
{
	/* This function will get the data for the appartment asked by the user */
	SEARCH_APPARTMENT res;
	char* token = strtok(input, "- ");
	while (token != NULL)
	{
		if (strcmp(token, "MinPrice") == 0)
		{
			res.min_price = atoi(strtok(input, "- "));
		}
		else if (strcmp(token, "MaxPrice") == 0)
		{
			res.max_price = atoi(strtok(input, "- "));		
		}
		else if (strcmp(token, "MinNumRooms") == 0)
		{
			res.min_rooms_number = atoi(strtok(input, "- "));
			res.min_rooms_flag = 1;
		}
		else if (strcmp(token, "MaxNumRooms") == 0)
		{
			res.max_rooms_num = atoi(strtok(input, "- "));
			res.max_rooms_flag = 1;
		}
		else if (strcmp(token, "Date") == 0)
		{
			token = strtok(input, " ");
			sscanf(token, "%2d", &res.entry_date.day);
			sscanf(token+2, "%2d", &res.entry_date.month);
			sscanf(token+4, "%d", &res.entry_date.year);
			res.date_flag = 1;
		}
		token = strtok(input, "- ");
	}
	return res;
}
void searchApt(SEARCH_APPARTMENT apt, APTree* tr)
{
	/* This function will search the appartments tree for appartments matching the criteria and will print the matching ones codes*/

	int* res = (int*)malloc(sizeof(int));
	checkMemoryAllocation(res);
	int logSize = 0, physSize = 1;
	searchAptHelper(apt, tr->root, &res, &logSize, &physSize);
	if (logSize == 0)
		printf("\nNo appartments matching the criteria found\n\n");
	else
	{
		int i;
		printf("\nThe appartments matching the criteria are: ");
		for (i = (logSize - 1); i >= 0; i--)
		{
			if (i > 0)
				printf("%d, ", res[i]);
			else
				printf("%d.\n\n ", res[i]);
		}
	}
	free(res);
}

void searchAptHelper(SEARCH_APPARTMENT apt, APTreeNode* root , int** res, int* logSize, int* physSize)
{
	/* This function will find the appartments matching the criteria */
	if (root == NULL) 
	{
		return;
	}
	else
	{
		searchAptHelper(apt, root->left, res, logSize, physSize);
		searchAptHelper(apt, root->right, res, logSize, physSize);
		if (aptFound(root->data, apt))
		{
			if (*logSize == *physSize)
			{
				*physSize *= 2;
				*res = (int*)realloc(*res, *physSize * sizeof(int));
				checkMemoryAllocation(*res);
			}
			(*res)[*logSize] = root->data.code;
			*logSize = *logSize + 1;
		}
	}
}

bool aptFound(APPARTMENT apt, SEARCH_APPARTMENT criteria)
{
	/* This function will check if an appartment matches the search criteria */
	if (apt.price > criteria.max_price)
		return false;
	if (apt.price < criteria.min_price)
		return false;
	if (criteria.max_rooms_flag == 1)
	{
		if (apt.rooms_number > criteria.max_rooms_num)
			return false;
	}
	if (criteria.min_rooms_flag == 1)
	{
		if (apt.rooms_number < criteria.min_rooms_number)
			return false;
	}
	if (criteria.date_flag == 1)
	{
		if (apt.entry_date.year < (criteria.entry_date.year%1000))
			return true;
		else if (apt.entry_date.year == (criteria.entry_date.year%1000))
		{
			if (apt.entry_date.month < criteria.entry_date.month)
				return true;
			else if (apt.entry_date.month > criteria.entry_date.month)
				return false;
			else
			{
				if (apt.entry_date.day < criteria.entry_date.day)
					return true;
				else if (apt.entry_date.day > criteria.entry_date.day)
					return false;
				else
					return true;
			}
		}
		else if (apt.entry_date.year > (criteria.entry_date.year%1000))
			return false;
	}
	return true;
}
void printShortTermHistory(char** short_term_history, int* short_term_history_size)
{
	/* This function will print the short term commands history */
	int i;
	for (i = 0; i < *short_term_history_size; i++)
	{
		printf("%d. %s\n", (i + 1), short_term_history[i]);
	}
	printf("\n");
}

void printHistory(List* history , char** short_term_history, int* short_term_history_size) 
{
	/* This function will print the commands history in-order */

	int i, count = 1;
	ListNode* curr = history->tail;
	if (short_term_history_size == 0)
		printf("\nNo commands in database\n\n");
	else if (*short_term_history_size < 7) {
		printf("History:\n");
		for (i = 0; i < *short_term_history_size; i++) {
			printf("%d. %s\n", i+1 , short_term_history[i]);
		}
	}
	else {
		printf("\nHistory:\n");
		while (curr != NULL) {
			printf("%d. %s\n", count, curr->data);
			count++;
			curr = curr->prev;
		}
		for (i = 0; i < *short_term_history_size; i++) {
			printf("%d. %s\n", count , short_term_history[i]);
			count++;
		}
	}
	printf("\n");
}
void buyAppartment(APTreeNode*** APTnodeArr, APTree* aptTree, char* input, int* node_arr_size)
{
	/* This function will fulfill the but appartment order */
	int PriceOfDelete; // price of the node we want to delete.
	int asked_code = atoi(strtok(input, " ")), place;
	if (!isAppartment(APTnodeArr, *node_arr_size, asked_code, &place , &PriceOfDelete))
		printf("Could not purchase appartment with ID %d: no such appartment exists in database \n", asked_code);
	else
	{
		removeAptFromArray(APTnodeArr, *node_arr_size, place);
		*node_arr_size -= 1;
		removeAptFromTree(aptTree, PriceOfDelete ,asked_code);
		printf("\nAppartment with ID %d was succesfully purchased.\n" , asked_code);
	}
}
bool isAppartment(APTreeNode*** APTnodeArr, int arr_size, int asked_code, int* code , int* deletePrice)
{
	/* This function will check if an asked apartment does exist in database */
	int i;
	for (i = 0; i < arr_size; i++)
	{
		if (asked_code == (*APTnodeArr)[i]->data.code)
		{
			*code = i;
			*deletePrice = (*APTnodeArr)[i]->data.price;
			return true;
		}
	}
	return false;
}
void removeAptFromArray(APTreeNode*** APTnodeArr, int node_arr_size, int code)
{
	/* This function will remove an asked apartment from the array */
	int i;
	for (i = code; i < (node_arr_size - 1); i++)
	{
		(*APTnodeArr)[i] = (*APTnodeArr)[i + 1];
	}

	(*APTnodeArr) = (APTreeNode**)realloc((*APTnodeArr), (node_arr_size - 1) * sizeof(APTreeNode*));
	checkMemoryAllocation(*APTnodeArr);
}

void myFree(char* input, APTreeNode** APTnodeArr, List orderList, char** short_term_history, APTree tree, int short_term_history_size)
{
	/* This function will free all of the allocated space */
	int i = 0;
	free(input);
	freeList(orderList);
	freeTree(tree);
	free(APTnodeArr);
	for (i = 0; i < short_term_history_size; i++)
	{
		if(short_term_history[i] != NULL)
			free(short_term_history[i]);
	}
}
void createCommandsTextFile(char** short_term_history, int short_term_history_size, List orderList)
{
	/* This function will save all of the commands in a new txt file */
	FILE* fp = fopen("commands.txt", "w");
	checkMemoryAllocation(fp);
	int i;
	for (i = short_term_history_size - 1; i >= 0; i--)
	{
		fputs(short_term_history[i], fp);
		fputs("\n", fp);
	}
	ListNode* curr = orderList.tail;
	while (curr != NULL)
	{
		fputs(curr->data, fp);
		fputs("\n", fp);
		curr = curr->prev;
	}
	fclose(fp);
}
void createAppartmentsBinFile(APTreeNode** APTnodeArr, int  node_arr_log_size)
{
	/* This function will save all of the appartments data of a binary file */
	FILE* fp = fopen("apartments.bin", "wb");
	checkMemoryAllocation(fp);
	BYTE* roomsNum_date = (BYTE*)malloc(numBytes * sizeof(BYTE));
	checkMemoryAllocation(roomsNum_date);
	int i;
	short int size;
	for (i = 0; i < node_arr_log_size; i++)
	{
		fwrite(&APTnodeArr[i]->data.code, sizeof(short int), 1, fp);
		size = (short int)strlen(APTnodeArr[i]->data.adrees);
		fwrite(&size, sizeof(short int), 1, fp);
		fwrite(&APTnodeArr[i]->data.adrees, sizeof(char), size, fp);
		fwrite(&APTnodeArr[i]->data.price, sizeof(int), 1, fp);
		convertToBytes(APTnodeArr[i]->data.entry_date, APTnodeArr[i]->data.rooms_number, &roomsNum_date);
		fwrite(&roomsNum_date, sizeof(BYTE), numBytes, fp);
	}

	free(roomsNum_date);
	fclose(fp);
}
void convertToBytes(DATE date, short int roomsNum, BYTE** roomsNum_date)
{
	/* This function will convert the asked data into bytes */
	int i;
	for (i = 0; i < numBytes; i++)
		(*roomsNum_date)[i] = 0x00;
	BYTE mask = roomsNum << 4;
	(*roomsNum_date)[0] = (*roomsNum_date)[0] | mask;
	BYTE dayMask1 = date.day >>1;
	BYTE dayMask2 = date.day <<7;
	(*roomsNum_date)[0] = (*roomsNum_date)[0] | dayMask1;
	(*roomsNum_date)[1] = (*roomsNum_date)[1] | dayMask2;
	BYTE monthMask = date.month << 3;
	(*roomsNum_date)[1] = (*roomsNum_date)[1] | monthMask;
	int year = date.year % 2000;
	BYTE yearMask1 = year >> 4;
	BYTE yearMask2 = year << 4;
	(*roomsNum_date)[1] = (*roomsNum_date)[1] | yearMask1;
	(*roomsNum_date)[2] = (*roomsNum_date)[2] | yearMask2;

}