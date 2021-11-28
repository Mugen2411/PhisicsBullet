#pragma once
#include "CVector.h"
#include "Constant.h"
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

	CVector Position;		//座標
	CVector Velocity;		//速度
	CVector Acceleration;	//加速度

	double Mass;			//質量
	double nowFricted;		//現在受けている摩擦系数
	double FrictionCF;		//摩擦係数
	double AirResCF;		//空気抵抗係数(風力の受けやすさ)
	double ReflectCF;		//反発係数
	double Temperature;		//温度

	double Size;			//物体の大きさ(半径)

	int Category;			//MOVER_IDによってカテゴリ分け
	int Status;				//0:生存　1:他殺 2:自殺
	
public:
	CMover(MOVER_ID ID, CVector position, double size, CVector velocity,
		double mass, double frictionCF, double airresCF, double reflectCF, double temperature);
	virtual ~CMover() {};
	void setMediator(std::shared_ptr<CGameMediator>);
	CVector getPosition();
	double getSize();
	int getCategory();
	void ApplyForce(CVector F);	//力をかける
	void ApplyFrictionForce(double FloorFrictionForce);
	void ApplyAirForce(CVector F);
	void Move();

	virtual void Dispatch(std::shared_ptr<CMover> m) = 0;
	virtual int Update() = 0;		//0:生存　1:他殺 2:自殺
	virtual void Render() const = 0;
	virtual void Hit(CMover*);
	virtual void Hit(CMover_ShotBase*);
	virtual void Hit(CMover_BulletBase*);
	virtual void Hit(CMover_EnemyBase*);
	virtual void Hit(CMover_Player*);
	virtual void Dead() = 0;		//死亡(他殺)
	virtual void Disappear() = 0;	//消滅(自殺)

	void onWall(CVector WallPosition, CVector WallSize, double WallReflectionCF);		//壁の上に乗ったか判定し、反射する
	virtual void ifonWall() {};
};

