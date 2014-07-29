#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h> 

#define LARGEUR_ECRAN 640
#define HAUTEUR_ECRAN 480

void scene(int nu);
int selection(int x, int y, int val);

int main()
{
	int continuer=1;
	int val=0;
	SDL_Event event;


	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);

	SDL_WM_SetCaption("Picking", NULL);
	SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_OPENGL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,3,0,3);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	scene(val);

	glFlush();
	SDL_GL_SwapBuffers();

	while(continuer){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				continuer=0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_a:
						selection(2, 2, val);

						if(val==1)
							val=0;
						else
							val=1;

						
						glClear(GL_COLOR_BUFFER_BIT);
						glMatrixMode(GL_MODELVIEW);
						glLoadIdentity();
						scene(val);
						glFlush();
						SDL_GL_SwapBuffers();
				}
		}
	}

	return 0;
}

void scene(int nu)
{
	int i, j, l=0;
	double x, y;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(nu==0){
				if((i+j)%2==0)
					glColor3ub(255,255,255);
				else
					glColor3ub(0,0,0);
			}else{
				if((i+j)%2==0)
					glColor3ub(0,0,0);
				else
					glColor3ub(255,255,255);
			}

			x=i;
			y=j;
			glPushName(l);
			glBegin(GL_QUADS);
				glVertex2d(x, y);
				glVertex2d(x, y+1);
				glVertex2d(x+1, y+1);
				glVertex2d(x+1, y);
			glEnd();

			l++;
		}
	}
	
}

int selection(int mouseX, int mouseY, int val)
{
	int new_val;
	GLuint selectBuffer[512];
	GLint viewport[4];
	int hits;
	float ratio;

	glSelectBuffer(512, selectBuffer);
	glRenderMode(GL_SELECT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluPickMatrix(mouseX, mouseY, 5, 5, viewport);
	ratio = (viewport[2]+0.0) / viewport[3];
	//gluPerspective(45, ratio, 0.1, 1000);
	gluOrtho2D(0,3,0,3);
	glMatrixMode(GL_MODELVIEW);
	glInitNames();

	scene(val);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	
	hits=glRenderMode(GL_RENDER);
	printf("%d hits\n", hits);
	if(hits>0){
		printf("number of names = %d\n", selectBuffer[0]);
		printf("hit on tile %d\n",  selectBuffer[3]);
	}

	return 0;
}
