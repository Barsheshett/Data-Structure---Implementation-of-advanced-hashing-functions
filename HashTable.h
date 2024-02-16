#pragma once
#include <conio.h>
#include <math.h>
#include "LinkedList.h"
#include <string.h>

typedef struct HashTableElement HashTableElement;

struct HashTableElement
{
	int key;
	LinkedList* chain;
};

typedef struct HashTable HashTable;

struct HashTable
{
	HashTableElement* hashTable;
	int hashFunction;
	int tableSize;
	int cellsTaken;
	int numOfElements;
};

int constantStringHashFunction(char* str);
int accumulateStringHashFunction(char* str);
int improvedHashFunction(char* str);

int hash(char* str, HashTable* ht);
HashTable* initTable(int tableSize, int hashFunction);
int insert(HashTable* ht, char* str);
int deleteElement(HashTable* ht, char* str);
int search(HashTable* ht, char* str);

//HashFunction number 1
int constantStringHashFunction(char* str)
{
	return 3;
}
//HashFunction number 2
int accumulateStringHashFunction(char* str)
{
	int sum = 0;
	for (int i = 0; str[i]!='\0'; i++)
	{
		sum += (int)str[i];
	}
	return sum;
}
//HashFunction number 3
int improvedHashFunction(char* str)
{
	int sum = 0;
	int n = strlen(str);

	if (str == NULL)
		return 0;
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		j = pow(31, (n - 1 - i));
		sum += (int)str[i] * j;
	}
	return sum;
}
//Creates and return a linked list by hashfunction.
HashTable* initTable(int tableSize, int hashFunction)
{
	HashTable *HashT = (HashTable*)malloc(sizeof(HashTable));;
	HashT->tableSize = tableSize;
	HashT->hashFunction = hashFunction;
	HashT->numOfElements = 0;
	HashT->hashTable = (HashTableElement*)malloc(tableSize*sizeof(HashTableElement));
	
	for (int i = 0; i < tableSize; i++)
		HashT->hashTable[i].chain = NULL;

	return HashT;
}

//return the index in hashtable
int hash(char* str, HashTable* ht)
{
	int index = 0;

	if (str == NULL)
		return 0;

	if (ht->hashFunction == 1)
		index = constantStringHashFunction(str) % ht->tableSize;
	else if (ht->hashFunction == 2)
		index = accumulateStringHashFunction(str) % ht->tableSize;
	else if (ht->hashFunction == 3)
		if(improvedHashFunction(str) < 0)
			index = (improvedHashFunction(str)*-1) % ht->tableSize;
		else
			index = improvedHashFunction(str) % ht->tableSize;

	return index;
}

//insert to the table the string by hashfunc.
int insert(HashTable* ht, char* str)
{
	if (str == NULL)
		return 0;


	int location = hash(str, ht);
	if ((ht->hashTable[location]).chain == NULL)
	{
		(ht->hashTable[location]).chain = addToStart((ht->hashTable[location]).chain,str);
		(ht->numOfElements)++;
	}
	else if (isInList((ht->hashTable[location]).chain, str) == 1)
		return 0;
	else
	{
		(ht->hashTable[location]).chain = addToStart((ht->hashTable[location]).chain, str);
		(ht->numOfElements)++;
		return 1;
	}
	

}

//delete element from hashtable
int deleteElement(HashTable* ht, char* str)
{
	if (str == NULL)
		return 0;

	int location = hash(str, ht);



	if (isInList((ht->hashTable[location]).chain, str) == 1)
	{
		deleteElement(ht->hashTable[location].chain, str);
		return 1;
	}
	else
		return 0;

}
//search a sstring in hash table
int search(HashTable* ht, char* str)
{
	if (str == NULL)
		return 0;

	int location = hash(str, ht);

	if (isInList((ht->hashTable[location]).chain, str) == 1)
		return 1;
	else
		return 0;
}