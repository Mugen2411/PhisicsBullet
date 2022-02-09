#pragma once
#include "Scene_Abstract.h"
#include "CMediator.h"
#include "CFieldHolder.h"
#include "CFieldFactory.h"
#include "CControllerFactory.h"
#include <memory>
#include <DxLib.h>

class CMapEditor :
    public Scene_Abstract, public CMediator
{
protected:
    std::weak_ptr<CSTGInputManager> input;
    void CreateParts();
    std::shared_ptr<CFieldHolder> field;
    int cur = 0;
    std::string currentMapchip;
    CFieldFactory CFF;

public:
    CMapEditor(SceneManager *ScnMng);
    ~CMapEditor();
    void Update();
    void Render()const;
    void PartsChanged(CParts* p);
};


int GetFileName(char *filename, int bufsize, bool isOpen);  //true:Open false:Save