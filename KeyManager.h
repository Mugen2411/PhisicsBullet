#pragma once
#include "Singleton.h"
class KeyManager :
	public Singleton<KeyManager>
{
protected:
	char buf[256];
	int key[256];
	int keycode[8];
public:
	enum KEY_CODE {
		UP,
		DOWN,
		RIGHT,
		LEFT,
		ENTER,
		CANCEL,
		OTHER,
		OTHER2
	};
	KeyManager();
	~KeyManager();

	void update();
	int get(int ID);
	int Get(KEY_CODE ID);
};

