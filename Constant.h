#pragma once
class Constant
{
public:
	static double Gravity;
	static double Frame;
	static double perFrame;
	static double zero_border;

	static double PI;
	static double PI2;

	static int ScreenW;
	static int ScreenH;

	enum SCENE_ID {
		SCENE_MAIN, SCENE_EDITOR, SCENE_TITLE
	};
};

