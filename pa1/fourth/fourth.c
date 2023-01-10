#include <stdio.h>

#include <stdlib.h>

//Fourth: Matrix Eponentation
void exponentiate(int** matrix, int** newMatrix, int size);

void exponentiate(int** matrix, int** newMatrix, int size){
	int i, j, k;
	int** tempMatrix;
	
	tempMatrix = (int**)malloc(size * sizeof(int*));
	for(i=0;i<size;i++){ //allocate space for rows
		tempMatrix[i] = (int*) malloc(size * sizeof(int));
	}

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			tempMatrix[i][j]=0;
			for(k=0;k<size;k++){
				tempMatrix[i][j]  += newMatrix[i][k] * matrix[k][j];
			}
		}
	}
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			newMatrix[i][j] = tempMatrix[i][j];
		}
	}
	free(tempMatrix);
}

int main(int argc, char** argv){

	FILE* fp = NULL;
	char* filename;
	int size, i, j, k, exp, value=0;
	int **matrix, **newMatrix ;
	
	filename = argv[1];
	fp = fopen(filename, "r");
	
	//get matrix size from file
	fscanf(fp, "%d\n" , &size);

	//allocate space for col
	matrix = (int**)malloc(size * sizeof(int*)); 
	for(i=0;i<size;i++){ //allocate space for rows
		matrix[i] = (int*) malloc(size * sizeof(int));
	}
	newMatrix = (int**)malloc(size * sizeof(int*));
	for(i=0;i<size;i++){ //allocate space for rows
		newMatrix[i] = (int*) malloc(size * sizeof(int));
	}
	
	//popuate matrix from file
	for(i=0; i<size; i++){
		for(j=0;j<size; j++){
			fscanf(fp, "%d\t", &matrix[i][j]); //scan in each element of row
			
		}
		fscanf(fp, "\n");//go to next row
	}
	
	//make maticies equal
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			newMatrix[i][j] = matrix[i][j];
		}
	}
	//END popuating matrix
	
	//get exponent
	fscanf(fp, "%d", &exp);
	//END reading file
	
	//Multipying the Matrix
	for(i=1;i<exp;i++){
		exponentiate(matrix, newMatrix, size);
	}
	
	//Print
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf("%d\t", newMatrix[i][j]);
		}
		printf("\n");
	}
	
	free(matrix);
	free(newMatrix);
	
	return 0;
}	
