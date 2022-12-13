#pragma once

class CVector;

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

	static int priority_decoration;
	static int priority_field;
	static int priority_wall;
	static int priority_effect;
	static int priority_enemy;
	static int priority_shot;
	static int priority_bullet;
	static int priority_number;
	static int priority_marker;

	static int MaxPause;

	enum SCENE_ID {
		SCENE_MAIN, SCENE_EDITOR, SCENE_TITLE, SCENE_QUIT, 
		SCENE_GAMEOVER, SCENE_STAGECLEAR, SCENE_UPGRADE, SCENE_GAMECLEAR, SCENE_OPTION
	};

	static CVector Costume_detail_pos;

	static int NumEnemySpawner;
};

struct COF {
	double FrictionCF = 0.0;	//ñÄéCåWêî
	double WaterResCF = 0.0;	//êÖÇÃíÔçRåWêî
	double AirResCF = 0.0;		//ãÛãCíÔçRåWêî
	double ReflectCF = 0.0;		//îΩéÀåWêî

	COF(double frictionCF, double waterResCF, double airResCF, double reflectCF)
	:FrictionCF(frictionCF), WaterResCF(waterResCF), AirResCF(airResCF), ReflectCF(reflectCF) {
	}

	COF() :FrictionCF(0.0), WaterResCF(0.0), AirResCF(0.0), ReflectCF(0.0) {

	}

	COF setFrictionCF(double frictionCF) {
		FrictionCF = frictionCF;
		return *this;
	}
	COF setWaterResCF(double waterResCF) {
		WaterResCF = waterResCF;
		return *this;
	}
	COF setAirResCF(double airResCF) {
		AirResCF = airResCF;
		return *this;
	}
	COF setReflectCF(double reflectCF) {
		ReflectCF = reflectCF;
		return *this;
	}
};
