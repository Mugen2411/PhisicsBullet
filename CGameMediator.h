#pragma once
#include <list>
#include <memory>
#include <vector>

#include "CAttribute.h"
#include "CControllerFactory.h"
#include "CNumberDrawer.h"
#include "CTextDrawer.h"
#include "CVector.h"
#include "Scene_Abstract.h"

class CMoverParent;
class CFieldParent;
class CPowerParent;
class CPower;
class CMover_Player;
class CMover;
class CCostumeBase;
class CEnemySpawner;

class CGameMediator : public Scene_Abstract {
 protected:
  std::weak_ptr<CSTGInputManager> input;
  std::unique_ptr<CMoverParent> moverParent;
  std::unique_ptr<CPowerParent> powerParent;
  std::shared_ptr<CMover_Player> player;
  std::unique_ptr<CFieldParent> fieldParent;
  std::list<std::unique_ptr<CEnemySpawner>> enemySpawner;

  std::vector<int> skillList;
  std::vector<int> skillLevelList;

  bool isPause;
  bool isRetire;
  bool isCostumeSelecterEnd;
  int pauseGuage;
  int cnt;

  bool isInitialized;

  int reserveMoney = 0;  //‘Þ‹p‚Å“¾‚ç‚ê‚é—\’è‚Ì‹à

  CTextDrawer::Text retireText[2];
  CTextDrawer::Text waveNumber;

  std::unique_ptr<CCostumeBase *> costumeNowFocusOn;
  double minFric;
  double maxFric;
  double minAirRes;
  double maxAirRes;
  double minWaterRes;
  double maxWaterRes;
  double minMass;
  double maxMass;
  double minVelocity;
  double maxVelocity;
  double minAccel;
  double maxAccel;
  int costumeSelecterCNT;

  int nowLevelOfStage;

  CNumberDrawer CND;

  void ProcessEnemySpawner();

 public:
  CGameMediator(SceneManager *ScnMng);
  virtual ~CGameMediator();

  virtual void CreateParts();

  void RegisterMover(std::shared_ptr<CMover> m);
  void RegisterPower(std::shared_ptr<CPower> p);
  void ApplyForceToMover(CMover *);
  bool HitToMover(CMover *);
  CVector GetPlayerPosition();
  std::list<CVector> GetRoute(CVector start, CVector goal, CAttribute attrDEF,
                              int distance);
  std::vector<CVector> GetTargetByDistance(CVector start, int distance);
  std::weak_ptr<CMover> GetNearestMover(int ID, CVector p);
  void getMoney(int value);

  void UpdateDresschangeMenu();
  void RenderDresschangeMenu() const;

  void UpdateRetireMenu();
  void RenderRetireMenu() const;

  void Update();
  void Render() const;
};
