#include <iostream>
#include "mpi.h" 

const int len = 4;
int matrix[len][len] = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };

int main()
{
	MPI_Init(NULL, NULL);

	int process_id;
	MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
	int num_proc;
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

	int * res = new int[len];	

	for (int j = 0; j < len; j++)
	{
		res[j] = 0;
	}

	int n = len / (num_proc - 1);

	//cd C:\Users\sasha\source\repos\ch_lab4\x64\Debug
	//mpiexec -n 5 chlab4.exe

	if (process_id == 0)
	{
		for (int i = 1; i < num_proc; i++)
		{
			MPI_Recv(res, len, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			for (int j = 0; j < len; j++)
			{
				std::cout << res[j] << " ";
			}
			std::cout << '\n';
		}
	}
	else
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < len; k++)
			{
				for (int l = 0; l < len; l++)
				{
					res[k] += matrix[j + process_id - 1][l] * matrix[l][k];
				}
			}
			MPI_Send(res, len, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}	
	MPI_Finalize();
}


