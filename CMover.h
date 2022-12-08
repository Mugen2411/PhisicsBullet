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
	CGameMediator* med;

	CVector Position;		//À•W
	CVector Velocity;		//‘¬“x
	CVector Acceleration;	//‰Á‘¬“x

	double Mass;			//¿—Ê
	double nowFricted;		//Œ»İó‚¯‚Ä‚¢‚é–€CŒn”
	COF Cofs;				//Šeí’è”
	double Temperature;		//‰·“x

	CVector frictionForce;	//Ã~‚ğƒVƒ~ƒ…ƒŒ[ƒg‚·‚é‚½‚ß‚Éˆê•Û‘¶‚·‚é–€C—Í
	CVector waterForce;		//“¯‚¶‚­…‚Ì’ïR
	CVector airForce;		//“¯‚¶‚­‹ó‹C’ïR

	double Size;			//•¨‘Ì‚Ì‘å‚«‚³(”¼Œa)

	int Category;			//MOVER_ID‚É‚æ‚Á‚ÄƒJƒeƒSƒŠ•ª‚¯
	int Status;				//0:¶‘¶@1:‘¼E 2:©E

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
	inline double getSize() {
		return Size;
	}
	inline int getCategory() {
		return Category;
	}
	inline void ApplyForce(CVector F) {
		Acceleration += (F / Mass);
	}	//—Í‚ğ‚©‚¯‚é
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
		auto NormA = Velocity;
		waterForce = (-NormA * Cofs.WaterResCF * waterResCF);
	}
	inline void ApplyWaterForce(CVector F) {
		ApplyForce(F * Cofs.WaterResCF);
	}
	inline void Move() {
		Velocity += Acceleration;

		//–€C‚Æ…‚Ì’ïR‚Æ‹ó‹C’ïR‚ÅÃ~‚·‚é
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

		Position += Velocity;
		Acceleration.x = 0;
		Acceleration.y = 0;
		Velocity.zero();
	}

	virtual void HitDispatch(std::shared_ptr<CMover> m) = 0;

	virtual void BaseUpdate() = 0;
	virtual bool BaseRender()const = 0;			//‰æ–Ê“à‚È‚çtrue‚ğ•Ô‚·
	virtual int Update() = 0;		//0:¶‘¶@1:‘¼E 2:©E
	virtual void Render() const = 0;
	virtual void Hit(CMover*);
	virtual void Hit(CMover_ShotBase*);
	virtual void Hit(CMover_BulletBase*);
	virtual void Hit(CMover_EnemyBase*);
	virtual void Hit(CMover_Player*);
	virtual void Dead() = 0;		//€–S(‘¼E)
	virtual void Disappear() = 0;	//Á–Å(©E)

	virtual void Damage(CAttribute shotATK, int style) = 0;			//ƒ_ƒ[ƒW‚ğó‚¯‚éˆ—
	virtual void RatioDamage(CAttribute shotATK, int style) = 0;	//Š„‡ƒ_ƒ[ƒW‚ğó‚¯‚éˆ—

	void onWall(CVector WallPosition, CVector WallSize, double WallReflectionCF);		//•Ç‚Ìã‚Éæ‚Á‚½‚©”»’è‚µA”½Ë‚·‚é
	virtual void ifonWall() {};
};

