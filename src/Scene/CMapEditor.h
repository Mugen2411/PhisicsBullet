#pragma once
#include <DxLib.h>

#include <memory>

#include "Input/CControllerFactory.h"
#include "Field/CFieldFactory.h"
#include "Field/CFieldHolder.h"
#include "CMediator.h"
#include "Scene_Abstract.h"

class CMapEditor : public Scene_Abstract, public CMediator {
 public:
  CMapEditor(SceneManager *ScnMng);
  ~CMapEditor();
  void Update();
  void Render() const;
  void PartsChanged(CParts *p);

 protected:
  void CreateParts();
  CVector current_select_;  //�I�𒆂̃`�b�v�̍��W
  std::weak_ptr<CSTGInputManager> input_;
  std::shared_ptr<CFieldHolder> field_;
  int cur_ = 0;
  std::string current_mapchip_;
  CFieldFactory field_factory_;

  int state_;    // 0:�}�b�v,1:�p���b�g
  int category_;  // 0:Floor,1:Wall
};

int GetFileName(char *filename, int bufsize,
                bool isOpen);  // true:Open false:Save