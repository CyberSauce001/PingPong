//Project by Alex and Erick
//CMPS 3640
#include <GL/freeglut.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include <X11/keysym.h>

using std::cout;

class game{
  public:
    int OrthoWid;
    int OrthoHei;
    int WinWid;
    int WinHei;
    int winXPos;
    int winYPos;
    float FieldSizeX;
    float FieldSizeY;
    int delay;
    float PThickness;
    float BallSize;
    float BorderT;
    float MLineT;
    int ScoreL;
    int ScoreR;
    float TextPosX;
    float TextPosY;
    float BallSpeedX;
    float PSpeedY;
    int id;
    game(){
      WinWid = 700;
      WinHei = 700;
      OrthoWid = 700;
      OrthoHei = 700;	
      winXPos = 100;
      winYPos = 100;
      delay = 1;
      PThickness = 10;
      BallSize = 5;
      FieldSizeX = 600;
      FieldSizeY = 400;
      BorderT = 10;
      MLineT = 5;
      ScoreL = 0;
      ScoreR = 0;
      TextPosX = 0;
      TextPosY = FieldSizeY + 10;
      BallSpeedX = 0.5;
      PSpeedY = 1;
    }
    void start_settings();
    void win();
    void KeyControl();
    void KeyReset();
    void DrawField();
    void DrawScore();
}settings;

class ball{
  public:
    float x;
    float y;
    float vx;
    float vy;
    void move();
    void reflection();
    void draw();
}ball;

class reflector{
  public: 
    float x,y;
    float vy;
    float size;
    bool Up, Down, Left, Right, hold;
    reflector(){
      vy = 0;
      y = 0;
      Up = false;
      Down = false;
      Left = false;
      Right = false;
      hold = false;
    }
    void draw(); 
    void move();
    void care();
}left,right,l,r;

void game::KeyReset(){
  left.vy = 0;
  right.vy = 0;
  l.vx = 0;
  r.vx = 0;
}

void game::KeyControl(){
  if((left.Up)&&(!left.Down))
    left.vy = PSpeedY;
  if((!left.Up)&&(left.Down))
    left.vy = -PSpeedY;

  if((right.Up)&&(!right.Down))
    right.vy = PSpeedY;
  if((!right.Up)&&(right.Down))
    right.vy = -PSpeedY;

  if((l.Left)&&(!l.Right))
    l.vx = PSpeedX;
  if((!r.Left)&&(r.Right))
    l.vx = -PSpeedX;

  if((r.Left)&&(!r.Right))
    r.vx = PSpeedX;
  if((!r.Left)&&(r.Right))
    r.vx = -PSpeedX;

}

void game::start_settings(){
  left.size = 200;
  right.size = 200;
  left.x = -510;
  right.x = 510;
  while(ball.vx == 0)
    ball.vx = (rand()%3 - 1)*BallSpeedX;
  ball.vy = 0;
  ball.x = 0;
  ball.y = 0;
}

void game::win(){
  if((ScoreL == 8)||(ScoreR == 8)){
    glutTimerFunc(2000,exit,0);
    settings.delay = 10000;
  }
  if(ball.x < left.x + PThickness - BallSpeedX){
    //start_settings();
    right.hold = true;	
    ScoreR++;
  }
  if(ball.x > right.x - PThickness + BallSpeedX){
    //start_settings();
    left.hold = true;		
    ScoreL++;
  }
}

void reflector::care(){
  if(hold){
    ball.vx = 0;
    if(x < 0)
      ball.x = x + 2*settings.PThickness;
    if(x > 0)
      ball.x = x - 2*settings.PThickness;
    ball.vy = vy;
    ball.y = y;
  }
}

void game::DrawField(){
  glColor3f(1,1,1);
  glVertex2f(-FieldSizeX - BorderT,-FieldSizeY - BorderT);
  glVertex2f(FieldSizeX + BorderT,-FieldSizeY - BorderT);
  glVertex2f(FieldSizeX + BorderT,-FieldSizeY);
  glVertex2f(-FieldSizeX - BorderT,-FieldSizeY);

  glVertex2f(-FieldSizeX - BorderT,FieldSizeY + BorderT);
  glVertex2f(FieldSizeX + BorderT,FieldSizeY + BorderT);
  glVertex2f(FieldSizeX + BorderT,FieldSizeY);
  glVertex2f(-FieldSizeX - BorderT,FieldSizeY);

  glVertex2f(-FieldSizeX - BorderT,-FieldSizeY - BorderT);
  glVertex2f(-FieldSizeX,-FieldSizeY - BorderT);
  glVertex2f(-FieldSizeX,FieldSizeY + BorderT);
  glVertex2f(-FieldSizeX - BorderT, FieldSizeY + BorderT);

  glVertex2f(FieldSizeX,-FieldSizeY - BorderT);
  glVertex2f(FieldSizeX + BorderT,-FieldSizeY - BorderT);
  glVertex2f(FieldSizeX + BorderT,FieldSizeY + BorderT);
  glVertex2f(FieldSizeX, FieldSizeY + BorderT);

  for(float i = -FieldSizeY; i <= FieldSizeY; i += 4*MLineT){
    glVertex2f(-MLineT,i + MLineT);
    glVertex2f(MLineT,i + MLineT);
    glVertex2f(MLineT,i - MLineT);
    glVertex2f(-MLineT,i - MLineT);
  }
}

