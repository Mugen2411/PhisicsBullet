#pragma once
#include "Scene_Abstract.h"
#include "CMediator.h"
#include "CFieldHolder.h"
#include "CControllerFactory.h"
#include <memory>
#include <DxLib.h>

class CMapEditor :
    public Scene_Abstract, public CMediator
{
protected:
    std::weak_ptr<CSTGInputManager> input;
    void CreateParts();
public:
    CMapEditor(SceneManager *ScnMng);
    void Update();
    void Render()const;
    void PartsChanged(CParts* p);
};


int GetFileName(char *filename, int bufsize, bool isOpen);  //true:Open false:Save