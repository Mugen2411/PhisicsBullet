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

class CMover
{
	friend CMoverParent;
public:
	enum MOVER_ID {
		MV_PLAYER, MV_ENEMY, MV_SHOT, MV_BULLET
	};
protected:
	std::weak_ptr<CGameMediator> med;

	CVector Position;		//���W
	CVector Velocity;		//���x
	CVector Acceleration;	//�����x

	double Mass;			//����
	double nowFricted;		//���ݎ󂯂Ă��門�C�n��
	double FrictionCF;		//���C�W��
	double AirResCF;		//��C��R�W��(���͂̎󂯂₷��)
	double WaterResCF;		//������R�W��(�����̎󂯂₷��)
	double ReflectCF;		//�����W��
	double Temperature;		//���x

	double Size;			//���̂̑傫��(���a)

	int Category;			//MOVER_ID�ɂ���ăJ�e�S������
	int Status;				//0:�����@1:���E 2:���E

public:
	CMover(MOVER_ID ID, CVector position, double size, CVector velocity,
		double mass, double frictionCF, double airresCF,double waterResCF, double reflectCF, double temperature);
	virtual ~CMover() {};
	inline void setMediator(std::shared_ptr<CGameMediator> m) {
		med = m;
	}
	inline CVector getPosition() {
		return Position;
	}
	inline void setPosition(CVector pos) {
		Position = pos;
	}
	inline double getSize() {
		return Size;
	}
	inline int getCategory() {
		return Category;
	}
	inline void ApplyForce(CVector F) {
		Acceleration += (F / Mass);
	}	//�͂�������
	inline void ApplyFrictionForce(double FloorFrictionCF) {
		nowFricted = FloorFrictionCF;
		auto NormA = Velocity;
		ApplyForce(-NormA * FrictionCF * FloorFrictionCF * Mass * Constant::Gravity * Constant::Frame);
	}
	inline void ApplyAirForce(CVector F) {
		ApplyForce(F * AirResCF);
	}
	inline void ApplyWaterForce(CVector F) {
		ApplyForce(F * WaterResCF);
	}
	inline void Move() {
		Velocity += Acceleration * Constant::perFrame;
		Position += Velocity;
		Acceleration.x = 0;
		Acceleration.y = 0;
		Velocity.zero();
	}

	virtual void HitDispatch(std::shared_ptr<CMover> m) = 0;

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

	void onWall(CVector WallPosition, CVector WallSize, double WallReflectionCF);		//�ǂ̏�ɏ���������肵�A���˂���
	virtual void ifonWall() {};
};

