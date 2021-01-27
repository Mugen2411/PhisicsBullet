#include "CFieldHolder.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Wall.h"
#include "CField.h"

CFieldHolder::CFieldHolder(int w, int h)
{
	fieldlist.resize(h);
	for (int i = 0; i < h; i++) {
		fieldlist[i].resize(w);
	}
}

std::shared_ptr<CField> CFieldHolder::getField(int x, int y)
{
	return fieldlist[y][x];
}

void CFieldHolder::write(std::shared_ptr<CField> f, int x, int y)
{
	fieldlist[y][x] = f;
}

int CFieldHolder::getHeight()
{
	return fieldlist.size();
}

int CFieldHolder::getWidth()
{
	return fieldlist[0].size();
}

void CFieldHolder::Update()
{
	std::for_each(fieldlist.begin(), fieldlist.end(), [](std::vector<std::shared_ptr<CField>> y) {
		std::for_each(y.begin(), y.end(), [](std::shared_ptr<CField> x) {
			x->Update();
			});
		});
}

void CFieldHolder::Render() const
{
	std::for_each(fieldlist.begin(), fieldlist.end(), [](std::vector<std::shared_ptr<CField>> y) {
		std::for_each(y.begin(), y.end(), [](std::shared_ptr<CField> x) {
			x->Render();
			});
		});
}
