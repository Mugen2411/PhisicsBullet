#pragma once
#include <cmath>
#include <string>

class CStatus
{
public:
	int Level;
	double ATK;
	double HP;
	double MaxHP;
	double atkCF;
	double hpCF;

	CStatus(int Level);
	CStatus(int Level, int ATK, int HP);
	CStatus(int Level, double atkCF, double hpCF);

	void Calculate();
	static int getMoneyToUpgrade(int now) {
		return 100 * std::powl(1.2, now);
	}
	CStatus Test(int TargetLevel);
	CStatus operator -(CStatus v);
};

_NODISCARD inline std::string floating_to_string(double _Val) {
	const auto _Len = static_cast<size_t>(_CSTD _scprintf("%.2f", _Val));
	std::string _Str(_Len, '\0');
	_CSTD sprintf_s(&_Str[0], _Len + 1, "%.2f", _Val);
	return _Str;
}