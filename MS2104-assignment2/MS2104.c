//Parallel Trapezoidal //

#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <mpi.h>
 
double f(double x)
{   return sqrt(x*x + 3*x+2);
} 
 
double Trap(double start_point, double end_point,int trap_count, double base_len ) 
{
   double estimate, x; 
   int i;
   estimate = (f(start_point) + f(end_point))/2.0;
   for (i = 1; i <= trap_count-1; i++) 
   {
      x = start_point + i*base_len;
      estimate += f(x);
   }
   estimate = estimate*base_len;

   return estimate;
}     


int main(int argc, char ** argv) 
{
   int my_rank, comm_size, n = 102, loc_n;   
   double a = 0.0, b = 4.0, h, loc_a, loc_b;
    //h = h/comm_size;
   double loc_int = 0.0;
   double total_int;
   int source; 
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
   h = (double)(b-a)/n;          
   loc_n = n/comm_size; 
   loc_a = a + my_rank*loc_n* h;
   loc_b = loc_a + loc_n*h;
   loc_int = Trap(loc_a, loc_b, loc_n, h);
   if (my_rank != 0) 
   { 
      MPI_Send(&loc_int, 1, MPI_DOUBLE, 0, 0, 
            MPI_COMM_WORLD); 
   } 
   else 
   {
      total_int = loc_int;
      for (source = 1; source < comm_size; source++) 
      {
         MPI_Recv(&loc_int, 1, MPI_DOUBLE, source, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         total_int += loc_int;
      }
   } 
   if (my_rank == 0) {
      printf("Total Integral from %f to %f = %f\n",
          a, b, total_int);
   }
   MPI_Finalize();
   return 0;
}
