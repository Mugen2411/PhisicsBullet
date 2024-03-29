#pragma once
#include "Data/CDataNode.h"

class CVector;

class Constant {
 public:
  static float kGravity;
  static float kFrame;
  static float kPerFrame;
  static float kZeroBorder;
  static float kDynamicBorder;
  static int kExpoBorder;

  static float kPI;
  static float kPI2;

  static int kScreenW;
  static int kScreenH;

  static int kScrollMargin;

  static double kDoubleInfinity;

  static int kPriorityDecoration;
  static int kPriorityField;
  static int kPriorityWall;
  static int kPriorityEffect;
  static int kPriorityEnemy;
  static int kPriorityShot;
  static int kPriorityBullet;
  static int kPriorityNumber;
  static int kPriorityMarker;
  static int kPriorityUI;
  static int kPriorityCurtain;
  static int kPriorityCoin;

  static double kBulletDeleteVelocity;

  static int kMaxPause;

  enum SceneID {
    kSceneMain,
    kSceneEditor,
    kSceneTitle,
    kSceneQuit,
    kSceneGameover,
    kSceneStageclear,
    kSceneUpgrade,
    kSceneGameclear,
    kSceneOption,
    kSceneGallery
  };

  static CVector kCostumeDetailPosition;

  static int kNumEnemySpawner;
};

struct COF {
  double FrictionCF = 0.0;  //���C�W��
  double WaterResCF = 0.0;  //���̒�R�W��
  double AirResCF = 0.0;    //��C��R�W��
  double ReflectCF = 0.0;   //���ˌW��
  double WindCF = 0.0;      //�����ϐ�

  COF(double frictionCF, double waterResCF, double airResCF, double reflectCF, double windCF)
      : FrictionCF(frictionCF),
        WaterResCF(waterResCF),
        AirResCF(airResCF),
        ReflectCF(reflectCF),
        WindCF(windCF) {}

  COF()
      : FrictionCF(0.0),
        WaterResCF(0.0),
        AirResCF(0.0),
        ReflectCF(0.0),
        WindCF(0.0) {}

  COF& SetFrictionCF(double frictionCF) {
    FrictionCF = frictionCF;
    return *this;
  }
  COF& SetWaterResCF(double waterResCF) {
    WaterResCF = waterResCF;
    return *this;
  }
  COF& SetAirResCF(double airResCF) {
    AirResCF = airResCF;
    return *this;
  }
  COF& SetReflectCF(double reflectCF) {
    ReflectCF = reflectCF;
    return *this;
  }
  COF& SetWindCF(double windCF) { WindCF = windCF;
    return *this;
  }
  void Load(const CDataNode* c) {
    FrictionCF = c->GetChild("frc")->GetDouble();
    WaterResCF = c->GetChild("wtr")->GetDouble();
    AirResCF = c->GetChild("air")->GetDouble();
    ReflectCF = c->GetChild("ref")->GetDouble();
    WindCF = c->GetChild("wnd")->GetDouble();
  }
};
