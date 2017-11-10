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
    float PSpeedX;
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
      BallSpeedX = 1.5;
      PSpeedY = 3;
      PSpeedX = 7;
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

class helper{
  public: 
    float x,y;
    float vx;
    float size;
    bool right, left, hold;
    helper(){
      vx = 0;
      x = 0;
      right = false;
      left = false;
      hold = false;
    }
    void draw(); 
    void move();
    //void care();
}top;

class reflector{
  public: 
    float x,y;
    float vy;
    float size;
    bool Up, Down, hold;
    reflector(){
      vy = 0;
      y = 0;
      Up = false;
      Down = false;
      hold = false;
    }
    void draw(); 
    void move();
    void care();
}left,right;

void game::KeyReset(){
  left.vy = 0;
  right.vy = 0;
  top.vx = 0;
}

void game::KeyControl(){
  if((left.Up)&&(!left.Down))     //left player [1st player]
    left.vy = PSpeedY;
  if((!left.Up)&&(left.Down))
    left.vy = -PSpeedY;

  if((right.Up)&&(!right.Down))  //right player [2nd player]
    right.vy = PSpeedY;
  if((!right.Up)&&(right.Down))
    right.vy = -PSpeedY;

  if((top.right)&&(!top.left))   //top player  [3rd player]
    top.vx = PSpeedX;
  if((!top.right)&&(top.left))
    top.vx = -PSpeedX;
}

void game::start_settings(){
  left.size = 200;
  right.size = 200;
  top.size = 200;
  left.x = -510;
  right.x = 510;
  top.y = 405;                   // where top is located
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

void helper::move(){
  x += vx;
  if(x < -settings.FieldSizeX + size/2){
    x = -settings.FieldSizeX + size/2;
    vx = 0;
  }
  if(x > settings.FieldSizeX - size/2){
    x = settings.FieldSizeX - size/2;
    vx = 0;
  }
}

void reflector::draw(){
  glColor3f(1,1,1);
  glVertex2f(x + settings.PThickness,y + size/2);
  glVertex2f(x + settings.PThickness,y - size/2);
  glVertex2f(x - settings.PThickness,y - size/2);
  glVertex2f(x - settings.PThickness,y + size/2);
}

void helper::draw(){
  glColor3f(1,0,0);
  glVertex2f(x + size/2, y + settings.PThickness);
  glVertex2f(x + size/2, y - settings.PThickness);
  glVertex2f(x - size/2, y - settings.PThickness);
  glVertex2f(x - size/2, y + settings.PThickness);
  glColor3f(1,1,1);
}

void ball::reflection(){
  //reflection on game field
  if((y <= -settings.FieldSizeY)||(y >= settings.FieldSizeY))
    vy = -vy;
  //reflection on 1st player [left player]]
  if((x <= left.x+settings.PThickness)&&
     (fabs(double(y - left.y)) <= left.size/2 + fabs(vy))){ 
    vx = -vx; 
    vy += left.vy;
  }
  //reflection on 2nd player [right player]]
  if((x >= right.x-settings.PThickness)&&
     (fabs(double(y - right.y)) <= right.size/2 + fabs(vy))){
    vx = -vx; 
    vy += right.vy;
  }
  //reflection on 3nd player [top player]]
  if((y >= top.y-settings.PThickness)&&
     (fabs(double(x - top.x)) <= top.size/2 + fabs(vx))){
    vy = -vy; 
    vx += top.vx;
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
    case 'q' :                // 1st player moves [left player]
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

    case 'p' :                //2nd player moves [right player]
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
    
    case 'y' :                //3rd player moves [top player]
      top.left = true;
      break;
    case 'u' :
      top.right = true;
      break;

    case 27:                  //exit game
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
    case 'y' :
      top.left = false;
      break;
    case 'u' :
      top.right = false;
      break;
  }	
}

void Timer (int value){
  settings.win();
  settings.KeyControl();
  left.move();
  right.move();
  top.move();
  ball.move();
  ball.reflection();
  left.care();
  right.care();
  settings.KeyReset();
  glutPostRedisplay();
  glutTimerFunc(settings.delay,Timer,0);
}

void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_QUADS);
  right.draw();
  left.draw();
  ball.draw();
  settings.DrawField();
  top.draw();
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


