#include "func.h"
#include "util.h"
#define NUMTHREADS 29

void func0(double *weights, double *arrayX, double *arrayY, int xr, int yr, int n)
{
	int i;
	double nTemp= 1/((double)(n));
#pragma omp parallel for num_threads(NUMTHREADS) private(i) firstprivate(n,weights,nTemp,arrayX,arrayY,xr,yr)
	for(i = 0; i < n; i++){
		weights[i] = nTemp;
		arrayX[i] = xr;
		arrayY[i] = yr;
	}
}

void func1(int *seed, int *array, double *arrayX, double *arrayY,
			double *probability, double *objxy, int *index,
			int Ones, int iter, int X, int Y, int Z, int n)
{

  int i, j, temp;
  int index_X, index_Y, arrayTemp1,arrayTemp2;
  int max_size = X*Y*Z;
  double probabilityTemp, onesTemp;
  onesTemp=(double) Ones;
  
#pragma omp parallel for num_threads(NUMTHREADS) private(i) firstprivate(n,seed,arrayX,arrayY)
   	for(i = 0; i < n; i++){
   		arrayX[i] += 1 + 5*rand2(seed, i);
   		arrayY[i] += -2 + 2*rand2(seed, i);
   	}
	
#pragma omp parallel for num_threads(NUMTHREADS) private(i,j,temp,arrayTemp1,arrayTemp2,probabilityTemp,  index_X,index_Y) firstprivate(Ones, iter, Y, Z, n, max_size,array,arrayX,arrayY,objxy,index,onesTemp)
   	for(i = 0; i<n; i++){
	  arrayTemp1= i*Ones;
   		for(j = 0; j < Ones; j++){
		  temp=j*2;
		  index_X = round(arrayX[i]) + objxy[temp + 1];
   			index_Y = round(arrayY[i]) + objxy[temp];
   			arrayTemp2 = fabs(index_X*Y*Z + index_Y*Z + iter);
   			if(arrayTemp2 >= max_size)
   				index[arrayTemp1 + j] = 0;
			else
			  index[arrayTemp1 +j]=arrayTemp2;
   		}
   		probabilityTemp = 0;

   		for(j = 0; j < Ones; j++) {
		  arrayTemp2=array[index[arrayTemp1+j]];
		  probabilityTemp += (pow((arrayTemp2 - 100),2) -
				      pow((arrayTemp2-228),2)) / 50.0;
   		}
   		probability[i] = probabilityTemp / onesTemp;
   	}
}

void func2(double *weights, double *probability, int n)
{
  int i;
  double temp;
  double sumWeights=0;

#pragma omp parallel for num_threads(NUMTHREADS) private(i,temp) firstprivate(n,weights,probability) reduction(+:sumWeights)
	for(i = 0; i < n; i++)
	  {
	    temp = weights[i] * exp(probability[i]);
	    sumWeights += temp;
	    weights[i]=temp;
	  }
	
#pragma omp parallel for num_threads(NUMTHREADS) private(i) firstprivate(weights,sumWeights,n)
	for(i = 0; i < n; i++)
   		weights[i] /= sumWeights;
}

void func3(double *arrayX, double *arrayY, double *weights, double *x_e, double *y_e, int n)
{
	double estimate_x=0.0;
	double estimate_y=0.0;
    int i;
    double weightTemp;

#pragma omp parallel for num_threads(NUMTHREADS) private(i,weightTemp) firstprivate(n,arrayX,arrayY,weights) reduction(+:estimate_x,estimate_y)
	for(i = 0; i < n; i++){
	  weightTemp=weights[i];
	  estimate_x += arrayX[i] * weightTemp;
   	  estimate_y += arrayY[i] * weightTemp;
   	}

	*x_e = estimate_x;
	*y_e = estimate_y;

}

void func4(double *u, double u1, int n)
{
	int i;
	double nTemp=((double)(n));

#pragma omp parallel for num_threads(NUMTHREADS) private(i) firstprivate(n,u,u1,nTemp)
	for(i = 0; i < n; i++){
   		u[i] = u1 + i/nTemp;
   	}
}

void func5(double *x_j, double *y_j, double *arrayX, double *arrayY, double *weights, double *cfd, double *u, int n)
{
	int i, j;
	int nSubTemp=n-1;
	double nDivTemp=1/((double)(n));
#pragma omp parallel for num_threads(NUMTHREADS) private(i,j) firstprivate(n,cfd,u,x_j,y_j,arrayX,arrayY,weights)
	for(j = 0; j < n; j++){
   		//i = findIndex(cfd, n, u[j]);
   		i = findIndexBin(cfd, 0, n, u[j]);
   		if(i == -1)
   			i = nSubTemp;
   		x_j[j] = arrayX[i];
   		y_j[j] = arrayY[i];
	}

#pragma omp parallel for num_threads(NUMTHREADS) private(i) firstprivate(n,arrayX,arrayY,x_j,y_j,weights,nDivTemp)
	for(i=0;i<n;i++)
	  {
		arrayX[i] = x_j[i];
		arrayY[i] = y_j[i];
		weights[i] = nDivTemp;
	}
}
