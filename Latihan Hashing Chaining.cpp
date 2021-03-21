#include <stdio.h> // buat semua library
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int size = 25;

struct node{
	char key[100];
	int val;
	node* next;
}*head[size];

int HashFunction(char key[])
{
	int val = 0;
	int len = strlen(key);
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
	temp->next = NULL;
	return temp;
}

void insert(char key[],int val)
{
	int hashval = HashFunction(key);
	if(head[hashval] == NULL) head[hashval] = createnode(key,val); // kosong
	else
	{
		node* curr = head[hashval];
		while(1)
		{
			if(strcmp(curr->key,key) == 0) // cek data sama apa ngga
			{
				curr->val = val;
				return;
			}
			else if(curr->next != NULL) // masukin ke dalam aka traverse dlu
			{
				curr = curr->next;
			}
			else{   // input
				curr->next = createnode(key,val);
				return;
			}
		}
	}
}

node* searchnode(char key[]) // isi untuk dieksekusi search function
{
	int hashval = HashFunction(key);
	node* curr = head[hashval];
	while(curr != NULL) // selama masih null bakal cek truss
	{
		if(strcmp(key,curr->key)==0) // cek apakah ada yang sama
		{
			return curr;
		}
		curr = curr->next; // traverse
	}
	return NULL; // jika ga ada
}

void search(char key[])
{
	node* curr = searchnode(key);
	int hashval = HashFunction(key);
	if(curr == NULL) printf("Not found %s\n",key);
	else
	{
		printf("Found at element-%d %s value %d\n",hashval,key,curr->val);
	}
}

node* deletenode(node* curr,char key[]) // isi untuk dieksekusi delete function
{
	if(curr == NULL) return curr; // kalo kosong
	else if(strcmp(curr->key,key) == 0) // cek yang sesuai kemudian hapus head dan traverse
	{
		node* temp = curr->next;
		free(curr);
		return temp;
	}
	else
	{    // apabila di bagian pertama ga sesuai dicek kedalam" lagi
		curr->next = deletenode(curr->next,key); 
		return curr;
	}
}

void deletes(char key[])
{
	node* temp = searchnode(key); // cari pake function
	if(temp == NULL) printf("Not found %s\n",key); // gak ketemu
	else
	{		// ketemu
		printf("Deleted %s value %d\n",key,temp->val);
		int hashval = HashFunction(key); // masukin key utk nentuin tempat
		head[hashval] = deletenode(head[hashval],key); // delete pake function
	}
}

void print()
{
	for(int i=0;i<size;i++)
	{
		printf("%d",i);
		node* temp = head[i];
		while(temp != NULL){
			printf(" %s %d | ",temp->key,temp->val);
			temp = temp->next;
		}
		printf("\n");
	}
	printf("=========================\n");
}

int main()
{
	printf("Hashing Chaining Method using Linked List\n");
	insert("kntl",3);
	insert("ppq",1);
	insert("hihi",4);
	insert("pwers",3);
	print();
	deletes("kntl");
	search("ppq");
	print();
	search("meme");
	
	return 0;
}

