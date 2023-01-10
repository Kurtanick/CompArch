//First: Linked List
#include <stdio.h>

#include <stdlib.h>

//operation prototypes
void insert(int v);
void delete(int v);
void print();

//creating struct of node 
typedef struct node{
	int value;
	struct node* next;
} node;

//global pointer to head of LL
struct node *head = NULL;
//global int for length of LL
int length = 0;

void insert(int v){
	//printf("INSERT %d\n", v);
	
	node* p = head;
	node* temp = (node*) malloc(sizeof(node));
	temp -> value = v;
	
	if(head == NULL || head->value > temp->value){
		temp->next = head;
		head = temp;
	}
	else{
		if(head->value == temp->value){
			//printf("number already in list!\n");
			return;
		}
		while(p->next != NULL){
			if(p->next->value == temp->value){
				//printf("number already in list!\n");
				return;
			}
			if(p->next->value < temp->value) p = p->next;
			else{
				break;
			}
		}
		//printf("HERE\n");
		temp->next = p->next;
		p->next = temp;
	}
	//printf("Inserted...\n");
	++length;
	//return;
}

void delete(int v){
	//printf("DELETE %d\n", v);

	node *temp = head, *p;
	
	//to delete head
	if(head == NULL) return;
	if(temp->value == v){
		head = temp->next;
		free(temp);
		--length;
		//printf("deleted...\n");
		return;
	}
	while(temp != NULL){
		if(temp->value == v){
			p->next = temp->next;
			free(temp);
			--length;
			//printf("deleted...\n");
			return;
		}
		else{
			p=temp;
			temp = temp->next;
		}
	}
	//printf("Value not found...\n");
}

void print(){
	
	//printf("LINKED LIST:\n");
	
	printf("%d\n", length);
	//printf("LL:\n");
	
	node* temp = head;
	//printf("%d\n", temp->value);
	while(temp != NULL) {
		printf("%d\t", (temp -> value));
		temp = temp -> next;
	}
	printf("\n");	
	
	return;
}


int main(int argc, char** argv){
//read the file
	
	FILE* fp = NULL;
	char* filename;
	char op;
	int value;
	
	filename = argv[1];
	
	fp = fopen(filename, "r");
	
	//read thru file and preform operations
	
	while(!feof(fp)){
		fscanf(fp, "%c\t%d\n", &op, &value);
		if(op == 'i') insert(value);
		if(op == 'd') delete(value);
	}
	//printf("done reading file.\n");
	fclose(fp);
	
	print();
	
	return(0);
}

