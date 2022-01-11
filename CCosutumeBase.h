#pragma once
#include "CAttribute.h"
#include "CStatus.h"
#include <string>
#include <memory>
#include "CMover_ShotBase.h"
#include "CSTGInputManager.h"

class CCostumeBase
{
protected:
	std::string GraphFilePath;	//画像ファイルのパス
	double animSpeed;			//毎フレーム足す量
	int MaxCharge;				//溜め射撃に必要な時間(毎フレーム+1)
	int ShotRate;				//連射を何フレームごとに撃つか
	double MaxSpeed;
	double Accelaration;

public:
	CAttribute AttributeDEF;	//属性耐性
	double atkCF, defCF, hpCF;	//各種倍率

	CCostumeBase(std::string filepath, double animSpeed, int MaxCharge, int ShotRate, double maxSpeed, double accel, CAttribute attrDEF);

	virtual std::shared_ptr<CMover_ShotBase> ChargeShot(double baseATK, CVector position, float angle) = 0;
	virtual std::shared_ptr<CMover_ShotBase> WeakShot(double baseATK, CVector position, float angle) = 0;

	double getMaxSpeed();
	double getAccelaration();

	double getAnimSpeed();
	int getShotRate();
	int getMaxCharge();
};

