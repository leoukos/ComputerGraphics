#include <stdio.h>
#include <stdlib.h>

void isoline(double *A, size_t n1, size_t n2, double seuil);

int main()
{
	double A1[4][4]={0,0,1,1,0,1,0,0,0,1,1,1,0,0,1,1};
	double *A=(double*)malloc(4*4*sizeof(double));
	//double A[2][2]={1,0,0,1};
	double seuil=0.5;
	size_t n=4;
	size_t i,j;
	int l;
	double p[4][2];

	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			A[i+4*j]=A1[i][j];
		}
	}

	isoline(A, 4, 4, 0.5);

	return 0;
}

void isoline(double *A, size_t n1, size_t n2, double seuil)
{
	size_t i,j;
	int l;
	double p[4][2];

	for(i=0; i<n1-1; i++){
		for(j=0; j<n2-1; j++){
			l=0;
			if(A[i+n2*j]>seuil && A[i+1+n2*j]<seuil ||
				A[i+n2*j]<seuil && A[i+1+n2*j]>seuil){
				p[l][0]=i+0.5;
				p[l][1]=j;
				l++;
			}
			if(A[i+1+n2*j]>seuil && A[i+1+n2*(j+1)]<seuil ||
				A[i+1+n2*j]<seuil && A[i+1+n2*(j+1)]>seuil){
				p[l][0]=i+1;
				p[l][1]=j+0.5;
				l++;
			}
			if(A[i+1+n2*(j+1)]>seuil && A[i+n2*(j+1)]<seuil ||
				A[i+1+n2*(j+1)]<seuil && A[i+n2*(j+1)]>seuil){
				p[l][0]=i+0.5;
				p[l][1]=j+0.5;
				l++;
			}
			if(A[i+n2*(j+1)]>seuil && A[i+n2*j]<seuil ||
				A[i+n2*(j+1)]<seuil && A[i+n2*j]>seuil){
				p[l][0]=i;
				p[l][1]=j+0.5;
				l++;
			}

			switch(l){
				case 0:
					printf("Cas 0\n");
					break;
				case 2:
					printf("Cas 1 ou 2\n");
					break;
				case 4:
					printf("Cas 3\n");
					break;
			}
		}
	}
}

/*
void isoline(double *A, size_t n1, size_t n2, double seuil)
{
	size_t i,j;
	int l;
	double p[4][2];

	for(i=0; i<n1-1; i++){
		for(j=0; j<n2-1; j++){
			l=0;
			if(A[i][j]>seuil && A[i+1][j]<seuil ||
				A[i][j]<seuil && A[i+1][j]>seuil){
				p[l][0]=i+0.5;
				p[l][1]=j;
				l++;
			}
			if(A[i+1][j]>seuil && A[i+1][j+1]<seuil ||
				A[i+1][j]<seuil && A[i+1][j+1]>seuil){
				p[l][0]=i+1;
				p[l][1]=j+0.5;
				l++;
			}
			if(A[i+1][j+1]>seuil && A[i][j+1]<seuil ||
				A[i+1][j+1]<seuil && A[i][j+1]>seuil){
				p[l][0]=i+0.5;
				p[l][1]=j+0.5;
				l++;
			}
			if(A[i][j+1]>seuil && A[i][j]<seuil ||
				A[i][j+1]<seuil && A[i][j]>seuil){
				p[l][0]=i;
				p[l][1]=j+0.5;
				l++;
			}

			switch(l){
				case 0:
					printf("Cas 0\n");
					break;
				case 2:
					printf("Cas 1 ou 2\n");
					break;
				case 4:
					printf("Cas 3\n");
					break;
			}
		}
	}
}
*/
