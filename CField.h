#pragma once
#include "CFieldParent.h"
#include "CMover.h"
#include "CVector.h"
#include "CImage.h"
#include "CImageManager.h"
#include "CAttribute.h"
#include "CAnchor.h"
#include <memory>
#include <string>
#include <vector>
#include <fstream>

class CMover_ShotBase;
class CMover_BulletBase;

class CField
{
private:
	int DamageInterval;
protected:
	CVector Position;
	CVector Size;
	COF Cofs;
	double Temperature;
	CAttribute Damage;

	std::string GID;

public:

	CField(std::string gid, CVector position, CVector size,
		COF cofs, double temperature, CAttribute damage = CAttribute(0.0), bool isWall = false);
	virtual ~CField() {};

	bool isWall;

	inline bool operator ==(std::string gid)const {
		return (gid == GID);
	}
	inline bool isInScreen() {
		const int Size = 32;
		auto p = CAnchor::getIns().getAnchoredPosition(Position);
		if (p.x + Size > 0 && p.x - Size < Constant::ScreenW && p.y + Size > 0 && p.y - Size < Constant::ScreenH)return true;
		return false;
	}
	inline std::string getGID() {
		return GID;
	}
	inline CAttribute getDamage() {
		return Damage;
	}
	inline CVector getPosition() {
		return Position;
	}
	inline CVector getSize() {
		return Size;
	}

	virtual void setFrictionForce(CMover* m);
	void attributeEffect(CMover * m) {
	};
	void attributeEffect(CMover_ShotBase* m);
	void attributeEffect(CMover_BulletBase* m);

	virtual void attributeReaction(CAttribute) {}

	inline void Move(CVector p) {
		Position = p;
	}
	virtual CField* Clone(CVector position) = 0;

	virtual bool Hit(CMover* m) { return false; }		//‹ß‚­‚É•¨‘Ì‚ª‚ ‚é‚Æ‚«‚ÉŒÄ‚Î‚ê‚éA‰½‚à‚µ‚½‚­‚È‚¯‚ê‚Î‚µ‚È‚­‚Ä‚à‚¢‚¢
	virtual void Update();
	virtual void Render()const;

	void Save(std::ofstream &fout);

	friend CFieldHolder;
};

