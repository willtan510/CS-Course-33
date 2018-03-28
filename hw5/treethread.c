#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int Tthreads;
pthread_t *tid;
void join(int threadnum);
void * threadFunc(void* startIndex);


int main(int argc, char** argv)
{
  int nthreads;
  
  if(argc!= 2)
    {
      printf("Wrong number of arguments\n");
      exit(1);
    }
  nthreads=atoi(argv[1]);

  if (nthreads<1)
    {
      printf("Argument must be positive\n");
      exit(1);
    }
  Tthreads=(2<<(nthreads-1))-2;


  tid=(pthread_t*) malloc(sizeof(pthread_t) *(Tthreads+1));
  int temp[Tthreads+1];
  int i;
   int j;
  for (i=0;i<Tthreads+1;i++)
    {
      temp[i]=i;
    }
 
  for (j=0;j<Tthreads+1;j++)
    {
       pthread_create(&tid[j],NULL,threadFunc,temp+j);
    }
 
  join(0);

    
  
  //pthread_join(tid[0],NULL);
  //pthread_join(tid[1],NULL);
  //pthread_join(tid[2],NULL);

  exit(0);
  
}


void join(int threadnum)
{

  if ((2*threadnum) < (Tthreads))
    {
      join((threadnum*2)+1);
      join((threadnum*2)+2);
    }
  printf("Thread %i%s",threadnum ," done\n");
  pthread_join(tid[threadnum],NULL);
}

void * threadFunc(void* startIndex)
{
  //int* arg= (int*) startIndex;
  //int id=*arg;
  /*  int temp[2];
  temp[0]=(2*id)+1;
  temp[1]=(2*id)+2;
  if ((2*id)<(Tthreads-1))
  {
    pthread_create(&tid[(2*id)+1],NULL,threadFunc,temp);
    pthread_create(&tid[(2*id)+2],NULL,threadFunc,temp+1);
    }*/

  //printf("Thread %i%s",id ," is done\n");
  return NULL;
}
