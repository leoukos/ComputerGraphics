#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h> 

#define LARGEUR_ECRAN 640
#define HAUTEUR_ECRAN 480

void isoline(double *A, size_t n1, size_t n2, double seuil);

int main()
{
	int continuer=1;
	SDL_Event event;


	double *A;
	double seuil;
	size_t n1, n2, i, j;
	
	n1=4;
	n2=4;
	seuil=0.5;

	A=(double*)malloc(n1*n2*sizeof(double));
	memset(A, 0, n1*n2*sizeof(double));

	A[0]=0;
	A[1]=0;
	A[2]=1;
	A[3]=0;
	A[4]=0;
	A[5]=1;
	A[6]=0;
	A[7]=0;
	A[8]=1;
	A[9]=0;
	A[10]=1;
	A[11]=1;
	A[12]=0;
	A[13]=1;
	A[14]=0;
	A[15]=0;
	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);

	SDL_WM_SetCaption("Isolignes", NULL);
	SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_OPENGL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,n1-1,0,n2-1);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
		glVertex2d(0,0);
		glVertex2d(n1-1,0);
		glVertex2d(n1-1,n2-1);
		glVertex2d(0,n2-1);
	glEnd();
	glColor3ub(0,0,0);
	for(i=0; i<n1-1; i++){
		for(j=0; j<n2-1; j++){
			glBegin(GL_LINES);
				glVertex2d(i, j);
				glVertex2d(i+1, j);
				glVertex2d(i+1, j);
				glVertex2d(i+1, j+1);
				glVertex2d(i+1, j+1);
				glVertex2d(i, j+1);
				glVertex2d(i, j+1);
				glVertex2d(i, j);
			glEnd();
		}
	}
	glColor3ub(0,0,255);
	isoline(A, n1, n2, 0.25);
	glColor3ub(255,0,0);
	isoline(A, n1, n2, 0.5);
	glColor3ub(0,255,0);
	isoline(A, n1, n2, 0.75);
	glFlush();
	SDL_GL_SwapBuffers();

	while(continuer){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				continuer=0;
				break;
		}
	}

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

			// Side 1
			if(A[i+n1*j]>seuil && A[i+1+n1*j]<seuil){
				p[l][0]=i+1-(A[i+n1*j]-A[i+1+n1*j])*seuil;
				p[l][1]=j;
				l++;
			}else if(A[i+n1*j]<seuil && A[i+1+n1*j]>seuil){
				p[l][0]=i-(A[i+n1*j]-A[i+1+n1*j])*seuil;
				p[l][1]=j;
				l++;
			}

			// Side 2
			if(A[i+1+n1*j]>seuil && A[i+1+n1*(j+1)]<seuil){
				p[l][0]=i+1;
				p[l][1]=j+1-(A[i+1+n1*j]-A[i+1+n1*(j+1)])*seuil;
				l++;
			}else if(A[i+1+n1*j]<seuil && A[i+1+n1*(j+1)]>seuil){
				p[l][0]=i+1;
				p[l][1]=j-(A[i+1+n1*j]-A[i+1+n1*(j+1)])*seuil;
				l++;
			}

			// Side 3
			if(A[i+1+n1*(j+1)]>seuil && A[i+n1*(j+1)]<seuil){
				p[l][0]=i+(A[i+1+n1*(j+1)]-A[i+n1*(j+1)])*seuil;
				p[l][1]=j+1;
				l++;
			}else if(A[i+1+n1*(j+1)]<seuil && A[i+n1*(j+1)]>seuil){
				p[l][0]=i+1+(A[i+1+n1*(j+1)]-A[i+n1*(j+1)])*seuil;
				p[l][1]=j+1;
				l++;
			}

			// Side 4
			if(A[i+n1*(j+1)]>seuil && A[i+n1*j]<seuil){
				p[l][0]=i;
				p[l][1]=j+(A[i+n1*(j+1)]-A[i+n1*j])*seuil;
				l++;
			}else if(A[i+n1*(j+1)]<seuil && A[i+n1*j]>seuil){
				p[l][0]=i;
				p[l][1]=j+1+(A[i+n1*(j+1)]-A[i+n1*j])*seuil;
				l++;
			}

			switch(l){
				case 0:
					break;
				case 2:
					glBegin(GL_LINES);
						glVertex2d(p[0][0], p[0][1]);
						glVertex2d(p[1][0], p[1][1]);
					glEnd();
					break;
				case 4:
					glBegin(GL_LINES);
						glVertex2d(p[0][0], p[0][1]);
						glVertex2d(p[1][0], p[1][1]);
						glVertex2d(p[2][0], p[2][1]);
						glVertex2d(p[3][0], p[3][1]);
					glEnd();
					break;
			}
		}
	}
}