void game::DrawScore(){
  glRasterPos2f(TextPosX - 50, TextPosY + 20);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + ScoreL);
  glRasterPos2f(TextPosX + 30, TextPosY + 20);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + ScoreR);
}

void reflector::move(){
  y += vy;
  if(y < -settings.FieldSizeY + size/2){
    y = -settings.FieldSizeY + size/2;
    vy = 0;
  }
  if(y > settings.FieldSizeY - size/2){
    y = settings.FieldSizeY - size/2;
    vy = 0;
  }
}
//For this we will need to create an opposite to move side to side instead
//of up and down for l and r
void reflector::draw(){
  glColor3f(1,1,1);
  glVertex2f(x + settings.PThickness,y + size/2);
  glVertex2f(x + settings.PThickness,y - size/2);
  glVertex2f(x - settings.PThickness,y - size/2);
  glVertex2f(x - settings.PThickness,y + size/2);
}

void ball::reflection(){
  if((y <= -settings.FieldSizeY)||(y >= settings.FieldSizeY))
    vy = -vy;
  if((x <= left.x+settings.PThickness)&&
     (fabs(double(y - left.y)) <= left.size/2 + fabs(vy))){
    vx = -vx; 
    vy += left.vy;
  }
  if((x >= right.x-settings.PThickness)&&
     (fabs(double(y - right.y)) <= right.size/2 + fabs(vy))){
    vx = -vx; 
    vy += right.vy;
  }
}

void ball::draw(){
  glVertex2f(x+settings.BallSize,y+settings.BallSize);
  glVertex2f(x+settings.BallSize,y-settings.BallSize);
  glVertex2f(x-settings.BallSize,y-settings.BallSize);
  glVertex2f(x-settings.BallSize,y+settings.BallSize);
}

void ball::move(){
  x += vx;
  y += vy;
}

void keyboard(unsigned char key, int x,int y){
  switch(key){
    case 't': 
	l.Left = true;
	break;
    case 'y':
	l.Right = true;
    case 'v':
	r.Left = true;
	break;
    case 'b':
	r.Right = true;
	break;
    case 'q' :
      left.Up = true;
      break;
    case 'a' :
      left.Down = true;
      break;
    case 'z' :
      if(left.hold){
        left.hold = false;
        ball.vx = settings.BallSpeedX;
      }
      break;
    case 'p' :
      right.Up = true;
      break;
    case 'l' :
      right.Down = true;
      break;
    case 'm' :
      if(right.hold){
        right.hold = false;
        ball.vx = -settings.BallSpeedX;
        break;
      }
    case 27:
     glutDestroyWindow(settings.id);
     exit (0);
     break;
  }	
}

void keyboardUp(unsigned char key, int x,int y){
  switch(key){
    case 'q' :
      left.Up = false;
      break;
    case 'a' :
      left.Down = false;
      break;
    case 'p' :
      right.Up = false;
      break;
    case 'l' :
      right.Down = false;
      break;
    case 't':
      l.Left = false;
      break;
    case 'y':
      l.Right = false;
      break;
    case 'v':
      r.Left = false;
      break;
    case 'b':
      r.Right = false;
      break;
  }	
}

void Timer (int value){
  settings.win();
  settings.KeyControl();
  left.move();
  l.move();
  right.move();
  r.move();
  ball.move();
  ball.reflection();
  left.care();
  l.care();
  right.care();
  r.care();
  settings.KeyReset();
  glutPostRedisplay();
  glutTimerFunc(settings.delay,Timer,0);
}

void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_QUADS);
  right.draw();
  r.draw();
  left.draw();
  l.draw();
  ball.draw();
  settings.DrawField();
  glEnd();
  settings.DrawScore();
  glutSwapBuffers();
}

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


