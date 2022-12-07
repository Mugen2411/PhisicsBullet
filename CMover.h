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

	CVector Position;		//座標
	CVector Velocity;		//速度
	CVector Acceleration;	//加速度

	double Mass;			//質量
	double nowFricted;		//現在受けている摩擦系数
	COF Cofs;				//各種定数
	double Temperature;		//温度

	double Size;			//物体の大きさ(半径)

	int Category;			//MOVER_IDによってカテゴリ分け
	int Status;				//0:生存　1:他殺 2:自殺

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
	}	//力をかける
	inline void ApplyFrictionForce(double FloorFrictionCF) {
		nowFricted = FloorFrictionCF;
		auto NormA = Velocity;
		ApplyForce(-NormA * Cofs.FrictionCF * FloorFrictionCF * Mass * Constant::Gravity * Constant::Frame);
	}
	inline void ApplyAirRegistance() {
		auto NormA = Velocity;
		ApplyForce(-NormA * Cofs.AirResCF * Mass * Constant::Frame);
	}
	inline void ApplyAirForce(CVector F) {
		ApplyForce(F * Cofs.AirResCF);
	}
	inline void ApplyWaterRegistance(double waterResCF) {
		auto NormA = Velocity;
		ApplyForce(-NormA * Cofs.WaterResCF * waterResCF * Mass * Constant::Frame);
	}
	inline void ApplyWaterForce(CVector F) {
		ApplyForce(F * Cofs.WaterResCF);
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
	virtual bool BaseRender()const = 0;			//画面内ならtrueを返す
	virtual int Update() = 0;		//0:生存　1:他殺 2:自殺
	virtual void Render() const = 0;
	virtual void Hit(CMover*);
	virtual void Hit(CMover_ShotBase*);
	virtual void Hit(CMover_BulletBase*);
	virtual void Hit(CMover_EnemyBase*);
	virtual void Hit(CMover_Player*);
	virtual void Dead() = 0;		//死亡(他殺)
	virtual void Disappear() = 0;	//消滅(自殺)

	virtual void Damage(CAttribute shotATK, int style) = 0;			//ダメージを受ける処理
	virtual void RatioDamage(CAttribute shotATK, int style) = 0;	//割合ダメージを受ける処理

	void onWall(CVector WallPosition, CVector WallSize, double WallReflectionCF);		//壁の上に乗ったか判定し、反射する
	virtual void ifonWall() {};
};

