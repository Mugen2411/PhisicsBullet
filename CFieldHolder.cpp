#include "CFieldHolder.h"
#include "CField.h"
#include "CFieldFactory.h"

CFieldHolder::CFieldHolder(std::string filepath) :filePath(filepath)
{
	if (Load() == 0)return;
	else OutputDebugString("Stage Load Error");
}

CFieldHolder::~CFieldHolder()
{
	Save();
}

std::shared_ptr<CField> CFieldHolder::getField(unsigned int x, unsigned int y)
{
	return fieldlist[width * y + x];
}

void CFieldHolder::write(std::shared_ptr<CField> f, unsigned int x, unsigned int y)
{
	fieldlist[width * y + x] = f;
}

int CFieldHolder::getHeight()
{
	return height;
}

int CFieldHolder::getWidth()
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

void CFieldHolder::Save()
{
	std::ofstream fout;
	fout.open(filePath);
	fout << width << "\n" << height << "\n";
	std::for_each(fieldlist.begin(), fieldlist.end(), [&](std::shared_ptr<CField> i) {
		i->Save(fout);
	});
}

int CFieldHolder::Load() {
	std::ifstream fin(filePath);
	if (!fin)return 1;
	fin >> width;
	fin >> height;
	fieldlist.resize(height * width);
	CFieldFactory CFF;
	std::string buf;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			fin >> buf;
			this->write(CFF.create(x, y, buf), x, y);
		}
	}
}