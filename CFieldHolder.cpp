#include "CFieldHolder.h"
#include "CField.h"
#include "CFieldFactory.h"

CFieldHolder::CFieldHolder(unsigned int w, unsigned int h) :width(w), height(h)
{
	CFieldFactory CFF = CFieldFactory();
	fieldlist.resize(h * w);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			this->write(CFF.create(x, y, "Field_IceFloor", std::vector<double>(1, 0.0)), x, y);
		}
	}
}

std::shared_ptr<CField> CFieldHolder::getField(unsigned int x, unsigned int y)
{
	return fieldlist[width * y + x];
}

void CFieldHolder::write(std::shared_ptr<CField> f, unsigned int x, unsigned int y)
{
	fieldlist[width * y + x] = f;
}

unsigned int CFieldHolder::getHeight()
{
	return height;
}

unsigned int CFieldHolder::getWidth()
{
	return width;
}

void CFieldHolder::Update()
{
	std::for_each(fieldlist.begin(), fieldlist.end(), [](std::shared_ptr<CField> i) {
		i->Update();
	});
}

void CFieldHolder::Render() const
{
	std::for_each(fieldlist.begin(), fieldlist.end(), [](std::shared_ptr<CField> i) {
		i->Render();
	});
}
