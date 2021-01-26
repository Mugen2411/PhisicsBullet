#pragma once
#include "Scene_Abstract.h"
#include "CMediator.h"
#include "CFieldParent.h"
#include <memory>

class CMapEditor :
    public Scene_Abstract, public CMediator
{
protected:
    void CreateParts();
public:
    CMapEditor(SceneManager *ScnMng);
    void Update();
    void Render()const;
    void PartsChanged(CParts* p);
};

