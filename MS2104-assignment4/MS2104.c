//Composite Simpson's Rule

#include<stdio.h>
#include<math.h>
#include<mpi.h>
#define FUNCTION(x) (2 + sin(2*sqrt(x)))
int main(int argc, char *argv[])
{
	MPI_Init(NULL, NULL);
	MPI_Status status;
	MPI_Init(&argc, &argv); 
	double a=2, b=10; 
	int numberOfIntervals=9, world_size, my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	double h = (b-a)/numberOfIntervals;
	double x = a + my_rank*h;
	double f_x = FUNCTION(x);
	double y, y_1, y_2, y_3;
	
	if(my_rank == 0 || my_rank == world_size)
	{
		MPI_Reduce(&f_x, &y_1, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	}
	else if(my_rank%3 == 0)
	{
		f_x *= 2;
		MPI_Reduce(&f_x, &y_2, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	}
	else
	{
		f_x *= 3;
		MPI_Reduce(&f_x, &y_3, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	}
	if(my_rank == 0)
	{
		y = y_1 + y_2 + y_3;
		y = 3*h*y/8;
		
		printf("Y = %f\n", y);
	}
	MPI_Finalize();
        return 0;
}
