#pragma once
#include "CCosutumeBase.h"
#include <string>
#include <vector>
#include <memory>

class CMover_Player;

class CCostumeFactory {
	std::vector<std::shared_ptr<CCostumeBase>> list;
	void Register(CCostumeBase* f);
	int cx;
	int cy;

public:
	CCostumeFactory();
	CCostumeBase* create(std::string);
	CCostumeBase* create(int);
	int getSize() {
		return list.size();
	}
	void getMinMaxFriction(double& min, double& max) {
		min = 9999;
		max = 0;
		for (auto& i : list) {
			if (i->constants.FrictionCF < min)min = i->constants.FrictionCF;
			if (i->constants.FrictionCF > max)max = i->constants.FrictionCF;
		}
	}
	void getMinMaxAirRes(double& min, double& max) {
		min = 9999;
		max = 0;
		for (auto& i : list) {
			if (i->constants.AirResCF < min)min = i->constants.AirResCF;
			if (i->constants.AirResCF > max)max = i->constants.AirResCF;
		}
	}
	void getMinMaxWaterRes(double& min, double& max) {
		min = 9999;
		max = 0;
		for (auto& i : list) {
			if (i->constants.WaterResCF < min)min = i->constants.WaterResCF;
			if (i->constants.WaterResCF > max)max = i->constants.WaterResCF;
		}
		min = 1.0 - max;
		max = 1.0 - min;
	}
	void getMinMaxMass(double& min, double& max) {
		min = 9999;
		max = 0;
		for (auto& i : list) {
			if (i->Mass < min)min = i->Mass;
			if (i->Mass > max)max = i->Mass;
		}
	}
	void getMinMaxVelocity(double& min, double& max) {
		min = 9999;
		max = 0;
		for (auto& i : list) {
			if (i->MaxSpeed < min)min = i->MaxSpeed;
			if (i->MaxSpeed > max)max = i->MaxSpeed;
		}
	}
	void getMinMaxAccel(double& min, double& max) {
		min = 9999;
		max = 0;
		for (auto& i : list) {
			if (i->Accelaration < min)min = i->Accelaration;
			if (i->Accelaration > max)max = i->Accelaration;
		}
	}
};