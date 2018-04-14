#include <omp.h>

int ADD(int* MatrixA, int* MatrixB, int* MatrixResult, int MatrixSize)
{
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			MatrixResult[i * MatrixSize + j] = MatrixA[i * MatrixSize + j] + MatrixB[i * MatrixSize + j];
		}
	}
	return 0;
}

int SUB(int* MatrixA, int* MatrixB, int* MatrixResult, int MatrixSize)
{
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			MatrixResult[i * MatrixSize + j] = MatrixA[i * MatrixSize + j] - MatrixB[i * MatrixSize + j];
		}
	}
	return 0;
}

int MUL(int* MatrixA, int* MatrixB, int* MatrixResult, int MatrixSize)
{
	for (int i = 0; i<MatrixSize; i++)
	{
		for (int j = 0; j<MatrixSize; j++)
		{
			MatrixResult[i * MatrixSize + j] = 0;
			for (int k = 0; k < MatrixSize; k++)
			{
				MatrixResult[i * MatrixSize + j] += MatrixA[i * MatrixSize + k] * MatrixB[k * MatrixSize + j];
			}
		}
	}
	return 0;
}

int Strassen(int *MatrixA, int *MatrixB, int *MatrixC, int N)
{

	int HalfSize = N / 2;
	
	if (N <= 64)
	{
		MUL(MatrixA, MatrixB, MatrixC, N);
	}
	else
	{
		int* A11;
		int* A12;
		int* A21;
		int* A22;

		int* B11;
		int* B12;
		int* B21;
		int* B22;

		int* C11;
		int* C12;
		int* C21;
		int* C22;

		int* P1;
		int* P2;
		int* P3;
		int* P4;
		int* P5;
		int* P6;
		int* P7;
		int* AResult;
		int* BResult;

		
		A11 = new int [HalfSize * HalfSize];
		A12 = new int [HalfSize * HalfSize];
		A21 = new int [HalfSize * HalfSize];
		A22 = new int [HalfSize * HalfSize];

		B11 = new int [HalfSize * HalfSize];
		B12 = new int [HalfSize * HalfSize];
		B21 = new int [HalfSize * HalfSize];
		B22 = new int [HalfSize * HalfSize];

		C11 = new int [HalfSize * HalfSize];
		C12 = new int [HalfSize * HalfSize];
		C21 = new int [HalfSize * HalfSize];
		C22 = new int [HalfSize * HalfSize];

		P1 = new int [HalfSize * HalfSize];
		P2 = new int [HalfSize * HalfSize];
		P3 = new int [HalfSize * HalfSize];
		P4 = new int [HalfSize * HalfSize];
		P5 = new int [HalfSize * HalfSize];
		P6 = new int [HalfSize * HalfSize];
		P7 = new int [HalfSize * HalfSize];

		AResult = new int [HalfSize * HalfSize];
		BResult = new int [HalfSize * HalfSize];


		
		
		for (int i = 0; i < HalfSize; i++)
		{
			for (int j = 0; j < HalfSize; j++)
			{
				A11[i * HalfSize + j] = MatrixA[i * N + j];
				A12[i * HalfSize + j] = MatrixA[i * N + (j + HalfSize)];
				A21[i * HalfSize + j] = MatrixA[(i + HalfSize) * N + j];
				A22[i * HalfSize + j] = MatrixA[(i + HalfSize) * N + (j + HalfSize)];

				B11[i * HalfSize + j] = MatrixB[i * N + j];
				B12[i * HalfSize + j] = MatrixB[i * N + (j + HalfSize)];
				B21[i * HalfSize + j] = MatrixB[(i + HalfSize) * N + j];
				B22[i * HalfSize + j] = MatrixB[(i + HalfSize) * N + (j + HalfSize)];

			}
		}

		//P1=(A11+A22)(B11+B22)
		ADD(A11, A22, AResult, HalfSize);
		ADD(B11, B22, BResult, HalfSize);
		Strassen(AResult, BResult, P1, HalfSize); 
		

		//P2=(A21+A22)B11
		ADD(A21, A22, AResult, HalfSize);              
		Strassen(AResult, B11, P2, HalfSize);       
		
		//P3=A11(B12-B22)										
		SUB(B12, B22, BResult, HalfSize);              
		Strassen(A11, BResult, P3, HalfSize);       
		
		//P4=A22(B21-B11)											
		SUB(B21, B11, BResult, HalfSize);           
		Strassen(A22, BResult, P4, HalfSize);       
		
		//P5=(A11+A12)B22											
		ADD(A11, A12, AResult, HalfSize);           
		Strassen(AResult, B22, P5, HalfSize);       
		

		//M6=(A21-A11)(B11+B12)											
		SUB(A21, A11, AResult, HalfSize);
		ADD(B11, B12, BResult, HalfSize);             
		Strassen(AResult, BResult, P6, HalfSize);    
		
		//M7=(A12-A22)(B21+B22)										 
		SUB(A12, A22, AResult, HalfSize);
		ADD(B21, B22, BResult, HalfSize);             
		Strassen(AResult, BResult, P7, HalfSize);     
		
		//C11 = P1 + P4 - P5 + P7;
		ADD(P1, P4, AResult, HalfSize);
		SUB(P7, P5, BResult, HalfSize);
		ADD(AResult, BResult, C11, HalfSize);
		

		//C12 = P3 + P5;
		ADD(P3, P5, C12, HalfSize);
		

		//C21 = P2 + P4;
		ADD(P2, P4, C21, HalfSize);
		

		//C22 = P1 + P3 - P2 + P6;
		ADD(P1, P3, AResult, HalfSize);
		SUB(P6, P2, BResult, HalfSize);
		ADD(AResult, BResult, C22, HalfSize);
		


		for (int i = 0; i < HalfSize; i++)
		{
			for (int j = 0; j < HalfSize; j++)
			{
				MatrixC[i * N + j] = C11[i * HalfSize + j];
				MatrixC[i * N +(j + HalfSize)] = C12[i * HalfSize + j];
				MatrixC[(i + HalfSize) * N + j] = C21[i * HalfSize + j];
				MatrixC[(i + HalfSize) * N + (j + HalfSize)] = C22[i * HalfSize + j];
			}
		}

	
		
		delete[] A11; delete[] A12; delete[] A21; delete[] A22;
		delete[] B11; delete[] B12; delete[] B21; delete[] B22;
		delete[] C11; delete[] C12; delete[] C21; delete[] C22;
		delete[] P1; delete[] P2; delete[] P3; delete[] P4; delete[] P5;
		delete[] P6; delete[] P7;
		delete[] AResult;
		delete[] BResult;

	}


	return 0;
}

