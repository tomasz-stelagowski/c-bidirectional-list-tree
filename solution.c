#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


int main(int argn, char** argc){
	Tree tree;
	if(argn == 1){
		tree = CREATE_TREE(0);
	} else if(argn == 2 && strcmp(argc[1], "-v") == 0) {
		tree = CREATE_TREE(1);
	} else {
		printf("ERROR\n");
		return 1;
	}

	int nrpol = 0;
		
	while(!feof(stdin)){
		char expr[10] = {0};
		scanf("%s", expr);
		
		int par1, par2;

		nrpol++;

		if( strcmp(expr, "ADD_NODE") == 0){
			scanf("%d", &par1);
			ADD_NODE(tree, par1);
		}
		else if( strcmp(expr, "RIGHTMOST_CHILD") == 0){
			scanf("%d", &par1);
			RIGHTMOST_CHILD(tree, par1);
		}
		else if( strcmp(expr, "DELETE_NODE") == 0){
			scanf("%d", &par1);
			DELETE_NODE(tree, par1);
		}
		else if( strcmp(expr, "DELETE_SUBTREE") == 0){
			scanf("%d", &par1);
			DELETE_SUBTREE(tree, par1);
		}
		else if( strcmp(expr, "SPLIT_NODE") == 0){
			scanf("%d %d", &par1, &par2);
			SPLIT_NODE(tree, par1, par2);
		}
	}



	FREE_TREE(tree);


	return 0;
}