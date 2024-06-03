#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<math.h>
#include <time.h>
#include <stdio.h>

void DrawCircle(float cx, float cy, float r, int num_segments);
void rocketRender();
void init2D();
void printSome(char *str,int x,int y);
void printSomeInt(int score,int x,int y);
void startGame();
void rocketRender();
void whiteStars();
void drawAsteroid();
int randomPositionX();
int generateRGB();
void doLaser();

int phyWidth = 700;
int phyHeight = 700;
int logWidth = 100;
int logHeight = 100;

int mouseX,mouseY;

int centerX=logWidth/2;
int centerY=logHeight/2;
int laserColor=1;
int score=0;
int timer=20;

int state=1;
int circleCounter=0;
int currentYaxis=100;
int circleColor=generateRGB();

int x=randomPositionX();

void init2D(){
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,logWidth,0,logHeight);
}
void printSome(char *str,int x,int y){

    //indicates the logical location x,y where the text is to be drawn
    glRasterPos2d(x,y);
    int n=strlen(str);
    for(int i=0;i<n;i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    }
}
void printSomeInt(int score,int x,int y){

    //indicates the logical location x,y where the text is to be drawn
    glRasterPos2d(x,y);
    char str[5];
    itoa(score,str,10);
    int n=strlen(str);
    for(int i=0;i<n;i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    }
}

void keyboard(unsigned char key, int x, int y) {
//lw dost space 8yr color el laser
    if (key == ' ') {
     if(laserColor==1){
        laserColor=2;

     }else if(laserColor==2){
     laserColor=3;
     }else if(laserColor==3){
      laserColor=1;
     }


    }

}
//lw dost f1 rg3 el state 1 y3ny el gaame wa hya sh8aala wa e3ml reset lel score wa el timer wa kolo
void specialKeyboard(int key, int x, int y)
{
if(key==GLUT_KEY_F1 && state==0){
    state=1;
    startGame();
}

glutPostRedisplay();
}
void startGame(){
currentYaxis=100;
    circleCounter=0;
    score=0;
    timer=19;

}

void passiveMouse(int x,int y){
    mouseX = x;
    mouseX=0.5+1.0*mouseX*logWidth/phyWidth;
    mouseY = phyHeight - y;
    mouseY=0.5+1.0*mouseY*logHeight/phyHeight;

}
void DrawCircle(float cx, float cy, float r, int num_segments) {

glBegin(GL_POLYGON);
for (int i = 0; i < num_segments; i++) {
float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); //get the current angle in radians
float x = r * cosf(theta);//calculate the x component
float y = r * sinf(theta);//calculate the y component
glVertex2f(x + cx, y + cy);//output vertex
}
glEnd();
}
void rocketRender(){
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    glVertex2d(mouseX-4,mouseY-2);
    glVertex2d(mouseX+4,mouseY-2);
    glVertex2d(mouseX,mouseY+4);

    glEnd();

    glColor3f(0.77,0.49,0.07);
    glBegin(GL_POLYGON);
    glVertex2d(mouseX-2,mouseY-2.5);
    glVertex2d(mouseX+2,mouseY-2.5);
    glVertex2d(mouseX+2,mouseY+2.5);
    glVertex2d(mouseX-2,mouseY+2.5);
    glEnd();
     glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    glVertex2d(mouseX-2,mouseY+2.5);
    glVertex2d(mouseX+2,mouseY+2.5);
    glVertex2d(mouseX,mouseY+4);

    glEnd();

}
void whiteStars(){

   glColor3f(1, 1, 1);
    glPointSize(1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 50; i++)
    {
        //random x and y to generate the points at
        float x = ((float)rand() / RAND_MAX) * 100.0f; // Random x coordinate between 0 and 100
        float y = ((float)rand() / RAND_MAX) * 100.0f; // Random y coordinate between 0 and 100
        glVertex2f(x, y);
    }
    glEnd();
}

//to generate random x axis
int randomPositionX(){
    //use srand to generate really random according to time
    srand(time(NULL));
int x = rand() % 93 + 4;
return x;
}

int generateRGB(){
     //srand(time(NULL));
    int circleColor=rand() % 3 + 1;
    return circleColor;
}
void Timer1(int value) {

glutTimerFunc(10, Timer1, value);

glutPostRedisplay();

}

void Timer2(int value) {

glutTimerFunc(1000, Timer2, value);
timer--;

}


void drawAsteroid(){

switch (circleColor){
    case 1: glColor3f(1,0,0);break;
     case 2: glColor3f(0,1,0);break;
      case 3: glColor3f(0,0,1);break;
  }
 //check number of asteroids generated
if(circleCounter<=25){

if (currentYaxis<1){
    if(currentYaxis==-1){
        score++;

    }

   currentYaxis=100;

  x = rand() % 93 + 4;

  circleCounter++;

circleColor=generateRGB();
  switch (circleColor){
    case 1: glColor3f(1,0,0);break;
     case 2: glColor3f(0,1,0);break;
      case 3: glColor3f(0,0,1);break;
  }

}

DrawCircle(x,currentYaxis,4,100);
//make it move down
currentYaxis-=2;

}

}

void doLaser(){
  switch (laserColor){
    case 1: glColor3f(1,0,0);break;
     case 2: glColor3f(0,1,0);break;
      case 3: glColor3f(0,0,1);break;
  }


    glBegin(GL_POLYGON);
    glVertex2d(mouseX-2,mouseY+2.5);
    glVertex2d(mouseX+2,mouseY+2.5);
    glVertex2d(mouseX+2,mouseY+100);
 glVertex2d(mouseX-2,mouseY+100);
    glEnd();

}


void display(){
glClear(GL_COLOR_BUFFER_BIT);
if(state==1){

    doLaser();
 whiteStars();
    drawAsteroid();
    rocketRender();
    if((mouseX+2>=x-4 && mouseX+2<=x+4)||(mouseX-2<=x+4&& mouseX-2>=x-4)){
    //check on the colors if matches
    //currentYaxis=-1 means the asteroids is destroyed and start new asteroid
    if(laserColor==circleColor)
        //b5leha -1 3shan a2l mn el zero wa y5leeha t5tfy wa sa3eth ael function htbtdy trsmly dayra gdida
        currentYaxis=-1;
}


printSome("Score: ",0,97);
    printSomeInt(score,8,97);
printSome("Time:",90,97);
printSomeInt(timer,97,97);
    }else{
glColor3f(0,1,0);
        glBegin(GL_POLYGON);
        glVertex2d(0,0);
        glVertex2d(0,100);
        glVertex2d(100,100);
        glVertex2d(100,0);
        glEnd();
        glColor3f(1,1,1);
        printSome("TIME'S UP",centerX-10,centerY-10);
        printSome("Your Score:     ",centerX-15,centerY-15);
        printSomeInt(score,centerX+5,centerY-15);
        printSome("Press F1 to play again!",centerX-15,centerY-20);
    }

    //law 5lst kol el circles aw el timer 5eles h8yr el state 3shan ageb el screen el tanya
if(timer<=0 || circleCounter==25){
    state=0;
}else{
    //lw laa2 yb2a zy mna staate bt3ty el game sh8ala
    state=1;
}
    glutSwapBuffers();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(phyWidth,phyHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("SpaceRocket");
    init2D();
    glutDisplayFunc(display);
glutPassiveMotionFunc(passiveMouse);
glutKeyboardFunc(keyboard);
glutSpecialFunc(specialKeyboard);
glutTimerFunc(10,Timer1,0);
glutTimerFunc(1000,Timer2,0);

    glutMainLoop();
}
