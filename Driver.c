#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"
#include <stdio.h>
#include <stdlib.h>
#include <excpt.h>
#include <windows.h>
#include <string.h>

int parseWordsToTable(char* path, HashTable* ht);
SpellingSuggestion* spellingCheck(char* text);
SpellingSuggestion* BuildWord(SpellingSuggestion* head, char* word, HashTable* ht);
SpellingSuggestion* addNewNode(SpellingSuggestion* head, char* word, HashTable* ht);
SpellingSuggestion* FreeSpellingSuggestion(SpellingSuggestion *head);



int main()
{
	spellingCheck("iam afraid youare about to become teh immexdiate pst president of teh eing alive club ha ha glados");

	return 0;
}


int parseWordsToTable(char* path, HashTable* ht)
{
	if (path == NULL)
		return 0;

	FILE* filePointer;
	char buffer[100];
	__try {
		filePointer = fopen(path, "r");

		while (fgets(buffer, 100, filePointer)) {

			if (buffer == NULL)
				return 0;
			strtok(buffer, "\n");

			insert(ht, buffer);
			//printf("%s", buffer);
		}

		fclose(filePointer);

		return 1;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { printf("Error reading the file"); }
}

SpellingSuggestion* spellingCheck(char* text)
{
	HashTable *HashT;
	HashT = initTable(1000, 3);
	parseWordsToTable("C:/Users/sizex/Desktop/dictionary.txt", HashT);
	int size = strlen(text);
	char *token, *T;
	T = (char*)malloc((size) * sizeof(char));
	//text[size + 1] = '\0';
	int i = 0, j;
	for (j = 0; j < size; j++)
	{
		T[j] = text[j];
	}
	T[j] = '\0';


	
	//create list of kind SpellingSuggestion.
	SpellingSuggestion *list = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion));;
	list->next = NULL;
	list->suggestions = NULL;

	char **words=NULL;
	int CountWords = 0;
	token = strtok(T, " ");
	int flag = 0;
	while (token != NULL)
	{
		for (int i = 0; i < CountWords; i++)
		{
			if (strcmp(words[i], token) == 0)
				flag = 1;
				
		}
		if (flag == 0)
		{
			if (isWordInDictionary(HashT, token) == 0) {
				words = realloc(words, sizeof(char*)*++CountWords);
				words[CountWords - 1] = token;
			}
		}
		token = strtok(NULL, " ");
		flag = 0;	
	}
	words = realloc(words, sizeof(char*)* (CountWords+1));
	words[CountWords] = NULL;


	for( int i = CountWords - 1; i >= 0 ; i--)
	{
		if (isWordInDictionary(HashT, words[i]) == 0)
		{
			list = addNewNode(list, words[i], HashT);

		}

	}
	
	
	

	for (SpellingSuggestion *temp = list; temp->next != NULL; temp = temp->next)
	{
		if (temp->suggestions != NULL)
		{
			printf("The word ''%s'' was misspelled. Did you mean", temp->originalWord);
			PrintList(temp->suggestions);
		}
		else
		{
			printf("The word ''%s'' was misspelled. No suggestions found for this word.", temp->originalWord);
			PrintList(temp->suggestions);
		}
	}
	

	//======free all memorry=======> 
	free(words);
	free(token);
	for (int i = 0; i < 1000; i++)
		FreeList((HashT->hashTable[i]).chain);

	for (SpellingSuggestion *temp = list; temp->next != NULL; temp = temp->next)
		FreeList(temp->suggestions);

	FreeSpellingSuggestion(list);	
	

}

SpellingSuggestion* BuildWord(SpellingSuggestion* head, char* word, HashTable* ht)
{

	SpellingSuggestion *node = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion));;
	node->originalWord = (char*)malloc(sizeof(char)*strlen(word));
	strcpy(node->originalWord, word);
	node->suggestions = getWordSuggestions(ht, word);
	node->next = NULL;
	return node;
}

SpellingSuggestion* addNewNode(SpellingSuggestion* head, char* word, HashTable* ht)
{
	
	SpellingSuggestion *new_elem = BuildWord(head, word, ht);
	new_elem->next = head;
	return new_elem;
}

SpellingSuggestion* FreeSpellingSuggestion(SpellingSuggestion *head)
{
	SpellingSuggestion *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}
