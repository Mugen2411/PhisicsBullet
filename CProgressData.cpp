#include "CProgressData.h"

CProgressData::CProgressData() :currentStage(0), lastStage(0), maxStage(1), Money(0) {

}

void CProgressData::save()
{
}

void CProgressData::load()
{
}

void CProgressData::win(int money)
{
	Money += money;
}

void CProgressData::lose(int money)
{
	Money += money * 0.5;
}
