/* Yuval Levy- 209370378, Tomer Siman-Tov- 206841073 */
/* This program will produce a stock of apartments and handle the buying and selling of them, and also other requests from the user*/
#include "Header.h"

void main() {

	int node_arr_phys_size = 1, input_size, short_term_history_size = 0, node_arr_log_size = 0;
	APTreeNode** APTnodeArr = (APTreeNode**)malloc(sizeof(APTreeNode*));
	APTree aptTree;
	char* short_term_history[N];
	List orderList;
	char* input = getInput(&input_size, input);
	makeEmptyTree(&aptTree);
	makeEmptyList(&orderList);
	while (strcmp(input, "exit") != 0)
	{
		if ((strcmp(input, "history") != 0) && (strcmp(input, "short_history") != 0) && (input[0] != '!'))
			updateHistory(short_term_history, &orderList, input, input_size, &short_term_history_size);
		CommandsOperator(input, &APTnodeArr, &aptTree, short_term_history, &orderList, &node_arr_phys_size, &node_arr_log_size, &short_term_history_size, input_size);
		input = getInput(&input_size, input);
	}
	updateHistory(short_term_history, &orderList, input, input_size, &short_term_history_size);
	createCommandsTextFile(short_term_history, short_term_history_size, orderList);
	createAppartmentsBinFile(APTnodeArr, node_arr_log_size);
	myFree(input, APTnodeArr, orderList, short_term_history, aptTree, short_term_history_size);

}