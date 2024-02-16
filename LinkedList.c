#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "LinkedList.h"

#define SWAP(x,y,t)((t)=(x),(x)=(y),(y)=(t))

typedef struct LinkedList LinkedList;
/*struct LinkedList {
	char* data;
	LinkedList  * next;
};

LinkedList *BuildNode(char* str)
{
	LinkedList *node = (LinkedList*)malloc(sizeof(LinkedList));
	node->data = str;
	node->next = NULL;
	return node;
}
*/
