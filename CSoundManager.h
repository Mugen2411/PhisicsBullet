#pragma once
#include "Singleton.h"
#include <memory>
#include <unordered_map>
#include "CSound.h"

class CSoundManager :
	public Singleton<CSoundManager>
{
	std::unordered_map<std::string, std::shared_ptr<CSound>> sndList;
	CSoundManager();

public:
	void unload();
	std::shared_ptr<CSound> find(std::string key);

	friend class Singleton<CSoundManager>;
};

