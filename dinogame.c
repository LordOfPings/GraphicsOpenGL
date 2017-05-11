#include<stdio.h>
#include<GL/glut.h>
#include<unistd.h>
#include<GL/glu.h>
#include<math.h>

float x=1100,y=100,x1,Y1,x2=1800,y2=100,x3,y3,x4=2500,y4=100,x5,y5,rad=50;
float angle=1,t1,t2,ang;
float angle2 = 0,da=3.0,time=5000;
int points,go=0,gs=1;
char tmp_str[40];
float dino[25][2]={{-260,260},{-260,370},{-230,400},{-180,400},{-130,380},{-130,360},{-145,350},{-130,340},{-130,330},{-200,320},{-200,180},{-290,140},{-400,180},{-400,220},{-360,190},{-290,150},{-290,100},{-260,50},{-270,150},{-270,100},{-240,50},{-220,240},{-150,260},{-120,240},{-165,360}};
void jump();
void drawcircle(int cx,int cy, int r,int a){  		//function to generate disks
	int x=0,y=r,p = 3/2 - r;
	while(x<=y){
		if(a==1){
			glBegin(GL_POINTS);
		}
		else{
			glBegin(GL_POLYGON);
		}
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

void body (void)			//generate body of the dino
{
	int i;
    glColor3f (1.0, 0.6, 0.0);
    glBegin (GL_POLYGON);
    for(i=0;i<13;i++){
	    glVertex2f(dino[i][0],dino[i][1]);
	}
	glEnd();
	glBegin (GL_POLYGON);
    	for(i=12;i<15;i++){
	    glVertex2f(dino[i][0],dino[i][1]);
	}
	glEnd();
}
void hands (void) {				//hands of the dino
    glColor3f(1.0,0.4,0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(dino[21][0],dino[21][1]);
    glVertex2f(dino[22][0],dino[22][1]);
    glVertex2f(dino[22][0],dino[22][1]);
    glVertex2f(dino[23][0],dino[23][1]); 
    glEnd();
}
void eyes(void){
    glColor3f (0, 0, 0);
    glPushMatrix();
    drawcircle(dino[24][0],dino[24][1],10,0);       
    glPopMatrix();
}

void legs (void)				//function to generate legs of dino
{

    glColor3f (1.0, 0.8, 0.0);
    
    glPushMatrix();
   
    glLineWidth(5);
    glBegin(GL_LINES);    
    glVertex2i (dino[15][0],dino[15][1]);
    glVertex2i (dino[16][0],dino[16][1]);
    glVertex2i (dino[16][0],dino[16][1]);
    glVertex2i (dino[17][0],dino[17][1]);    
    glEnd();
    
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2i (dino[18][0],dino[18][1]);
    glVertex2i (dino[19][0],dino[19][1]);
    glVertex2i (dino[19][0],dino[19][1]);
    glVertex2i (dino[20][0],dino[20][1]);    
    glEnd();
    
    glPopMatrix();
}

void Write(char *string)				//score display
{
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void Walk (void)				//moving the legs
{
    
    
    /*t1=dino[16][0]-dino[15][0],t2=dino[16][1]-dino[15][1];
	dino[16][0] = dino[15][0]+t1*cos(da)-t2*sin(da);
	dino[16][1]= dino[15][1]+t1*sin(da)+t2*cos(da);
	
	t1=dino[17][0]-dino[15][0],t2=dino[17][1]-dino[15][1];
	dino[17][0] = dino[15][0]+t1*cos(da)-t2*sin(da);
	dino[17][1]= dino[15][1]+t1*sin(da)+t2*cos(da);*/
	
	dino[16][0] = dino[16][0]+da;
	dino[16][1]= dino[16][1]+da;
	
	dino[17][0] = dino[17][0]+da;
	dino[17][1]= dino[17][1]+da;
	
	dino[19][0] = dino[19][0]+da;
	dino[19][1]= dino[19][1]+da;
	
	dino[20][0] = dino[20][0]+da;
	dino[20][1]= dino[20][1]+da;
    da =  -da;
    glutPostRedisplay();
    
}

void display(){
	if(gs==1){									// start screen condition
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.3,0.8,0.1);
		glColor3f(1, 1, 0);
	    glRasterPos2f(175,450);
	    sprintf(tmp_str, "DINO JUMP");
	    Write(tmp_str);
	    glRasterPos2f(150,400);
	    sprintf(tmp_str, "Press SPACE to start");
	    Write(tmp_str);
	    glRasterPos2f(150,300);
	    sprintf(tmp_str, "Press UP to jump");
	    Write(tmp_str);
	    glFlush();
	}
	if(go==0 && gs==0){								//gameplay
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.3,0.8,0.1);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-500,0);
		glVertex2f(1000,0);
		glVertex2f(1000,50);
		glVertex2f(-500,50);
	glEnd();

	glColor3f(1,0.0,0.0);			//disks movements
	drawcircle(x,y,rad,1);
	x1=x+rad;
	Y1=y;
	ang = (angle*3.14159265)/180;
	t1=x1-x,t2=Y1-y;
	x1 = x+t1*cos(ang)-t2*sin(ang);
	Y1 = y+t1*sin(ang)+t2*cos(ang);
	glBegin(GL_LINES);
		glVertex2f(x,y);
		glVertex2f(x1,Y1);
		glVertex2f(x,y);
		glVertex2f(2*x-x1,2*y-Y1);
	glEnd();
	ang = (90*3.14159265)/180;
	t1=x1-x,t2=Y1-y;
	x1 = x+t1*cos(ang)-t2*sin(ang);
	Y1 = y+t1*sin(ang)+t2*cos(ang);
	glBegin(GL_LINES);
		glVertex2f(x,y);
		glVertex2f(x1,Y1);
		glVertex2f(x,y);
		glVertex2f(2*x-x1,2*y-Y1);
	glEnd();
	x=x-1.64;
	if(x<-1000)
		x=1100;
	
	glColor3f(0,1.0,0.0);	
	drawcircle(x2,y2,rad,1);
	x3=x2+rad;
	y3=y2;
	ang = (angle*3.14159265)/180;
	t1=x3-x2,t2=y3-y2;
	x3 = x2+t1*cos(ang)-t2*sin(ang);
	y3 = y2+t1*sin(ang)+t2*cos(ang);
	glBegin(GL_LINES);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glVertex2f(x2,y2);
		glVertex2f(2*x2-x3,2*y2-y3);
	glEnd();
	ang = (90*3.14159265)/180;
	t1=x3-x2,t2=y3-y2;
	x3 = x2+t1*cos(ang)-t2*sin(ang);
	y3 = y2+t1*sin(ang)+t2*cos(ang);
	glBegin(GL_LINES);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glVertex2f(x2,y2);
		glVertex2f(2*x2-x3,2*y2-y3);
	glEnd();
	x2=x2-1.64;
	if(x2<-1000)
		x2=1100;
	
	glColor3f(1,1.0,0.0);
	drawcircle(x4,y4,rad,1);
	x5=x4+rad;
	y5=y4;
	ang = (angle*3.14159265)/180;
	t1=x5-x4,t2=y5-y4;
	x5 = x4+t1*cos(ang)-t2*sin(ang);
	y5 = y4+t1*sin(ang)+t2*cos(ang);
	glBegin(GL_LINES);
		glVertex2f(x4,y4);
		glVertex2f(x5,y5);
		glVertex2f(x4,y4);
		glVertex2f(2*x4-x5,2*y4-y5);
	glEnd();
	ang = (90*3.14159265)/180;
	t1=x5-x4,t2=y5-y4;
	x5 = x4+t1*cos(ang)-t2*sin(ang);
	y5 = y4+t1*sin(ang)+t2*cos(ang);
	glBegin(GL_LINES);
		glVertex2f(x4,y4);
		glVertex2f(x5,y5);
		glVertex2f(x4,y4);
		glVertex2f(2*x4-x5,2*y4-y5);
	glEnd();
	x4=x4-1.64;
	if(x4<-1000){
		x4=1100;
	}
	angle=angle+1;

    glColor3f(1, 1, 0);						//displaying scores
    glRasterPos2f(750,800);
    sprintf(tmp_str, "Points: %d",points);
    Write(tmp_str);
    
    body ();
    hands();
    eyes();
    legs ();
    
	glutSwapBuffers ();
	//game over display
	if(((x-rad<dino[17][0])&&(y+rad>dino[17][1])&&(x+rad>dino[17][0]))||((x2-rad<dino[17][0])&&(y2+rad>dino[17][1])&&(x2+rad>dino[17][0]))||((x4-rad<dino[17][0])&&(y4+rad>dino[17][1])&&(x4+rad>dino[17][0]))){
		glRasterPos2f(200,500);
	    sprintf(tmp_str,"GAME OVER");
	    Write(tmp_str);
	    glRasterPos2f(175,450);
	    sprintf(tmp_str,"press ESC to exit");
	    Write(tmp_str);
	    go=1;
	}
	glFlush();
	usleep(time);
	if(time>500){
		time-=0.4;
	}
	}
}

void spac(unsigned char key, int x, int y){		//keyboard function
	if(key==27){
		exit(0);
	}
	if(key==32){
		gs=0;
	}
}

void keys(int key, int x, int y){			//Special keys to jump
	if(key==GLUT_KEY_UP){
		jump();
	}	
}

void main(int argc , char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition(100,100);
	glutInitWindowSize(750,500);
	glutCreateWindow("Dino Jump");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500,1000,0,1000);
	glutDisplayFunc(display);
	glutIdleFunc(Walk);
	glutSpecialFunc(keys);
	glutKeyboardFunc(spac);
	glutIgnoreKeyRepeat(1);
	glutMainLoop();
}

void jump(){					//jumping the dino
	int i,j;	
	for(i=0;i<180;i++){
		for(j=0;j<25;j++){
			dino[j][1]+=1;
		}
		display();
	}
	for(i=0;i<180;i++){
		for(j=0;j<25;j++){
			dino[j][1]-=1;
		}
		display();
	}
	points++;
}

