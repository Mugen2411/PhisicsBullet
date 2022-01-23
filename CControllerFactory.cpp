#include "CControllerFactory.h"

CControllerFactory::CControllerFactory()
{
	current = std::make_shared<CKeyInputManager>();
}

std::weak_ptr<CSTGInputManager> CControllerFactory::getController()
{
	return current;
}

void CControllerFactory::update()
{
	current->update();
}
