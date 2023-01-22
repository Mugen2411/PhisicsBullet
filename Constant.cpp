#include "Constant.h"

#include "CVector.h"

double Constant::kGravity = 0.98;
double Constant::kFrame = 60.0;
double Constant::kPerFrame = 1.0 / Constant::kFrame;
double Constant::kZeroBorder = 0.01;

double Constant::kPI = 3.1415926;
double Constant::kPI2 = Constant::kPI * 2;

int Constant::kScreenW = 640;
int Constant::kScreenH = 480;

int Constant::kScrollMargin = 240;

double Constant::kDoubleInfinity = 1.0e200;

int Constant::kPriorityDecoration = -1;
int Constant::kPriorityField = -2;
int Constant::kPriorityWall = 3;
int Constant::kPriorityEffect = 4;
int Constant::kPriorityBullet = 2;
int Constant::kPriorityEnemy = 0;
int Constant::kPriorityShot = 1;
int Constant::kPriorityNumber = 7;
int Constant::kPriorityMarker = 10;

double Constant::kBulletDeleteVelocity = 0.8;

int Constant::kMaxPause = 120;

CVector Constant::kCostumeDetailPosition = CVector(16, 128);

int Constant::kNumEnemySpawner = 32;