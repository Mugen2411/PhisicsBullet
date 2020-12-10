#include "CControllerFactory.h"

CControllerFactory::CControllerFactory()
{
	current = std::make_shared<CKeyInputManager>();
}

std::shared_ptr<CSTGInputManager> CControllerFactory::getController()
{
	return current;
}
