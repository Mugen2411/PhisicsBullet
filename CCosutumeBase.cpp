#include "CCosutumeBase.h"
#include "CImageManager.h"

CCostumeBase::CCostumeBase(std::string filepath, double animSpeed, int MaxCharge, int ShotRate, double maxSpeed, double accel)
:animSpeed(animSpeed), MaxCharge(MaxCharge), ShotRate(ShotRate), MaxSpeed(maxSpeed), Accelaration(accel){
	GraphFilePath = filepath;
	CImageManager::getIns().set("player_komuk", std::make_shared<CImage>(GraphFilePath, 16, 4, 4, 32, 32));
}

double CCostumeBase::getMaxSpeed()
{
	return MaxSpeed;
}

double CCostumeBase::getAccelaration()
{
	return Accelaration;
}

double CCostumeBase::getAnimSpeed()
{
	return animSpeed;
}

int CCostumeBase::getShotRate()
{
	return ShotRate;
}

int CCostumeBase::getMaxCharge()
{
	return MaxCharge;
}
