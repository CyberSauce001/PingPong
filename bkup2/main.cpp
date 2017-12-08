#include <GL/freeglut.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include <X11/keysym.h>
#include "project.h"

game settings;
helper top,bott;
reflector left,right;

int main (int argc, char ** argv){

  srand(time(NULL));
  settings.start_settings();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
  glutInitWindowSize(settings.WinWid, settings.WinHei);
  glutInitWindowPosition(settings.winXPos, settings.winYPos);
  settings.id = glutCreateWindow("Ping Pong");
  glutDisplayFunc(draw);
  glutTimerFunc(settings.delay,Timer,0);

  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);

  glClearColor(0,0,0,1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-settings.OrthoWid,settings.OrthoWid,-settings.OrthoHei,settings.OrthoHei);
  glutMainLoop();
  return(0);
}
