#pragma once
#include "CAttribute.h"
#include <string>
#include <memory>
#include "CSTGInputManager.h"

class CCostumeBase
{
protected:
	std::string GraphFilePath;	//�摜�t�@�C���̃p�X
	double animSpeed;			//���t���[��������
	int MaxCharge;				//���ߎˌ��ɕK�v�Ȏ���(���t���[��+1)
	int Charge;					//���݂̗��ߎ���(0��Charge��MaxCharge)
	int ShotRate;				//�A�˂����t���[�����ƂɌ���
	double MaxSpeed;
	double Accelaration;

	virtual void ChargeShot(CVector position, float angle) = 0;
	virtual void WeakShot(CVector position, float angle) = 0;

public:
	CAttribute AttributeDEF;	//�����ϐ�
	double atkCF, defCF, hpCF;	//�e��{��

	CCostumeBase(std::string filepath, double animSpeed, int MaxCharge, int ShotRate, double maxSpeed, double accel);
	double ChargeRatio();
	void Shot(CVector position, float angle, double baseATK, int RpushTime);

	double getMaxSpeed();
	double getAccelaration();
};

