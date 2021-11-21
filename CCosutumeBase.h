#pragma once
#include "CAttribute.h"
#include <string>
#include <memory>
#include "CSTGInputManager.h"

class CCostumeBase
{
protected:
	std::string GraphFilePath;	//æt@CÌpX
	double animSpeed;			//t[«·Ê
	int MaxCharge;				//­ßËÉKvÈÔ(t[+1)
	int Charge;					//»ÝÌ­ßÔ(0ChargeMaxCharge)
	int ShotRate;				//AËð½t[²ÆÉÂ©
	double MaxSpeed;
	double Accelaration;

	virtual void ChargeShot(CVector position, float angle) = 0;
	virtual void WeakShot(CVector position, float angle) = 0;

public:
	CAttribute AttributeDEF;	//®«Ï«
	double atkCF, defCF, hpCF;	//eí{¦

	CCostumeBase(std::string filepath, double animSpeed, int MaxCharge, int ShotRate, double maxSpeed, double accel);
	double ChargeRatio();
	void Shot(CVector position, float angle, double baseATK, int RpushTime);

	double getMaxSpeed();
	double getAccelaration();
};

