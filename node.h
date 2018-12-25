#ifndef _NODE_H
#define _NODE_H

struct _Node {
	union {
		int n;
		char c;
	} val;
	void *ptr;
	int var;
};
typedef struct _Node Node;

#endif
