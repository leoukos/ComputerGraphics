#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

#define LARGEUR_ECRAN 640
#define HAUTEUR_ECRAN 480

#define L1 10
#define L2 5

void dessiner(int n, int X0, int Y0);
void dessiner_T(int scale, int X0, int Y0);
void dessiner_Y(int scale, int X0, int Y0);

int main(int argc, char *argv[])
{
	bool continuer;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);

    SDL_WM_SetCaption("Dessin recursif", NULL);
    SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_OPENGL);

    SDL_EnableKeyRepeat(10,10);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,LARGEUR_ECRAN,0,HAUTEUR_ECRAN);


	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	dessiner(10,LARGEUR_ECRAN/2,0);
	glFlush();
	SDL_GL_SwapBuffers();
	
    while(continuer)
    {
	 	SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
					continuer=false;
			}
    }
	
	SDL_Quit();
    return 0;
}

void dessiner(int n, int X0, int Y0)
{

	if(n==0){
		return;
	}
	if(n>0){
		dessiner_T(n, X0, Y0);
		dessiner(n-1, X0+n*L2, Y0+n*L1);
		dessiner(n-1, X0-n*L2, Y0+n*L1);
	}

}

void dessiner_T(int scale, int X0, int Y0)
{
	glTranslated(X0, Y0, 0);
	glColor3ub(255,0,0);
	glBegin(GL_LINES);
		glVertex2d(0, 0);
		glVertex2d(0, scale*L1);
	glEnd();

	glTranslated(0, scale*L1, 0);
	glColor3ub(0,255,0);
	glBegin(GL_LINES);
		glVertex2d(-scale*L2, 0);
		glVertex2d(scale*L2, 0);
	glEnd();

	glTranslated(0, -scale*L1, 0);
	glTranslated(-X0, -Y0, 0);

}

void dessiner_Y(int scale, int X0, int Y0)
{
	glTranslated(X0, Y0, 0);
	glColor3ub(255,0,0);
	glBegin(GL_LINES);
		glVertex2d(0, 0);
		glVertex2d(0, scale*L1);
	glEnd();

	glTranslated(0, scale*L1, 0);
	glRotated(+45, 0, 0, 1);
	glColor3ub(0,255,0);
	glBegin(GL_LINES);
		glVertex2d(0, 0);
		glVertex2d(scale*L2, 0);
	glEnd();

	glRotated(+90, 0, 0, 1);
	glColor3ub(0,0,255);
	glBegin(GL_LINES);
		glVertex2d(0, 0);
		glVertex2d(scale*L2, 0);
	glEnd();

	glRotated(+45, 0, 0, 1);
	glTranslated(0, -scale*L1, 0);
	glTranslated(-X0, -Y0, 0);

}
