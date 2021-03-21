#include <stdio.h> // buat semua library
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int size = 25;
int hashnew;
struct node{
	char key[100];
	int val;
}*head[size];

int HashFunction(char key[])
{
	int val = 0;
	int len = strlen(key); // dapatin value dari key
	for(int i=0;i<len;i++)
	{
		val = val + len;
	}
	return val % size;
}

node* createnode(char key[],int val)
{
	node* temp = (node*)malloc(sizeof(node));
	strcpy(temp->key,key);
	temp->val = val;
	return temp;
}

void insert(char key[], int val)
{
	int hashval = HashFunction(key);
	if(head[hashval] == NULL) head[hashval] = createnode(key,val); // masih kosong
	else
	{
		int next = hashval+1; // jika udah terisi bakal traverse 1x.
		while(head[next] != NULL){ // kalo nanti increment masih berisi
			next++;
			if(next == size) next  = 0;
			if(next == hashval)
			{
			printf("Penuh!"); return;
			}
		}
		head[next] = createnode(key,val);
	}
}

node* searchnode(char key[])
{
	hashnew = 0;
	hashnew = HashFunction(key);
	while(head[hashnew] != NULL)
	{
		if(strcmp(key,head[hashnew]->key) == 0)
		{
			return head[hashnew];
		}
		hashnew++;
		if(hashnew == size) hashnew = 0;
	}
	return NULL;
}

void search(char key[])
{
	node* temp = searchnode(key);
	if(temp == NULL)
	{
		printf("Not Found %s\n",key);
	}
	else
	{
		printf("found at element-%d %s value %d\n",hashnew,key,temp->val);
	}
}

node* deletenode(node* temp, char key[])
{
	if(temp == NULL) return temp;
	else if(strcmp(temp->key,key) == 0)
	{
		temp =NULL;
	}
}

void deletes(char key[])
{
	node* curr = searchnode(key);
	if(curr == NULL) printf("Not found %s\n",key);
	else
	{
		printf("Deleted %s value %d\n",key,curr->val);
		head[hashnew] = deletenode(head[hashnew],key);
	}
}

void print()
{
	for(int i=0;i<size;i++)
	{
		printf("%d",i);
		if(head[i] != NULL)
		{
			printf(" %s %d",head[i]->key,head[i]->val);
		}
		printf("\n");
	}
}

int main()
{
	printf("Hashing Linear Probing using Array & Pointer\n");
	insert("sobregekake",102);
	insert("gey",10);
	insert("lol",1);
	insert("haha",4);
	insert("LOL",2);
	print();
	search("haha");
	deletes("haha");
	search("haha");
	print();
	insert("anjas",2);
	print();
	search("anjas");
	return 0;
}

