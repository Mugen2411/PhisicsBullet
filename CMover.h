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

	CVector Position;		//À•W
	CVector Velocity;		//‘¬“x
	CVector Acceleration;	//‰Á‘¬“x

	double Mass;			//¿—Ê
	double SFrictionCF;		//Ã~–€CŒW”
	double FrictionCF;		//–€CŒW”
	double AirResCF;		//‹ó‹C’ïRŒW”(•——Í‚Ìó‚¯‚â‚·‚³)
	double ReflectCF;		//”½”­ŒW”
	double Temperature;		//‰·“x

	double Size;			//•¨‘Ì‚Ì‘å‚«‚³(”¼Œa)

	int Category;			//MOVER_ID‚É‚æ‚Á‚ÄƒJƒeƒSƒŠ•ª‚¯
	int Status;				//0:¶‘¶@1:‘¼E 2:©E
	
public:
	CMover(MOVER_ID ID, CVector position, double size, CVector velocity,
		double mass, double sfrictionCF, double frictionCF, double airresCF, double reflectCF, double temperature);
	virtual ~CMover() {};
	void setMediator(std::shared_ptr<CGameMediator>);
	CVector getPosition();
	double getSize();
	int getCategory();
	void ApplyForce(CVector F);	//—Í‚ğ‚©‚¯‚é
	void ApplyFrictionForce(double FloorFrictionForce);
	void ApplyAirForce(CVector F);
	void Move();

	virtual void Dispatch(std::shared_ptr<CMover> m) = 0;
	virtual int Update() = 0;		//0:¶‘¶@1:‘¼E 2:©E
	virtual void Render() const = 0;
	virtual void Hit(CMover*);
	virtual void Hit(CMover_ShotBase*);
	virtual void Hit(CMover_BulletBase*);
	virtual void Hit(CMover_EnemyBase*);
	virtual void Dead() = 0;		//€–S(‘¼E)
	virtual void Disappear() = 0;	//Á–Å(©E)

	void onWall(CVector WallPosition, CVector WallSize, double WallReflectionCF);		//•Ç‚Ìã‚Éæ‚Á‚½‚©”»’è‚µA”½Ë‚·‚é
	virtual void ifonWall() {};
};

