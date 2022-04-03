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

	static int ScrollMargin;

	static double dbl_INF;

	static double priority_field;
	static double priority_wall;
	static double priority_enemy;
	static double priority_shot;
	static double priority_bullet;
	static double priority_number;

	enum SCENE_ID {
		SCENE_MAIN, SCENE_EDITOR, SCENE_TITLE
	};
};

