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

std::shared_ptr<CField> CFieldHolder::getFloor(unsigned int x, unsigned int y)
{
	return floorlist[width * y + x];
}

std::shared_ptr<CField> CFieldHolder::getWall(unsigned int x, unsigned int y)
{
	return walllist[width * y + x];
}

void CFieldHolder::writefloor(std::shared_ptr<CField> f, unsigned int x, unsigned int y)
{
	if (0 > x || x > width || 0 > y || y > height)return;
	floorlist[width * y + x] = f;
}

void CFieldHolder::writewall(std::shared_ptr<CField> f, unsigned int x, unsigned int y)
{
	if (0 > x || x > width || 0 > y || y > height)return;
	walllist[width * y + x] = f;
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
	std::for_each(walllist.begin(), walllist.end(), [](std::shared_ptr<CField> i) {
		i->Update();
	});
	std::for_each(floorlist.begin(), floorlist.end(), [](std::shared_ptr<CField> i) {
		i->Update();
	});
}

void CFieldHolder::Render() const
{
	std::for_each(walllist.begin(), walllist.end(), [](std::shared_ptr<CField> i) {
		i->Render();
	});
	std::for_each(floorlist.begin(), floorlist.end(), [](std::shared_ptr<CField> i) {
		i->Render();
	});
}

void CFieldHolder::Save()
{
	std::ofstream fout;
	fout.open(filePath);
	fout << width << "\n" << height << "\n";
	std::for_each(floorlist.begin(), floorlist.end(), [&](std::shared_ptr<CField> i) {
		i->Save(fout);
	});
	std::for_each(walllist.begin(), walllist.end(), [&](std::shared_ptr<CField> i) {
		i->Save(fout);
	});
}

int CFieldHolder::Load() {
	std::ifstream fin(filePath);
	if (!fin)return 1;

	fin >> width;
	fin >> height;

	floorlist.resize(height * width);
	walllist.resize(height * width);

	CFieldFactory CFF;
	std::string buf;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			fin >> buf;
			this->writefloor(CFF.create(x, y, buf), x, y);
		}
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			fin >> buf;
			this->writewall(CFF.create(x, y, buf), x, y);
		}
	}
}