#include<stdio.h>
#include<GL/glut.h>
#include<unistd.h>
#include<GL/glu.h>
#include<math.h>

float x=125,y=125,x1,Y1,x2=275,y2=125,x3,y3,rad=25;
float angle=1,t1,t2,ang,intr=1;
float trck[6][2]={{100,150},{300,150},{300,225},{225,225},{225,300},{100,305}};
float chopar[11][2]={{100,750},{300,750},{350,800},{300,850},{100,850},{50,800},{0,800},{200,850},{200,900},{150,900},{250,900}};
float light[3][2]={{150,750},{100,150},{300,150}};
void drawcircle(int cx,int cy, int r){
	int x=0,y=r,p = 3/2 - r;
	while(x<=y){	
		glBegin(GL_POINTS);
			glVertex2f(cx+x,cy+y);
			glVertex2f(cx+y,cy+x);		
			glVertex2f(cx-x,cy+y);
			glVertex2f(cx+y,cy-x);
			glVertex2f(cx-x,cy-y);
			glVertex2f(cx-y,cy-x);
			glVertex2f(cx+x,cy-y);
			glVertex2f(cx-y,cy+x);
		glEnd();
		if (p<0){
			p += (2*x)+3;
		}
		else {
			p += (2*(x-y))+5;
			y -= 1;
		}
		x++;
	}  
}

void truck (void)
{
	int i;
    glColor3f (1.0, 0.0, 0.0);
    glBegin (GL_POLYGON);
    for(i=0;i<6;i++){
	    glVertex2f(trck[i][0],trck[i][1]);
	}
	glEnd();
}
void choper (void) {
   int i;
    glColor3f (0.0, 0.0, 1.0);
    glBegin (GL_POLYGON);
    for(i=0;i<6;i++){
	    glVertex2f(chopar[i][0],chopar[i][1]);
	}
	glEnd();
	glBegin (GL_LINES);
    for(i=5;i<11;i++){
	    glVertex2f(chopar[i][0],chopar[i][1]);
	}
	glEnd();
}
void lit(void)
{
    glColor3f (1,1, 0.0);
    glBegin (GL_POLYGON);
	    glVertex2f((chopar[0][0]+chopar[1][0])/2,chopar[0][1]);
	    glVertex2f(trck[0][0]-50,100);
	    glVertex2f(trck[1][0]+50,100);
	glEnd();
}


void movetruck(){
	int i;	
	for(i=0;i<6;i++){
			trck[i][0]+=1.64;
	}
	glutPostRedisplay();
}

void movechoper(){
	int i;	
	for(i=0;i<11;i++){
			chopar[i][0]+=1.15;
	}
	chopar[9][0]+=intr;
	chopar[10][0]-=intr;
	glutPostRedisplay();
	
}

void display(){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(1500,0);
		glVertex2f(1500,100);
		glVertex2f(0,100);
	glEnd();		
	
	angle=angle+1;
	choper();
	lit();
	truck();
	tyre();
	movetruck();
	movechoper();
	glutSwapBuffers();
	glFlush();
	usleep(8000);
}

void main(int argc , char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition(100,100);
	glutInitWindowSize(750,500);
	glutCreateWindow("Animation");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(300,1300,0,1000);
	glutDisplayFunc(display);
	glutMainLoop();
}

