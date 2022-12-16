#pragma once
#include "CVector.h"
#include "Constant.h"
#include "CStatus.h"
#include "CAttribute.h"
#include "CGameMediator.h"
#include <memory>

class CMover_ShotBase;
class CMover_EnemyBase;
class CMover_BulletBase;
class CMover_Player;
class CField;

class CMover
{
	friend CMoverParent;
public:
	static enum MOVER_ID {
		MV_PLAYER, MV_ENEMY, MV_SHOT, MV_BULLET
	};
	static enum STATUS {
		ALIVE = 0, DEAD, VANISHED
	};
protected:
	CGameMediator* med;

	CVector Position;		//���W
	CVector Velocity;		//���x
	CVector Acceleration;	//�����x

	double Mass;			//����
	double nowFricted;		//���ݎ󂯂Ă��門�C�n��
	double nowWatered;		//���������̒�R
	COF Cofs;				//�e��萔
	double Temperature;		//���x

	CVector frictionForce;	//�Î~���V�~�����[�g���邽�߂Ɉꎞ�ۑ����門�C��
	CVector waterForce;		//���������̒�R
	CVector airForce;		//��������C��R

	double Size;			//���̂̑傫��(���a)

	int Category;			//MOVER_ID�ɂ���ăJ�e�S������
	int Status;				//0:�����@1:���E 2:���E

	int isLockedAxis;		//(X�Œ�)(Y�Œ�)

public:
	CMover(MOVER_ID ID, CVector position, double size, CVector velocity,
		double mass, COF cofs, double temperature);
	virtual ~CMover() {};
	inline void setMediator(CGameMediator* m) {
		med = m;
	}
	inline CVector getPosition() {
		return Position;
	}
	inline void setPosition(CVector pos) {
		Position = pos;
	}
	inline CVector getVelocity() {
		return Velocity;
	}
	inline CVector getAcceleration() {
		return Acceleration;
	}
	inline double getSize() {
		return Size;
	}
	inline int getCategory() {
		return Category;
	}
	inline void setStatus(int status) {
		Status = status;
	}
	inline int getStatus() {
		return Status;
	}
	inline void ApplyForce(CVector F) {
		Acceleration += (F / Mass);
	}	//�͂�������
	inline void ApplyFrictionForce(double FloorFrictionCF) {
		nowFricted = FloorFrictionCF;
		auto NormA = Velocity;
		double cons = Cofs.FrictionCF * FloorFrictionCF * Constant::Gravity;
		frictionForce = (NormA * -cons);
	}
	inline void ApplyAirRegistance() {
		auto NormA = Velocity;
		airForce = (-NormA * Cofs.AirResCF);
	}
	inline void ApplyAirForce(CVector F) {
		ApplyForce(F * Cofs.AirResCF);
	}
	inline void ApplyWaterRegistance(double waterResCF) {
		nowWatered = waterResCF;
		auto NormA = Velocity;
		waterForce = (-NormA * Cofs.WaterResCF * waterResCF);
	}
	inline void ApplyWaterForce(CVector F) {
		ApplyForce(F * Cofs.WaterResCF);
	}
	inline void Move() {

		Velocity += Acceleration;

		//���C�Ɛ��̒�R�Ƌ�C��R�ŐÎ~����
		CVector frictedVelocity = Velocity + frictionForce;
		if (frictedVelocity.dot(Velocity) < 0)frictedVelocity = CVector(0.0, 0.0);

		CVector wateredVelocity = Velocity + waterForce;
		if (wateredVelocity.dot(Velocity) < 0)wateredVelocity = CVector(0.0, 0.0);

		CVector airedVelocity = Velocity + airForce;
		if (airedVelocity.dot(Velocity) < 0)airedVelocity = CVector(0.0, 0.0);

		if (frictedVelocity.getLength2() < Constant::zero_border ||
			wateredVelocity.getLength2() < Constant::zero_border ||
			airedVelocity.getLength2() < Constant::zero_border)
		{
			Velocity = CVector(0.0, 0.0);
		}
		else {
			Velocity += frictionForce;
			Velocity += waterForce;
			Velocity += airForce;
		}

		if (Velocity.getLength2() > 32 * 32) {
			Velocity = Velocity.getNorm() * 32;
		}

		if (!(isLockedAxis & 1)) {
			Position.x += Velocity.x;
		}
		if (!((isLockedAxis >> 1) & 1)) {
			Position.y += Velocity.y;
		}
		isLockedAxis = 0;
		Acceleration.x = 0;
		Acceleration.y = 0;
		frictionForce = CVector(0.0, 0.0);
		waterForce = CVector(0.0, 0.0);
		airForce = CVector(0.0, 0.0);
		Velocity.zero();
	}

	void resetPower() {
		isLockedAxis = 0;
		Acceleration.x = 0;
		Acceleration.y = 0;
		frictionForce = CVector(0.0, 0.0);
		waterForce = CVector(0.0, 0.0);
		airForce = CVector(0.0, 0.0);
		Velocity.zero();
	}

	virtual void HitDispatch(std::shared_ptr<CMover> m) = 0;
	virtual void FieldDispatch(CField *f) = 0;

	virtual void BaseUpdate() = 0;
	virtual bool BaseRender()const = 0;			//��ʓ��Ȃ�true��Ԃ�
	virtual int Update() = 0;		//0:�����@1:���E 2:���E
	virtual void Render() const = 0;
	virtual void Hit(CMover*);
	virtual void Hit(CMover_ShotBase*);
	virtual void Hit(CMover_BulletBase*);
	virtual void Hit(CMover_EnemyBase*);
	virtual void Hit(CMover_Player*);
	virtual void Dead() = 0;		//���S(���E)
	virtual void Disappear() = 0;	//����(���E)

	virtual void Damage(CAttribute shotATK, int style) = 0;			//�_���[�W���󂯂鏈��
	virtual void RatioDamage(CAttribute shotATK, int style) = 0;	//�����_���[�W���󂯂鏈��
	virtual CAttribute TestDamage(CAttribute shotATK) = 0;	//�_���[�W���e�X�g����

	bool onWall(CField* f, double WallReflectionCF);		//�ǂ̏�ɏ���������肵�A���˂���
	virtual void ifonWall() {};
};

