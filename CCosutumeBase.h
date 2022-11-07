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

public:
	CAttribute AttributeDEF;	//属性耐性
	COF constants;				//各種物理定数
	const double Mass;
	const double animSpeed;			//毎フレーム足す量
	const int MaxCharge;				//溜め射撃に必要な時間(毎フレーム+1)
	const int ShotRate;				//連射を何フレームごとに撃つか
	const int StrongShotDuration;		//強攻撃を撃った後に操作不能になるフレーム数
	const double MaxSpeed;
	const double Accelaration;
	const std::string GID;

	CCostumeBase(std::string filepath, double animSpeed, int MaxCharge, int ShotRate,
		int strongshotDuration, double maxSpeed, double accel, double mass, CAttribute attrDEF, COF constants, std::string GID);
	virtual ~CCostumeBase(){}

	virtual void ChargeShot(double baseATK, CVector position, float angle) = 0;
	virtual void WeakShot(double baseATK, CVector position, float angle) = 0;

	void setPlayer(CMover_Player* p) {
		p_player = p;
	}
	void RegisterShot(std::shared_ptr<CMover_ShotBase>);

	virtual CCostumeBase* Clone() = 0;
};

