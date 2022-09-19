//Parallel Addition//


#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int main(int argc, char** argv)
{
MPI_Init(&argc, &argv);
MPI_Status status;

int first_no,last_no,n,s,N,i,world_size,my_rank,partial_sum,sum=0,tag=0,temp;

FILE *inptr,*outptr;
inptr=fopen("input.txt","r");
outptr=fopen("output.txt","w");
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


if (inptr == NULL || outptr == NULL)
{
printf("Error! Could not open file \n");
exit(-1);
}

fscanf(inptr, "%d", &N);
fprintf(outptr, "%d \n", N);

int *a;
a = (int*)malloc(sizeof(int));

for(i=0;i<N;i++)
fscanf(inptr, "%d", &a[i]);

for(i=0;i<N;i++)
fscanf(outptr, "%d \n",&a[i]);

n = N/world_size;
first_no = my_rank*n;

if(my_rank == world_size-1)
last_no=N;
else
last_no = first_no + n;
for(i=first_no;i<last_no;i++)
{
sum += a[i];
}
printf("\nLocalSum : %d,Rank=%d",sum,my_rank);
fprintf(outptr,"\nLocalSum : %d,Rank=%d",sum,my_rank);
if (my_rank!=0)
MPI_Send(&sum, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
else
{
for(i=1;i<world_size;++i)
{
MPI_Recv(&s,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
sum+=s;
}
}
printf("\n Final Sum is : %d", sum);
fprintf(outptr, "\n Final Sum is : %d", sum);

    fclose(inptr);
    fclose(outptr);
    MPI_Finalize();
}

