#include <stdio.h> // buat semua library
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// PROBING LINEAR HASHING

const int HASH_SIZE = 20;

struct Node{
	char key[100];
	int value;
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
	return temp;
}

void insert(char key[],int value){
	int hashValue = HashFunction(key);
	if(head[hashValue] == NULL) head[hashValue] = createNode(key, value);
	else{
		int temp = hashValue + 1;
		while(head[temp] != NULL)
		{
			temp++;
			if(temp ==  HASH_SIZE)
			{
				temp = 0;
			}
			if(temp == hashValue)
			{
				printf("Data Penuh");
				return;
			}
		}
		head[temp] = createNode(key,value);
	}
}

void print()
{
	for(int i = 0;i < HASH_SIZE ; i++)
	{
		printf("%d",i);
		if(head[i] != NULL) 
		{printf(" %s %d",head[i]->key, head[i]->value);
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
	insert("testing", 648);
	insert("Maya", 82);
	print();
	return 0;
}

