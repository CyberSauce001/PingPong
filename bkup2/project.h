#ifndef PROJECT_H
#define PROJECT_H

#include <GL/freeglut.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include <X11/keysym.h>

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
    game();
    void start_settings();
    void win();
    void KeyControl();
    void KeyReset();
    void DrawField();
    void DrawScore();
};
extern game settings;

class helper{
  public:
    float x,y;
    float vx;
    float size;
    bool right, left, hold;
    helper();
    void draw();
    void move();
};
extern helper top,bott;

class reflector{
  public:
    float x,y;
    float vy;
    float size;
    bool Up, Down, hold;
    reflector();
    void draw();
    void move();
    void care();
};
extern reflector left,right;

void draw();
void Timer (int value);
void keyboard(unsigned char key, int x,int y);
void keyboardUp(unsigned char key, int x,int y);

#endif
