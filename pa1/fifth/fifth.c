#include <stdio.h>

#include <stdlib.h>

//Fifth: Matrix Squares
//TODO spit things into functions? (save this file first)
void unique(int element, int** matrix, int size);

//function to check if an element is unique within the matrix
void unique(int element, int** matrix, int size){
	int i, j, found=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
		if(element == matrix[i][j]){
				++found;
				if(found > 1){
					printf("not-magic\n");
					exit(0);
				}
			}
		}
	}
}

int main(int argc, char** argv){

	FILE* fp = NULL;
	char* filename;
	int size, i, j, magicNum = 0, value=0;
	int** matrix;
	
	filename = argv[1];
	fp = fopen(filename, "r");
	
	//get matrix size from file
	fscanf(fp, "%d\n" , &size);

	//allocate space for col
	matrix = (int**)malloc(size * sizeof(int*)); 
	for(i=0;i<size;i++){ //allocate space for rows
		matrix[i] = (int*) malloc(size * sizeof(int));
	}
	
	//popuate matrix from file
	for(i=0; i<size; i++){
		for(j=0;j<size; j++){
			fscanf(fp, "%d\t", &matrix[i][j]); //scan in each element of row
			
		}
		fscanf(fp, "\n");//go to next row
	}
	//END popuating matrix
	// test matrix
	
	//test that every element is unique
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			unique(matrix[i][j], matrix, size);
		}
	}
	
	//find the magic number from adding up 1st col
	j=0;
	for(i=0; i<size; i++){
		magicNum += matrix[i][j];
	}
	
	//test rows of matrix
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			value += matrix[i][j];
		}
		if(value != magicNum){ //matrix is not magical :(
			printf("not-magic\n");
			//printf("ROWS MagicNum: %d	Value:%d\n" , magicNum, value);
			exit(0);
		}	
		value = 0;		
	}
	
	//test columns
	
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			value += matrix[j][i];
		}
		if(value != magicNum){ //matrix is not magical :(
			printf("not-magic\n");
			//printf("COLS MagicNum: %d	Value:%d\n" , magicNum, value);
			exit(0);
		}
		value = 0;
	}	
	
	//test main diagonal
	for(i=0;i<size; i++){
		value += matrix[i][i];
	}
	if (value != magicNum){
		printf("not-magic\n");
		//printf("DIAG MagicNum: %d	Value:%d\n" , magicNum, value);
		exit(0);
	}
	
	//free allocated matrix memory
	for(i=0; i<size; i++){
		free(matrix[i]);
	}
	free(matrix);
	
	printf("magic\n");
	return 0;
}
