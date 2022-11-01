#pragma once
#include "CAttribute.h"
#include "CStatus.h"
#include <string>
#include <memory>
#include "CMover_ShotBase.h"
#include "CSTGInputManager.h"

class CMover_Player;

class CCostumeBase
{
protected:
	CMover_Player* p_player;	//プレイヤーへのポインタ
	std::string GraphFilePath;	//画像ファイルのパス
	double animSpeed;			//毎フレーム足す量
	int MaxCharge;				//溜め射撃に必要な時間(毎フレーム+1)
	int ShotRate;				//連射を何フレームごとに撃つか
	int StrongShotDuration;		//強攻撃を撃った後に操作不能になるフレーム数
	double MaxSpeed;
	double Accelaration;

public:
	CAttribute AttributeDEF;	//属性耐性
	double atkCF, defCF, hpCF;	//各種倍率

	CCostumeBase(CMover_Player* player, std::string filepath, double animSpeed, int MaxCharge, int ShotRate,
		int strongshotDuration, double maxSpeed, double accel, CAttribute attrDEF);

	virtual void ChargeShot(double baseATK, CVector position, float angle) = 0;
	virtual void WeakShot(double baseATK, CVector position, float angle) = 0;

	inline double getMaxSpeed() {
		return MaxSpeed;
	}
	inline double getAccelaration() {
		return Accelaration;
	}
	inline double getAnimSpeed() {
		return animSpeed;
	}
	inline int getShotRate() {
		return ShotRate;
	}
	inline int getMaxCharge() {
		return MaxCharge;
	}
	inline int getStrongShotDuration() {
		return StrongShotDuration;
	}

	void RegisterShot(std::shared_ptr<CMover_ShotBase>);

	virtual CCostumeBase* Clone(CMover_Player* player) = 0;
};

