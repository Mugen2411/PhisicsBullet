#pragma once
#include "CField.h"

class CField_Lava :
	public CField
{
public:
	CField_Lava(std::string gid, CVector position, double temperature);
	void Update();
	void Render()const;

	void attributeReaction(CAttribute a) {
		auto f = a * CAttribute(0.0).FIRE(1.0);
		Temperature += f.Sum();
		f = a * CAttribute(0.0).AQUA(0.5).ICE(1.0);
		Temperature -= f.Sum();
		Temperature = min(1000, max(Temperature, -100));
	};

	CField* Clone(CVector position);

	void Save(std::ofstream& fout);
};

