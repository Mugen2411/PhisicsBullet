#pragma once
#include "CAttribute.h"
#include <string>
#include <memory>
#include "CSTGInputManager.h"

class CCostumeBase
{
protected:
	std::string GraphFilePath;	//画像ファイルのパス
	double animSpeed;			//毎フレーム足す量
	int MaxCharge;				//溜め射撃に必要な時間(毎フレーム+1)
	int Charge;					//現在の溜め時間(0≦Charge≦MaxCharge)
	int ShotRate;				//連射を何フレームごとに撃つか
	double MaxSpeed;
	double Accelaration;

	virtual void ChargeShot(CVector position, float angle) = 0;
	virtual void WeakShot(CVector position, float angle) = 0;

public:
	CAttribute AttributeDEF;	//属性耐性
	double atkCF, defCF, hpCF;	//各種倍率

	CCostumeBase(std::string filepath, double animSpeed, int MaxCharge, int ShotRate, double maxSpeed, double accel);
	double ChargeRatio();
	void Shot(CVector position, float angle, double baseATK, int RpushTime);

	double getMaxSpeed();
	double getAccelaration();
};

