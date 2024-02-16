#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedList LinkedList;

struct LinkedList {
	char* data;
	LinkedList  * next;
};

void PrintList(LinkedList *);
LinkedList *BuildNode(char*);
LinkedList *addToStart(LinkedList *, char*);
LinkedList *FreeList(LinkedList *);
LinkedList *DeleteElement(LinkedList *, char*);
int isInList(LinkedList*, char*);
LinkedList* addToTail(LinkedList *head, char* data);
LinkedList* MergeList(LinkedList *a, LinkedList *b);
int CountNodes(LinkedList *head);
LinkedList* FreeList(LinkedList *head);





//==========================Functions=================>>


// build a new node in linked list
LinkedList* BuildNode(char* data)
{
	LinkedList *node = (LinkedList*)malloc(sizeof(LinkedList));
	node->data = (char*)malloc(sizeof(char)*strlen(data));
	strcpy(node->data, data);
	node->next = NULL;
	return node;
}
// add to the head new element
LinkedList* addToStart(LinkedList* head, char* data)
{
	LinkedList *new_elem = BuildNode(data);
	new_elem->next = head;
	return new_elem;
}
//head to tail, not used
LinkedList* addToTail(LinkedList *head, char* data)
{
	LinkedList *temp, *new_elem;
	new_elem = BuildNode(data);
	if (head == NULL)
		return new_elem;
	for (temp = head; temp->next != NULL; temp = temp->next);
	temp->next = new_elem;
	return head;
}
// free function
LinkedList* FreeList(LinkedList *head)
{
	LinkedList *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}
//delete element from list
LinkedList* DeleteElement(LinkedList* head, char* data)
{
	LinkedList *previous = head, *current = head->next;
	if (head == NULL)
		return head;

	if (strcmp(head->data ,data)==0)
	{
		LinkedList *temp = head;
		head = head->next;
		free(temp);
		return head;
	}
	while (previous != NULL)
	{
		if (strcmp(previous->data, data) == 0)
			break;
		current = previous;
		previous = previous->next;
	}
	if (previous != NULL)
		current->next = previous->next;
	free(previous);
	return head;
}
// chack if the element in the list, return 1 if true else false.
int isInList(LinkedList* head, char* data)
{
	int flag = 0;
	int i = 1;
	LinkedList* temp = head;

	if (temp == NULL)
		return 0;

	for (temp = head; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->data , data)==0)
		{
			flag = 1;
			break;
		}
		i++;
	}

	if (flag == 1)
		return 1;
	else
		return 0;
}
//print the list function
void PrintList(LinkedList *head)
{
	LinkedList *temp = head;
	printf("\n");
	while (temp != NULL)
	{
		printf("%s\n", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

//merging tow list to one
LinkedList* MergeList(LinkedList *start1, LinkedList *start2)
{

	LinkedList *ptr;
	if (start1 == NULL)
	{
		start1 = start2;
		return start1;
	}
	if (start2 == NULL)
		return start1;
	ptr = start1;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = start2;

	return start1;

}
//count nodes in linked list
int CountNodes(LinkedList *head)
{
	int num = 0;
	LinkedList *temp = head;
	while (temp != NULL)
	{
		num++;
		temp = temp->next;
	}
	return num;
}

