#include "CCosutumeBase.h"
#include "CImageManager.h"

CCostumeBase::CCostumeBase(std::string filepath, double animSpeed, int MaxCharge, int ShotRate, double maxSpeed, double accel)
:animSpeed(animSpeed), MaxCharge(MaxCharge), Charge(0), ShotRate(ShotRate), MaxSpeed(maxSpeed), Accelaration(accel){
	GraphFilePath = filepath;
	CImageManager::getIns().set("player_komuk", std::make_shared<CImage>(GraphFilePath, 16, 4, 4, 32, 32));
}

double CCostumeBase::ChargeRatio()
{
	return (double)Charge / MaxCharge;
}

void CCostumeBase::Shot(CVector position, float angle, double baseATK, int RpushTime)
{
	if (RpushTime == 0) {
		Charge++;
		Charge %= MaxCharge;
		return;
	}
	if (Charge == MaxCharge - 1) {
		ChargeShot(position, angle);
		Charge = 0;
		return;
	}
	if (RpushTime % ShotRate == 1)WeakShot(position, angle);
}

double CCostumeBase::getMaxSpeed()
{
	return MaxSpeed;
}

double CCostumeBase::getAccelaration()
{
	return Accelaration;
}
