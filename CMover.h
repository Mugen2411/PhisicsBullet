#pragma once
#include "CVector.h"
#include "Constant.h"
#include "CGameMediator.h"
#include <memory>

class CMover
{
protected:
	std::shared_ptr<CGameMediator> med;

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

	int Status;				//0:�����@1:���E 2:���E
	
public:
	CMover(CVector position, double size, CVector velocity,
		double mass, double sfrictionCF, double frictionCF, double airresCF, double reflectCF, double temperature);
	virtual ~CMover() {};
	void setMediator(std::shared_ptr<CGameMediator>);
	CVector getPosition();
	double getSize();
	void ApplyForce(CVector F);	//�͂�������
	void ApplyFrictionForce(double FloorFrictionForce);
	void ApplyAirForce(CVector F);
	void Move();

	virtual int Update() = 0;		//0:�����@1:���E 2:���E
	virtual void Render() const = 0;
	virtual void Dead() = 0;		//���S(���E)
	virtual void Disappear() = 0;	//����(���E)

	void onWall(CVector WallPosition, CVector WallSize, double WallReflectionCF);		//�ǂ̏�ɏ���������肵�A���˂���
	virtual void ifonWall() {};
};

