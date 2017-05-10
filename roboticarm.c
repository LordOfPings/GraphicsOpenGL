#include<stdio.h>
#include<stdlib.h>
#include<GLUT/glut.h>
#include<unistd.h>
#include<math.h>

float co2[3]={-10,10,0},co3[3]={50,10,0},co4[3]={100,10,0},co1[2]={-90,10};
float temp[3];
static int interval=0;
float ep[3],sp[2];
int k,pointer;


void Rotate(float angle,float p[3]){
    int i;
    float  trans[3][3]={0.0};
    angle = (angle*3.141)/180;
    trans[0][0] = cos(angle);
    trans[0][1] = -sin(angle) ;
    trans[0][2] = sp[0]*(1 - cos(angle)) + sp[1]*sin(angle);
    trans[1][0] = sin(angle);
    trans[1][1] = cos(angle);
    trans[1][2] = sp[1]*(1 - cos(angle)) - sp[0]*sin(angle);
    trans[2][2] = 1;
    for(i = 0; i < 3; i++){
        ep[i] = trans[i][0]*p[0] + trans[i][1]*p[1] + trans[i][2]*p[2];
    }
}


void keyboard(unsigned char key, int x, int y){
    switch (key){
        case 'a':
            interval=(interval+1)%360;glutPostRedisplay();
            break;
            
        case 's':
            interval=(interval-1)%360;glutPostRedisplay();
            break;
            
        case 27:
            exit(0);break;
            
        default: printf("Invalid key");
            
            
    }
}

void perform(){
    sp[0]=co1[0];
    sp[1]=co1[1];
    Rotate(interval,co2);
    co2[0]=ep[0];
    co2[1]=ep[1];
    co2[2]=1;
    
    sp[0]=co1[0];
    sp[1]=co1[1];
    Rotate(interval,co3);
    temp[0]=ep[0];
    temp[1]=ep[1];
    temp[2]=1;
    
    sp[0]=co2[0];
    sp[1]=co2[1];
    Rotate(interval,temp);
    co3[0]=ep[0];
    co3[1]=ep[1];
    co3[2]=1;
    
    sp[0]=co1[0];
    sp[1]=co1[1];
    Rotate(interval,co4);
    temp[0]=ep[0];
    temp[1]=ep[1];
    temp[2]=1;
    
    sp[0]=co2[0];
    sp[1]=co2[1];
    Rotate(interval,temp);
    temp[0]=ep[0];
    temp[1]=ep[1];
    temp[2]=1;
    
    sp[0]=co3[0];
    sp[1]=co3[1];
    Rotate(interval,temp);
    co4[0]=ep[0];
    co4[1]=ep[1];
    co4[2]=1;
}


void displayit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(5);
    glBegin(GL_LINES);                              //Drawing the arm with coordinate values
    glColor3f(1,0,1);
    glVertex2f(co1[0],co1[1]);
    glVertex2f(co2[0],co2[1]);
    glColor3f(1,1,0);
    glVertex2f(co2[0],co2[1]);
    glVertex2f(co3[0],co3[1]);
    glColor3f(0,1,1);
    glVertex2f(co3[0],co3[1]);
    glVertex2f(co4[0],co4[1]);
    glEnd();
    perform();
    glFlush();
    usleep(50000);
}


int main(int argc ,char **argv)
{
    printf("Press 'a' to move anti clock and 's' to move clockwise. Direction will change after few keypresses");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Robotic arm");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250,250,-250,250);
    glutDisplayFunc(displayit);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}