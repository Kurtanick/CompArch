#include <stdio.h>

#include <stdlib.h>

//Fourth: Matrix Eponentation

int main(int argc, char** argv){

	FILE* fp = NULL;
	char* filename;
	int size,h, i, j, k, exp, sum, value=0;
	int **matrix, **newMatrix, **tempMatrix;
	
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
	tempMatrix = (int**)malloc(size * sizeof(int*));
	for(i=0;i<size;i++){ //allocate space for rows
		tempMatrix[i] = (int*) malloc(size * sizeof(int));
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
	for(h=0;h<exp;h++){
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
				//newMatrix[i][j]=0;
				for(k=0;k<size;k++){
					sum = sum + newMatrix[i][j] * matrix[i][j];
				}
				tempMatrix[i][j] = sum;
				sum = 0;
			}
		}
		for(i=0;i<size;i++){
			for(j=0;j<size;j++){
				newMatrix[i][j] = tempMatrix[i][j];
			}
		}	
	}
	
	//Print
	printf("Input Matrix:\n");
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
	printf("New Matrix:\n");
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf("%d\t", newMatrix[i][j]);
		}
		printf("\n");
	}
	
	
	
	free(matrix);
	free(newMatrix);
	free(tempMatrix);
	
	return 0;
}	