int ParallelStrassen(int *MatrixA, int *MatrixB, int *MatrixC, int N)
{

	int HalfSize = N / 2;

	if (N <= 64)
	{
		MUL(MatrixA, MatrixB, MatrixC, N);
	}
	else
	{
		int* A11;
		int* A12;
		int* A21;
		int* A22;

		int* B11;
		int* B12;
		int* B21;
		int* B22;

		int* C11;
		int* C12;
		int* C21;
		int* C22;

		int* P1;
		int* P2;
		int* P3;
		int* P4;
		int* P5;
		int* P6;
		int* P7;


		int* PResult;
		int* P1Result;



		A11 = new int[HalfSize * HalfSize];
		A12 = new int[HalfSize * HalfSize];
		A21 = new int[HalfSize * HalfSize];
		A22 = new int[HalfSize * HalfSize];

		B11 = new int[HalfSize * HalfSize];
		B12 = new int[HalfSize * HalfSize];
		B21 = new int[HalfSize * HalfSize];
		B22 = new int[HalfSize * HalfSize];

		C11 = new int[HalfSize * HalfSize];
		C12 = new int[HalfSize * HalfSize];
		C21 = new int[HalfSize * HalfSize];
		C22 = new int[HalfSize * HalfSize];

		P1 = new int[HalfSize * HalfSize];
		P2 = new int[HalfSize * HalfSize];
		P3 = new int[HalfSize * HalfSize];
		P4 = new int[HalfSize * HalfSize];
		P5 = new int[HalfSize * HalfSize];
		P6 = new int[HalfSize * HalfSize];
		P7 = new int[HalfSize * HalfSize];

		PResult = new int[HalfSize * HalfSize];
		P1Result = new int[HalfSize * HalfSize];




#pragma omp  for default(shared)
		for (int i = 0; i < HalfSize; i++)
		{
			for (int j = 0; j < HalfSize; j++)
			{
				A11[i * HalfSize + j] = MatrixA[i * N + j];
				A12[i * HalfSize + j] = MatrixA[i * N + (j + HalfSize)];
				A21[i * HalfSize + j] = MatrixA[(i + HalfSize) * N + j];
				A22[i * HalfSize + j] = MatrixA[(i + HalfSize) * N + (j + HalfSize)];

				B11[i * HalfSize + j] = MatrixB[i * N + j];
				B12[i * HalfSize + j] = MatrixB[i * N + (j + HalfSize)];
				B21[i * HalfSize + j] = MatrixB[(i + HalfSize) * N + j];
				B22[i * HalfSize + j] = MatrixB[(i + HalfSize) * N + (j + HalfSize)];

			}
		}

#pragma omp task 
		{
			int* AResult = new int[HalfSize * HalfSize];
			int* BResult = new int[HalfSize * HalfSize];
			ADD(A11, A22, AResult, HalfSize);
			ADD(B11, B22, BResult, HalfSize);
			ParallelStrassen(AResult, BResult, P1, HalfSize);
		}



#pragma omp task 
		{
			int* AResult = new int[HalfSize * HalfSize];
			ADD(A21, A22, AResult, HalfSize);
			ParallelStrassen(AResult, B11, P2, HalfSize);
		}


#pragma omp task 
		{
			int* BResult = new int[HalfSize * HalfSize];
			SUB(B12, B22, BResult, HalfSize);
			ParallelStrassen(A11, BResult, P3, HalfSize);
		}

#pragma omp task 
		{
			int* BResult = new int[HalfSize * HalfSize];
			SUB(B21, B11, BResult, HalfSize);
			ParallelStrassen(A22, BResult, P4, HalfSize);
		}



#pragma omp task 
		{
			int* AResult = new int[HalfSize * HalfSize];
			ADD(A11, A12, AResult, HalfSize);
			ParallelStrassen(AResult, B22, P5, HalfSize);
		}



#pragma omp task 
		{
			int* AResult = new int[HalfSize * HalfSize];
			int* BResult = new int[HalfSize * HalfSize];
			SUB(A21, A11, AResult, HalfSize);
			ADD(B11, B12, BResult, HalfSize);
			ParallelStrassen(AResult, BResult, P6, HalfSize);
		}

#pragma omp task 
		{
			int* AResult = new int[HalfSize * HalfSize];
			int* BResult = new int[HalfSize * HalfSize];
			SUB(A12, A22, AResult, HalfSize);
			ADD(B21, B22, BResult, HalfSize);
			ParallelStrassen(AResult, BResult, P7, HalfSize);
		}
#pragma omp taskwait

		ADD(P1, P4, PResult, HalfSize);
		SUB(P7, P5, P1Result, HalfSize);
		ADD(PResult, P1Result, C11, HalfSize);

		ADD(P3, P5, C12, HalfSize);

		ADD(P2, P4, C21, HalfSize);

		ADD(P1, P3, PResult, HalfSize);
		SUB(P6, P2, P1Result, HalfSize);
		ADD(PResult, P1Result, C22, HalfSize);


#pragma omp  for default(shared)
		for (int i = 0; i < HalfSize; i++)
		{
			for (int j = 0; j < HalfSize; j++)
			{
				MatrixC[i * N + j] = C11[i * HalfSize + j];
				MatrixC[i * N + (j + HalfSize)] = C12[i * HalfSize + j];
				MatrixC[(i + HalfSize) * N + j] = C21[i * HalfSize + j];
				MatrixC[(i + HalfSize) * N + (j + HalfSize)] = C22[i * HalfSize + j];
			}
		}



		delete[] A11; delete[] A12; delete[] A21; delete[] A22;
		delete[] B11; delete[] B12; delete[] B21; delete[] B22;
		delete[] C11; delete[] C12; delete[] C21; delete[] C22;
		delete[] P1; delete[] P2; delete[] P3; delete[] P4; delete[] P5;
		delete[] P6; delete[] P7;
		delete[] PResult;
		delete[] P1Result;

	}


	return 0;
}
int OMPStrassen(int *MatrixA, int *MatrixB, int *MatrixC, int N)
{
#pragma omp parallel 
	{
#pragma omp single
		{
			ParallelStrassen(MatrixA, MatrixB, MatrixC, N);
		}
	}
	return 0;
}