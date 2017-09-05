#include "list.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>



List CREATE_LIST(){
	List l = (List)malloc(sizeof(struct Listt));
	l->tail = CREATE_LIST_NODE();
	l->head = CREATE_LIST_NODE();
	l->head->next = l->tail;
	l->tail->prev = l->head;
	return l;
}

struct ListNode* CREATE_LIST_NODE(){
	struct ListNode* pom = (struct ListNode*)malloc(sizeof(struct ListNode));
	pom->prev = pom->next = NULL;
	pom->v = NULL;
	return pom;
}

struct ListNode* PUSH_BACK(List l, struct TreeNode* v){
	if( IS_EMPTY(l) ){
		l->head->next = l->tail->prev = CREATE_LIST_NODE();
		l->tail->prev->v = v;
		l->tail->prev->next = l->tail;
		l->tail->prev->prev = l->head;
	} else {
		l->tail->prev->next = CREATE_LIST_NODE();
		l->tail->prev->next->prev = l->tail->prev;
		l->tail->prev->next->next = l->tail;
		l->tail->prev = l->tail->prev->next;
		l->tail->prev->v = v;
	}
	return l->tail->prev;
}

struct ListNode* PUSH_FRONT(List l, struct TreeNode* v){
	if( IS_EMPTY(l) ){
		l->head->next = l->tail->prev = CREATE_LIST_NODE();
		l->tail->prev->v = v;
		l->tail->prev->next = l->tail;
		l->tail->prev->prev = l->head;
	} else {
		l->head->next->prev = CREATE_LIST_NODE();
		l->head->next->prev->next = l->head->next;
		l->head->next->prev->prev = l->head;
		l->head->next = l->head->next->prev;
		l->head->next->v = v;
	}
	return l->head->next;
}

void UNLINK_LIST_NODE(struct ListNode* n){
	if(n->next == NULL && n->prev == NULL){
		return;
	} else if (n->prev == NULL){
		n->next->prev = NULL;
	} else if (n->next == NULL){
		n->prev->next = NULL;
	} else {
		n->prev->next = n->next;
		n->next->prev = n->prev;
	}
}

void REMOVE_BACK(List l){
	if( IS_EMPTY(l) ){
		return;
	} else {
		l->tail->prev = l->tail->prev->prev;
		free(l->tail->prev->next->v);
		free(l->tail->prev->next);
		l->tail->prev->next = l->tail;
	}
}

void REMOVE_FRONT(List l){
	if( IS_EMPTY(l) ){
		return;
	} else {
		l->head->next = l->head->next->next;
		free(l->head->next->prev->v);
		free(l->head->next->prev);
		l->head->next->prev = l->head;
	}
}

struct TreeNode* FRONT(List l){
	if( IS_EMPTY(l) ){
		return 0;
	} else {
		return l->head->next->v;
	}
}
struct TreeNode* BACK(List l){
	if( IS_EMPTY(l) ){
		return 0;
	} else {
		return l->tail->prev->v;
	}
}

int IS_EMPTY(List l){
	if(l->head->next == l->tail) return 1;
	else return 0;
}

int FREE_LIST(List l){
	while(!IS_EMPTY(l)){
		REMOVE_FRONT(l);
	}

	free(l->head);
	free(l->tail);
	free(l);
	return 1;
}
