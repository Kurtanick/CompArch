//Eighth: Binary Search Tree
#include <stdio.h>

#include <stdlib.h>


typedef struct node{
	int key;
	struct node *left, *right;
} node;

node *newNode(int k);
void insert(int k);
node *recInsert(node *node, int k);
void *search(int k);
node *recSearch(node *node, int k);
void freeBST(node *node);

node *root = NULL;
int height;
int inserted;


//creates a new BST node
node *newNode(int k){
	node *temp = (node*)malloc(sizeof(node));
	temp->key = k;
	temp->left = NULL;
	temp->right = NULL; 
	return temp;
}

void insert(int k){

	//printf("Insert: %d\n", k);
	
	height = 1;
	inserted = 0;
		
	if(root == NULL){
		root = recInsert(root, k);
	}
	else	recInsert(root, k);
	if(inserted == 1) printf("inserted %d\n", height);
	else printf("duplicate\n");
}

node *recInsert(node *node, int k){
	
	//empty tree
	if (node == NULL){
		//printf("inserted = 1\n");
		inserted = 1;
		return newNode(k);
	}
	if (k < node->key){
		//printf("moving left\n");
		++ height;
		node->left = recInsert(node->left, k);
	}
	else if(k > node->key){
		//printf("moving right\n");
		++ height;
		node->right = recInsert(node->right, k);
	}
	
	//printf("duplicate\n");
	return node;
}

void *search(int k){
	//printf("Search: %d\n", k);
	
	height = 1;
	inserted = 0; //= 1 if key is present in BST
	recSearch(root, k);
	if(inserted == 1) printf("present %d\n", height);
	else printf("absent\n");
}

node *recSearch(node *node, int k){
	
	if(node == NULL) return node;
	if(node->key == k){
		inserted = 1;
		return node;
	}
	if(node->key < k){
		++height;
		return recSearch(node->right, k);
	}
	else{
		++height;
		return recSearch(node->left, k);
	}
}

void freeBST(node *node){
	if(node == NULL) return;
	
	freeBST(node->left);
	freeBST(node->right);
	free(node);
}

int main(int argc, char**argv){

	FILE* fp = NULL;
	char* filename;
	char op;
	int key;
	
	if(argc < 2){
		printf("error\n");
		exit(0);
	}
	
	filename = argv[1];
	
	fp = fopen(filename, "r");
	
	while(!feof(fp)){
		fscanf(fp, "%c\t%d\n", &op, &key);
		if(op == 'i'){
			insert(key);
		}
		else if(op == 's') search(key);
		else{
			printf("error\n");
			exit(0);
		}
	}
	//printf("done reading file.\n");
	fclose(fp);
	
	freeBST(root);

	return 0;
}


