#include "Constant.h"
#include "CVector.h"

double Constant::Gravity = 0.98;
double Constant::Frame = 60.0;
double Constant::perFrame = 1.0 / Constant::Frame;
double Constant::zero_border = 0.01;

double Constant::PI = 3.1415926;
double Constant::PI2 = Constant::PI * 2;

int Constant::ScreenW = 640;
int Constant::ScreenH = 480;

int Constant::ScrollMargin = 240;

double Constant::dbl_INF = 1.0e200;

int Constant::priority_decoration = -1;
int Constant::priority_field = -2;
int Constant::priority_wall = 3;
int Constant::priority_effect = 4;
int Constant::priority_bullet = 2;
int Constant::priority_enemy = 0;
int Constant::priority_shot = 1;
int Constant::priority_number = 7;

int Constant::MaxPause = 180;

CVector Constant::Costume_detail_pos = CVector(32, 128);

int Constant::NumEnemySpawner = 32;