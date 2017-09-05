#ifndef TREE_H
#define TREE_H
#include "list.h"

struct TreeNode{
	int k;
	List sons;
};

struct Treet{
	struct TreeNode* root;
	int nextNodeNumber;
	//przechowuje listyNody które opakowują TreeNode
	struct ListNode** tab;
	int tabSize;
	int sizeOfTree;
};

typedef struct Treet* Tree;

Tree CREATE_TREE();

void ADD_NODE(Tree t, int k);

void RIGHTMOST_CHILD(Tree t,int k);

void DELETE_NODE(Tree t,int k);

void DELETE_SUBTREE(Tree t,int k);

void SPLIT_NODE(Tree t, int k, int w);

int FREE_TREE(Tree t);

#endif