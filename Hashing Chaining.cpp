#include <stdio.h> // buat semua library
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// PROBING CHAINING

const int HASH_SIZE = 20;

struct Node{
	char key[100];
	int value;
	Node* next;
}*head[HASH_SIZE];

int HashFunction(char key[]) // buat nemu tempat
{
	int value = 0;
	int len = strlen(key);
	for(int i = 0;i<len;i++){
		value += tolower(key[i]) - 'a'; // gak mesti tolower katanya bebas
	}
	return value % HASH_SIZE;
}

Node* createNode(char key[],int value){
	Node* temp =(Node*)malloc(sizeof(Node));
	strcpy(temp->key,key);
	temp->value =value;
	temp->next = NULL;
	return temp;
}

void insert(char key[],int value){ // key harus unique
	int hashValue = HashFunction(key);
	if(head[hashValue] == NULL) 
	{
		head[hashValue] = createNode(key, value);
	}
	
	else{ //override (replace) mencegah unique
		Node* curr = head[hashValue];
		while(1){
			if(strcmp(curr->key, key) == 0)
			{
				curr->value = value;
				return;
			}
			else if(curr->next != NULL)
			{
				curr = curr->next;
			}
			else
			{
				curr->next = createNode(key,value);
				return;
			}
	   	}
	}
}

Node* searchNode(char key[]) // kalo ketemu bakal return 
{
	int hashValue = HashFunction(key);
	Node* curr = head[hashValue];
	while(curr != NULL)
	{
		if(strcmp(key,curr->key) == 0) 
		{
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

void search(char key[])
{
	Node* curr = searchNode(key);
	if(curr == NULL){
		printf("Not Found %s\n",key);
	}
	else{
		printf("Found %s value %d\n ", key, curr->value);
	}
}

Node* deleteNode(Node* curr, char key[])
{
	if(curr == NULL) return curr;
	else if(strcmp(curr->key,key) == 0)
		{
			Node* temp = curr->next;
			free(curr);
			return temp;
		}
		
	else{
		curr->next = deleteNode(curr->next,key);
		return curr;
	}
}

void deletes(char key[])
{
	Node* curr = searchNode(key);
	if(curr == NULL){
		printf("Not Found %s\n",key);
	}
	else{
		printf("Deleted %s value %d\n ", key, curr->value);
		int hashValue = HashFunction(key);
		head[hashValue] = deleteNode(head[hashValue], key);
	}
}

void print()
{
	for(int i = 0;i < HASH_SIZE ; i++)
	{
		printf("%d",i);
		Node* curr = head[i];
		while(curr != NULL){
				printf(" %s %d | ",curr->key, curr->value);
				curr = curr->next;
		}
	printf("\n");
	}
	printf("====================\n");
}

int main()
{
//	Node* temp = createNode("Testing",5);
//	printf("%s %d\n",temp->key,temp->value);
//	printf("%d\n", HashFunction("Testing"));
//	printf("%d\n", HashFunction("testing"));
//	printf("%d\n",HashFunction("Maya"));
	insert("Testing", 15);
	insert("Maya", 82);
	insert("testing", 648);
	insert("tngesti", 72);
	insert("tingtes", 23);

	print();
	deletes("Testing");
	deletes("Maya");
	
	search("Testing");
	search("Kaya");
	print();
	return 0;
}

