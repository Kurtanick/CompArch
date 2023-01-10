#include <stdio.h>
#include<stdlib.h>

//PA2 - learn: does matrix things to learn stuff to find the price of a house

//function definitions:
double** multiply(double** x, double** y, int xrows, int xcols, int yrows, int ycols); //returns Matrix X * Matrix Y
void transpose(double** x, int rows, int cols);//returns the transpose of Matrix X
double** invert(double** x, int rows, int cols);//returns the inverse of Matirx X
void input(char* filename); //inputs X from learnFile
void printMatrix(double** x, int rows, int cols); //prints given matrix
void test(char* filename);

//Global Variables
double **X, **Y, **W, **Xt; //The Matricies
int Rows, Cols; //Number of rows and columns in Matrix X
int i, j, k;

double** multiply(double** x, double** y, int xrows, int xcols, int yrows, int ycols){
	//printf("Multipy Matrix %d by %d.", x, y);
	
	//allocate space for new matrix
	double** temp = (double**)malloc(xrows * sizeof(double*));
	for(i=0;i<xrows;i++){
		temp[i] = (double*) malloc(ycols * sizeof(double));
	}
	
	for(i=0;i<xrows;i++){
		for(j=0;j<ycols;j++){
			temp[i][j]=0;
			for(k=0;k<xcols;k++){
				temp[i][j] += x[i][k] * y[k][j];
			}
		}
	}
	
	//free(X);
	
	return temp;
}

void transpose(double** x, int rows, int cols){
	//printf("Transpose Matrix %d." , x);

	//allocate space for Xt
	//allocate space for rows of Matrix Xt
	Xt = (double**)malloc(cols * sizeof(double*));
	//allocate space for cols of Matrix Xt
	for(i=0;i<cols; i++){
		Xt[i] = (double*) malloc(rows * sizeof(double));
	}
	
	//transpose X
	for(i=0;i<rows;++i){
		for(j=0;j<cols;++j){
			Xt[j][i] = X[i][j];
		}
	}
	
}

double** invert(double** x, int rows, int cols){
	//printf("Invert Matrix %d." , x);
	int k; //col value for stepping through entire rows
	int l; //holds row value of current diagonal
	double val;
	
	//allocate temp matrix
	double** temp = (double**)malloc(rows * sizeof(double*));
	for(i=0;i<rows;i++){
		temp[i] = (double*) malloc(cols * sizeof(double));
	}
	
	//make temp the identity matrix
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			if(i==j) temp[i][j] = 1;
			else temp[i][j] = 0;
		}
	}
	
	//REF
	for(j=0; j<cols; j++){
		for(i=0;i<rows;i++){
			if( (i==j) && x[i][j] != 1){
				val = x[i][j];
				for(k=0;k<cols;++k){
					//printf("DIV ROWS: %lf/%lf", temp[i][k], val);
					
					x[i][k] = x[i][k]/val; //divide whole row by diagonal
					
					temp[i][k] = temp[i][k]/val;
					//printf(" = %lf\n", temp[i][k]);
				}
			}
			
			if(i==j) l=i; //save row value of diagonal
			
			if( (i>j) && x[i][j] != 0){
				val = x[i][j];
				for(k=0;k<cols;++k){
					//printf("MIN ROWS: %lf - (%lf * %lf)", x[i][k], x[l][k], val);
					 
					x[i][k] = x[i][k] - (x[l][k]*val);
					temp[i][k] = temp[i][k] - (temp[l][k]*val);
					
					//printf(" = %lf\n", x[i][k]);
				}
			}
		}
	}
	
	//RREF
	for(j=(cols-1);j>=0;j--){
		for(i=(rows-1);i>=0;i--){
			if(j==i) l=i;
			
			if(j>i){
				val = x[i][j];
				for(k=cols-1;k>=0;k--){
					x[i][k] = x[i][k] - (x[l][k]*val);
					temp[i][k] = temp[i][k] - (temp[l][k]*val);
				}
			}
		}
	}
	
	free(x);
	
	//return x;
	return temp;
}

void printMatrix(double** x, int rows, int cols){
	
	for(i=0; i<rows; i++){
		for(j=0; j<cols; j++){
			printf("%lf ", x[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void input(char* filename){
	int N, K; //N = examples(rows), K = attributes(cols)
	FILE* fp = fopen(filename, "r");
	
	fscanf(fp, "%d\n" ,&K);
	fscanf(fp, "%d\n" ,&N);
	
	//set size of Matrix X
	Rows = N;
	Cols = (K+1);
	//printf("ROWS = %d	COLS = %d\n", Rows, Cols);
	
	//allocate space for rows of Matrix X
	X = (double**)malloc(Rows * sizeof(double*));
	//allocate space for cols of Matrix X
	for(i=0;i<Rows; i++){
		X[i] = (double*) malloc(Cols * sizeof(double));
	}
	
	//allocate space for Matrix Y
	Y = (double**)malloc(Rows * sizeof(double*));
	for(i=0;i<Rows;++i){
		Y[i] = (double*) malloc(sizeof(double));
	}
	
	//populate matrix X and Y
	for(i=0;i<Rows;i++){
		for(j=0;j<=Cols;j++){
			if(j==0) X[i][j] = 1;
			else if(j == Cols) fscanf(fp, "%lf\n", &Y[i][0]);
				else fscanf(fp, "%lf,", &X[i][j]);
		}
	}
	fclose(fp);
}

void test(char* filename){
	int N; //number of examples
	int a;
	double value; //price of house
	FILE* fp = fopen(filename, "r");
	
	fscanf(fp, "%d\n" ,&N);
	//printf("Examples: %d\n", N);
	
	//allocate space for X
	X = (double**)malloc(sizeof(double*)); //1 row
	//allocate space for cols of Matrix X
	X[0] = (double*) malloc(Cols * sizeof(double)); //Cols columns
	
	for(a=0;a<N;a++){//loop for each example
		for(j=0;j<Cols;j++){//loop for Cols of data
			if(j==0) X[0][j] = 1;
			else fscanf(fp, "%lf,", &X[0][j]);
			//printf("%
		}
		fscanf(fp, "\n");
		Y = multiply(X, W, 1, Cols, Cols, 1);
		value = Y[0][0];
		printf("%0.0f\n", value);
		//printf("%d\n", value);
		//printf("%d\n", a);
		
	}
}

int main(int argc, char** argv){

	//W = Inv(Xt.X).Xt.Y
	
	char* learnFilename = argv[1];
	char* testFilename = argv[2];
	
	input(learnFilename); //find X and Y
	transpose(X, Rows, Cols); //find Xt
	
	//printMatrix(X, Rows, Cols);
	//printMatrix(Y, Rows, 1);
	//printMatrix(Xt, Cols, Rows);
	
	X = multiply(Xt, X, Cols, Rows, Rows, Cols); //X = (Xt.X)
	//printMatrix(X, Cols, Cols);
	
	X = invert(X, Cols, Cols); //X = INVERSE(Xt.X)
	//printMatrix(X, Cols, Cols);
	
	X = multiply(X, Xt, Cols, Cols, Cols, Rows); //X = INV(Xt.X).Xt
	
	W = multiply(X, Y, Cols, Rows, Rows, 1); //W = Inv((Xt.X).Xt).Y
	//printMatrix(W, Cols, 1);
	
	test(testFilename);
	
	//free Memory
	free(X);
	free(Y);
	free(Xt);
	free(W);
	
	return 0;
}
