//Matrix Vector Multiplication

#include<mpi.h>
#include<stdio.h>
#include<math.h>
int main(int argc,char **argv)
{
	MPI_Init(NULL, NULL);
	MPI_Status status;
	MPI_Init(&argc, &argv); 
	double mat[4][4]={1,1,1,1,
			  1,1,1,1,
			  1,1,1,1,
			  1,1,1,1},vec[4]={1,1,1,1},recv_buf[4];	
	MPI_Init(&argc,&argv);
	int world_size,my_rank;
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Bcast(&vec,4,MPI_FLOAT,0,MPI_COMM_WORLD);
	MPI_Scatter(&mat,4,MPI_DOUBLE,&recv_buf,4,MPI_DOUBLE,0,MPI_COMM_WORLD);
	double mult=0,temp[4],final_res[4];
	for(int i=0;i<4;i++)
		mult+=recv_buf[i]*vec[i];
	MPI_Gather(&mult,1,MPI_DOUBLE,&final_res,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	if(my_rank==0){
		
		printf("Matrix Vector Multiplication is \n");
		for(int j=0;j<4;j++){
			printf("%f\n",final_res[j]);
		}	
	}
	MPI_Finalize();
}
