#ifndef LIST_H
#define LIST_H

struct ListNode{
	struct TreeNode* v;
	struct ListNode *prev, *next;
};

struct Listt{
	struct ListNode* head;
	struct ListNode* tail;
};

typedef struct Listt* List;

List CREATE_LIST();

struct ListNode* CREATE_LIST_NODE();

struct ListNode* PUSH_BACK(List l, struct TreeNode* v);

struct ListNode* PUSH_FRONT(List l, struct TreeNode* v);

int IS_EMPTY(List l);

struct TreeNode* FRONT(List l);

struct TreeNode* BACK(List l);

void UNLINK_LIST_NODE(struct ListNode* n);

void REMOVE_FRONT(List l);

void REMOVE_BACK(List l);

int FREE_LIST(List l);

#endif