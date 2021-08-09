#pragma once
#include "CVector.h"
#include "Constant.h"
#include "CGameMediator.h"
#include <memory>

class CMover_ShotBase;
class CMover_EnemyBase;
class CMover_BulletBase;

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
	double SFrictionCF;		//�Î~���C�W��
	double FrictionCF;		//���C�W��
	double AirResCF;		//��C��R�W��(���͂̎󂯂₷��)
	double ReflectCF;		//�����W��
	double Temperature;		//���x

	double Size;			//���̂̑傫��(���a)

	int Category;			//MOVER_ID�ɂ���ăJ�e�S������
	int Status;				//0:�����@1:���E 2:���E
	
public:
	CMover(MOVER_ID ID, CVector position, double size, CVector velocity,
		double mass, double sfrictionCF, double frictionCF, double airresCF, double reflectCF, double temperature);
	virtual ~CMover() {};
	void setMediator(std::shared_ptr<CGameMediator>);
	CVector getPosition();
	double getSize();
	int getCategory();
	void ApplyForce(CVector F);	//�͂�������
	void ApplyFrictionForce(double FloorFrictionForce);
	void ApplyAirForce(CVector F);
	void Move();

	virtual void Dispatch(std::shared_ptr<CMover> m) = 0;
	virtual int Update() = 0;		//0:�����@1:���E 2:���E
	virtual void Render() const = 0;
	virtual void Hit(CMover*);
	virtual void Hit(CMover_ShotBase*);
	virtual void Hit(CMover_BulletBase*);
	virtual void Hit(CMover_EnemyBase*);
	virtual void Dead() = 0;		//���S(���E)
	virtual void Disappear() = 0;	//����(���E)

	void onWall(CVector WallPosition, CVector WallSize, double WallReflectionCF);		//�ǂ̏�ɏ���������肵�A���˂���
	virtual void ifonWall() {};
};

