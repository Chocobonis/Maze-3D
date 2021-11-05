#include "SDL.h"
#include <stdio.h>
#include<GL/glut.h>
#include<iostream>
#include<unistd.h>
/* g++ gl.cpp -o gl -lGL -lGLU -lglut */

float px = 1,pz = 1;
int   pa = 0;

int map[8][8] = {
			{1,1,1,1,1,5,1,1},
			{1,0,0,0,0,0,0,1},
			{1,0,0,4,0,0,0,1},
			{1,0,3,1,3,0,0,1},
			{1,0,0,4,0,0,0,1},
			{1,0,0,0,0,0,0,1},
			{1,0,0,0,2,0,0,1},
			{1,1,1,1,1,1,1,1},
		 };

void iniGL();
void screen();
void standf();
void keybd(unsigned char key, int x, int y);

int main(int argc, char **argv){
 glutInit(&argc,argv);
 glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
 glutInitWindowSize(640,480);
 glutInitWindowPosition(64,64);
 glutCreateWindow("test file");
 glClearDepth(1.0f);
 glDepthFunc(GL_LEQUAL);
 iniGL();
 glutDisplayFunc(screen);
 glutIdleFunc(standf);
 glutKeyboardFunc(keybd);
 glutMainLoop();
 return 0;
}

void iniGL(){
 glEnable(GL_DEPTH_TEST);
 glClearColor(0.0f,0.0f,0.0f,0.0f);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(60,1,0.1,100);
}

void standf(){
  usleep(33);
  glutPostRedisplay();
}

void keybd(unsigned char key, int x, int y){
int tmpx,tmpz;
 switch(key){
  case '.':glutDestroyWindow(1);break;
  case 'w':
        tmpx = roundf(px+cos((pa*3.14159)/180)*0.1);
        tmpz = roundf(pz-sin((pa*3.14159)/180)*0.1);
  	if(map[tmpx][tmpz]<1){
  	 px=px+cos((pa*3.14159)/180)*0.1;pz=pz-sin((pa*3.14159)/180)*0.1;
  	}
  break;
  case 'a':pa++;break;
  case 's':
  	tmpx = roundf(px+cos((pa*3.14159)/180)*-0.1);
        tmpz = roundf(pz-sin((pa*3.14159)/180)*-0.1);
  	if(map[tmpx][tmpz]<1){
  	 px=px+cos((pa*3.14159)/180)*-0.1;pz=pz-sin((pa*3.14159)/180)*-0.1;
  	}
  break;
  case 'd':pa--;break;
 }
}

void screen(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(px,0,pz, px+cos((pa*3.14159)/180)*3,0,pz-sin((pa*3.14159)/180)*3, 0,1,0);
  
  for(int x = 0; x < 8; x++){
   for(int z = 0; z < 8; z++){
    switch(map[x][z]){
     case 1:glPushMatrix();glColor3f(1,0,0);glTranslatef(x,0,z);glutSolidCube(1);glPopMatrix();break;
     case 2:glPushMatrix();glColor3f(0,1,0);glTranslatef(x,0,z);glutSolidCube(1);glPopMatrix();break;
     case 3:glPushMatrix();glColor3f(0,0,1);glTranslatef(x,0,z);glutSolidCube(1);glPopMatrix();break;
     case 4:glPushMatrix();glColor3f(1,0,1);glTranslatef(x,0,z);glutSolidCube(1);glPopMatrix();break;
     case 5:glPushMatrix();glColor3f(1,1,0);glTranslatef(x,0,z);glutSolidCube(1);glPopMatrix();break;
    }
   }
  }
    
  glFlush();
  glutSwapBuffers();
}

