#include "Constant.h"

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