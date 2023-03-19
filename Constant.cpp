#include "Constant.h"

#include "CVector.h"

float Constant::kGravity = 0.98f;
float Constant::kFrame = 60.0f;
float Constant::kPerFrame = 1.0f / Constant::kFrame;
float Constant::kZeroBorder = 0.01f;
float Constant::kDynamicBorder = 1.0f;

float Constant::kPI = 3.1415926f;
float Constant::kPI2 = Constant::kPI * 2;

int Constant::kScreenW = 640;
int Constant::kScreenH = 480;

int Constant::kScrollMargin = 240;

double Constant::kDoubleInfinity = 1.0e200;

int Constant::kPriorityDecoration = -10;
int Constant::kPriorityField = -20;
int Constant::kPriorityWall = 30;
int Constant::kPriorityEffect = 40;
int Constant::kPriorityBullet = 20;
int Constant::kPriorityEnemy = 00;
int Constant::kPriorityShot = 10;
int Constant::kPriorityNumber = 90;
int Constant::kPriorityMarker = 100;
int Constant::kPriorityUI = 80;
int Constant::kPriorityCurtain = 200;
int Constant::kPriorityCoin = -5;

double Constant::kBulletDeleteVelocity = 0.8;

int Constant::kMaxPause = 120;

CVector Constant::kCostumeDetailPosition = CVector(16, 128);

int Constant::kNumEnemySpawner = 32;