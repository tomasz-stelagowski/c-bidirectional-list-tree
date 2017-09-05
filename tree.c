#include "list.h"
#include "tree.h"
#include "stdio.h"
#include <stdlib.h>
#include <stdio.h>

int diagnostic = 0;

void output(char* msg, int num){
	printf("%s\n", msg);
	if(diagnostic == 1){
		fprintf(stderr, "NODES: %d\n", num);
	}
}

Tree CREATE_TREE(int diagn){
	if(diagn) diagnostic = diagn;

	Tree tree = (Tree)malloc(sizeof(struct Treet));

	tree->root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	tree->root->k = 0;
	tree->root->sons = CREATE_LIST();

	tree->nextNodeNumber = 1;

	tree->tab = (struct ListNode**)malloc(10*sizeof(struct ListNode*));
	tree->tabSize = 10;
	tree->tab[0] = (struct ListNode*)CREATE_LIST_NODE();
	tree->tab[0]->v = tree->root;

	tree->sizeOfTree = 1;

	return tree;
}

struct TreeNode* CREATE_TREE_NODE(Tree t){
	if(t->nextNodeNumber >= t->tabSize){
		t->tabSize = 2* t->tabSize;
		t->tab = (struct ListNode**)realloc((t->tab), (t->tabSize) * sizeof(struct TreeNode*));
	}
	struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	newNode->sons = CREATE_LIST();
	newNode->k = t->nextNodeNumber;
	t->nextNodeNumber = t->nextNodeNumber + 1;

	t->sizeOfTree = t->sizeOfTree + 1;

	return newNode;
}

void ADD_NODE(Tree t, int k){
	struct TreeNode* newTreeNode = CREATE_TREE_NODE(t);

	struct ListNode* newListNode = PUSH_BACK(t->tab[k]->v->sons, newTreeNode);
	t->tab[newTreeNode->k] = newListNode;

	output("OK", t->sizeOfTree);
}

void RIGHTMOST_CHILD(Tree t,int k){
	if(IS_EMPTY(t->tab[k]->v->sons)){
		output("-1", t->sizeOfTree);
	} else {
		char msg[31];
		sprintf(msg, "%d", ((BACK(t->tab[k]->v->sons))->k));
		output(msg, t->sizeOfTree);
	}
}

void DELETE_NODE(Tree t,int k){
	//Connect sons of k in k place
	if(!IS_EMPTY(t->tab[k]->v->sons)){
		
		t->tab[k]->prev->next = t->tab[k]->v->sons->head->next;
		t->tab[k]->v->sons->head->next->prev = t->tab[k]->prev;
		t->tab[k]->next->prev = t->tab[k]->v->sons->tail->prev;
		t->tab[k]->v->sons->tail->prev->next = t->tab[k]->next;

		t->tab[k]->v->sons->tail->prev = t->tab[k]->v->sons->head;
		t->tab[k]->v->sons->head->next = t->tab[k]->v->sons->tail;
	
	} else {
		UNLINK_LIST_NODE(t->tab[k]);
	}

	FREE_LIST(t->tab[k]->v->sons);

	free(t->tab[k]->v);
	free(t->tab[k]);
	t->tab[k] = NULL;

	t->sizeOfTree = t->sizeOfTree-1;

	output("OK", t->sizeOfTree);
}

void DELETE_SUBTREE_INNER_RECURSION(Tree t, int k){
	while(!IS_EMPTY(t->tab[k]->v->sons)){
		DELETE_SUBTREE_INNER_RECURSION(t, (FRONT(t->tab[k]->v->sons))->k);
	}

	UNLINK_LIST_NODE(t->tab[k]);

	FREE_LIST(t->tab[k]->v->sons);
	free(t->tab[k]->v);
	free(t->tab[k]);
	t->tab[k] = NULL;

	t->sizeOfTree = t->sizeOfTree-1;
}

void DELETE_SUBTREE(Tree t, int k){
	DELETE_SUBTREE_INNER_RECURSION(t, k);
	output("OK", t->sizeOfTree);
}

void SPLIT_NODE(Tree t, int k, int w){
	struct TreeNode* newTreeNode = CREATE_TREE_NODE(t);

	struct ListNode* kl = PUSH_BACK(t->tab[k]->v->sons, newTreeNode);
	t->tab[newTreeNode->k] = kl;

	struct ListNode* wl = t->tab[w];

	if(kl->prev != wl){
		//relink sibing between kl and wl to kl
		kl->v->sons->head->next = wl->next;
		kl->v->sons->tail->prev = kl->prev;

		kl->v->sons->head->next->prev = kl->v->sons->head;
		kl->v->sons->tail->prev->next = kl->v->sons->tail;

		kl->prev = wl;
		wl->next = kl;
	}

	output("OK", t->sizeOfTree);
}

int FREE_TREE(Tree t){
	/*while(!IS_EMPTY(t->root->sons)){
		DELETE_SUBTREE_INNER_RECURSION(t, FRONT(t->root->sons)->k);
	}
	FREE_LIST(t->root->sons);
	free(t->root);
	free(t->tab[0]);
	free(t->tab);
	free(t);
*/
	DELETE_SUBTREE_INNER_RECURSION(t, 0);

	free(t->tab);
	free(t);
	return 1;
}