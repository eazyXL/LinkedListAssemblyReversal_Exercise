#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "node.h"

extern Node* reverse_asm_64(Node *head, unsigned int offset);

#define NUM_NODES 20


Node *get_head(void *p)
{
	return p == NULL ?
		NULL :
		((Node *)((char *)(p)-(unsigned long)(&((Node *)0)->ptr)));
}

Node *gen_rand_list(unsigned int count)
{
	Node *head, *tail, *curr;
	void *p;
	unsigned int i;

	head = tail = curr = NULL;
	for(i = 0; i < count; i++) {
		curr = (Node *) malloc (sizeof(Node));
		memset(curr, 0, sizeof(Node));
		curr->var = curr->val.n = rand() % 1000;
		if(head == NULL) {
			head = tail = curr;
		} else {
			tail->ptr = &(curr->ptr);
			tail = curr;
		}
	}
	return head;
}

void print_node(Node *node)
{
	printf("%d", node->var);
}

void print_list(Node *head)
{
	while(head) {
		print_node(head);
		printf(" -> ");
		head = get_head(head->ptr);
	}
	printf(" NULL\n");
}

Node *reverse_C(Node *head)
{
	void *headptr, *nextptr, *new_headptr;

	headptr = nextptr = new_headptr = NULL;
	if(head == NULL) return NULL;
	headptr = &(head->ptr);
	while (headptr) {
		nextptr = (void *)(*((unsigned long *)headptr));
		*(unsigned long *)headptr = (unsigned long) new_headptr;
		new_headptr = headptr;
		headptr = nextptr;
	}
	return get_head(new_headptr);
}

int main()
{
	Node *head, *revhead;

	/* This is the offset from base of node structure to the ptr field */
	unsigned int offset;
	
	/* We ask the compiler: "If 0 were the address of a Node, what is the address of ptr field?" */
	offset = (unsigned int)(&((Node *)0)->ptr);

	head = gen_rand_list(NUM_NODES);
	print_list(head);
	revhead = reverse_asm_64(head, offset);
	printf("****REV****\n");
	print_list(revhead);
	return 0;
}
