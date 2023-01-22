#pragma once

class CVector;

class Constant {
 public:
  static double kGravity;
  static double kFrame;
  static double kPerFrame;
  static double kZeroBorder;

  static double kPI;
  static double kPI2;

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
    kSceneOption
  };

  static CVector kCostumeDetailPosition;

  static int kNumEnemySpawner;
};

struct COF {
  double FrictionCF = 0.0;  //ñÄéCåWêî
  double WaterResCF = 0.0;  //êÖÇÃíÔçRåWêî
  double AirResCF = 0.0;    //ãÛãCíÔçRåWêî
  double ReflectCF = 0.0;   //îΩéÀåWêî

  COF(double frictionCF, double waterResCF, double airResCF, double reflectCF)
      : FrictionCF(frictionCF),
        WaterResCF(waterResCF),
        AirResCF(airResCF),
        ReflectCF(reflectCF) {}

  COF() : FrictionCF(0.0), WaterResCF(0.0), AirResCF(0.0), ReflectCF(0.0) {}

  COF SetFrictionCF(double frictionCF) {
    FrictionCF = frictionCF;
    return *this;
  }
  COF SetWaterResCF(double waterResCF) {
    WaterResCF = waterResCF;
    return *this;
  }
  COF SetAirResCF(double airResCF) {
    AirResCF = airResCF;
    return *this;
  }
  COF SetReflectCF(double reflectCF) {
    ReflectCF = reflectCF;
    return *this;
  }
};
