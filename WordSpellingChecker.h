#pragma once
#include "HashTable.h"

typedef struct SpellingSuggestion SpellingSuggestion;

struct SpellingSuggestion {
	char* originalWord;
	LinkedList  * suggestions;
	SpellingSuggestion* next;
};

int wordSpellingChecker(HashTable* dictionaryTable);// unused function..
int isWordInDictionary(HashTable* dictionaryTable, char* word);
LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word);
LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word);


int isWordInDictionary(HashTable* dictionaryTable, char* word)
{
	if (word == NULL)
		return 0;

	if (search(dictionaryTable, word) == 1)
		return 1;
	else
		return 0;
}

//Functions that create a linked list of all those returned tests and merge them into a single list.
LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word) 
{
	
	LinkedList* list = NULL;
	LinkedList* temp;
	if (dictionaryTable == NULL)
		return list;
	
	list = MergeList(list, addSpaceCheck(dictionaryTable, word));
	list = MergeList(list, replaceCharacterCheck(dictionaryTable, word));
	list = MergeList(list, deleteCharacterCheck(dictionaryTable, word));
	list = MergeList(list, addCharacterCheck(dictionaryTable, word));
	list = MergeList(list, switchAdjacentCharacterCheck(dictionaryTable, word));
	
	
	for (temp = list; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->data, word) == 0)
		{
			temp = DeleteElement(list, word);
		}
	}

	return list;
	
}

// All five functions that test similar words
LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word)
{
	LinkedList* list = NULL;
	int size = strlen(word);
	char* spacedword = (char*)malloc((size + 2) * sizeof(char));
	char* possibleWord = (char*)malloc((size + 2) * sizeof(char));
	char* token;

	for (int k = 1; k < size; k++) {
		for (int i = 0; i <= size; i++)
		{
			if (i < k)
				spacedword[i] = word[i];
			else if (i == k) 
				spacedword[i] = ' ';
			else
				spacedword[i] = word[i-1];
		}
		spacedword[size+1] = '\0';
		strcpy(possibleWord, spacedword);
		token = strtok(spacedword, " ");
		if (isWordInDictionary(dictionaryTable, token) == 1) {
			token = strtok(NULL, " ");
			if (isWordInDictionary(dictionaryTable, token) == 1) {
				if (list == NULL)
				{
					list = BuildNode(possibleWord);
				}
				else
					list = addToStart(list, possibleWord);
			}
		}
	}
	return list;
}


LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word)
{
	LinkedList* list = NULL;
	int size = strlen(word);
	char* possibleWord = (char*)malloc((size + 1) * sizeof(char));


	possibleWord[size] = '\0';
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++)
		{
			if (i != k)
				possibleWord[i] = word[i];
		}
		for (int i = 97; i < 123; i++) {
			possibleWord[k] = (char)i;
			if ((strcmp(possibleWord, word) != 0) && isWordInDictionary(dictionaryTable, possibleWord) == 1){
				if (list == NULL)
				{
					list = BuildNode(possibleWord);
				}
				else
					list = addToStart(list, possibleWord);
			}
		}
	}

	return list;

}

LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word)
{
	LinkedList* list = NULL;
	int size = strlen(word);
	char* possibleWord = (char*)malloc((size - 1) * sizeof(char));

	possibleWord[size - 1] = '\0';
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++)
		{
			if (i < k)
				possibleWord[i] = word[i];
			if (i > k)
				possibleWord[i-1] = word[i];
		}
		if (isWordInDictionary(dictionaryTable, possibleWord) == 1) {
			if (list == NULL)
			{
				list = BuildNode(possibleWord);
			}
			else
				list = addToStart(list, possibleWord);
		}
	}
	return list;
}

LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word)
{
	LinkedList* list = NULL;
	int size = strlen(word);
	char* possibleWord = (char*)malloc((size + 2) * sizeof(char));


	possibleWord[size + 1] = '\0';
	for (int k = 0; k <= size; k++) {
		for (int i = 0; i <= size; i++)
		{
			if (i < k)
				possibleWord[i] = word[i];
			if (i > k)
				possibleWord[i] = word[i - 1];
		}
		for (int i = 97; i < 123; i++) {
			possibleWord[k] = (char)i;
			if ((strcmp(possibleWord, word) != 0) && isWordInDictionary(dictionaryTable, possibleWord) == 1) {
				if (list == NULL)
				{
					list = BuildNode(possibleWord);
				}
				else
					list = addToStart(list, possibleWord);				
			}
		}
	}

	return list;
}


LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word)
{
	LinkedList* list = NULL;
	int size = strlen(word);
	char* possibleWord = (char*)malloc((size + 1) * sizeof(char));


	possibleWord[size] = '\0';   //kiss
	for (int k = 0; k < size - 1; k++) {
		for (int i = 0; i < size; i++)
		{
			if (i != k)
				possibleWord[i] = word[i];
			else if (i == k) {
				possibleWord[i] = word[i + 1];
				possibleWord[i + 1] = word[i];
				i++;
			}
		}
		if (isWordInDictionary(dictionaryTable, possibleWord) == 1) {
			if (list == NULL)
			{
				list = BuildNode(possibleWord);
			}
			else
				list = addToStart(list, possibleWord);
		}
				
	}

	return list;

}

