#include <omp.h>
#include <stdio.h>
// nvc++ -mp=gpu -Minfo -o hello hello.cpp
int main(int argc, char *argv[]) {
#pragma omp target teams parallel \
num_teams(108) thread_limit(4*32)
{
printf("Hello world from (%d, %d)!\n",
omp_get_team_num(),
omp_get_thread_num());
} // end target teams parallel
return(0);
}