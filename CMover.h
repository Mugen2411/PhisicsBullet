#pragma once
#include "CVector.h"
#include "Constant.h"
#include "CGameMediator.h"
#include <memory>

class CMover
{
protected:
	std::shared_ptr<CGameMediator> med;

	CVector Position;		//座標
	CVector Velocity;		//速度
	CVector Acceleration;	//加速度

	double Mass;			//質量
	double SFrictionCF;		//静止摩擦係数
	double FrictionCF;		//摩擦係数
	double AirResCF;		//空気抵抗係数(風力の受けやすさ)
	double ReflectCF;		//反発係数
	double Temperature;		//温度

	double Size;			//物体の大きさ(半径)

	int Status;				//0:生存　1:他殺 2:自殺
	
public:
	CMover(CVector position, double size, CVector velocity,
		double mass, double sfrictionCF, double frictionCF, double airresCF, double reflectCF, double temperature);
	virtual ~CMover() {};
	void setMediator(std::shared_ptr<CGameMediator>);
	CVector getPosition();
	double getSize();
	void ApplyForce(CVector F);	//力をかける
	void ApplyFrictionForce(double FloorFrictionForce);
	void ApplyAirForce(CVector F);
	void Move();

	virtual int Update() = 0;		//0:生存　1:他殺 2:自殺
	virtual void Render() const = 0;
	virtual void Dead() = 0;		//死亡(他殺)
	virtual void Disappear() = 0;	//消滅(自殺)

	void onWall(CVector WallPosition, CVector WallSize, double WallReflectionCF);		//壁の上に乗ったか判定し、反射する
	virtual void ifonWall() {};
};

