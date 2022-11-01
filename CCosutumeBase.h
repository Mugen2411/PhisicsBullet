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
	CMover_Player* p_player;	//�v���C���[�ւ̃|�C���^
	std::string GraphFilePath;	//�摜�t�@�C���̃p�X
	double animSpeed;			//���t���[��������
	int MaxCharge;				//���ߎˌ��ɕK�v�Ȏ���(���t���[��+1)
	int ShotRate;				//�A�˂����t���[�����ƂɌ���
	int StrongShotDuration;		//���U������������ɑ���s�\�ɂȂ�t���[����
	double MaxSpeed;
	double Accelaration;

public:
	CAttribute AttributeDEF;	//�����ϐ�
	double atkCF, defCF, hpCF;	//�e��{��

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

