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
  void GetMoney(double value);

  void UpdateDresschangeMenu();
  void RenderDresschangeMenu() const;

  void UpdateRetireMenu();
  void RenderRetireMenu() const;

  void Update();
  void Render() const;

 protected:
  void ProcessEnemySpawner();

  std::weak_ptr<CSTGInputManager> input_;
  std::unique_ptr<CMoverParent> mover_parent_;
  std::unique_ptr<CPowerParent> power_parent_;
  std::shared_ptr<CMover_Player> player_;
  std::unique_ptr<CFieldParent> field_parent_;
  std::list<std::unique_ptr<CEnemySpawner>> enemy_spawner_;

  std::vector<int> skill_list_;
  std::vector<int> skill_level_list_;

  bool is_pause_;
  bool is_retire_;
  bool is_costume_selecter_end_;
  int pause_guage_;
  int cnt_;
  bool is_enemy_vanished;

  bool is_initialized_;

  double reserve_money_ = 0;  //‘Þ‹p‚Å“¾‚ç‚ê‚é—\’è‚Ì‹à

  CTextDrawer::Text retire_text_[2];
  CTextDrawer::Text wave_number_;
  CTextDrawer::Text wait_next_stage;

  std::unique_ptr<CCostumeBase *> costume_now_focus_;
  double min_fric_;
  double max_fric_;
  double min_air_res_;
  double max_air_res_;
  double min_water_res_;
  double max_water_res_;
  double min_mass_;
  double max_mass_;
  double min_velocity_;
  double max_velocity_;
  double min_accel_;
  double max_accel_;
  int costume_selecter_cnt_;

  int now_level_of_stage_;

  CNumberDrawer number_drawer_;
};
