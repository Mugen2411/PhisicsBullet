#include "CFieldHolder.h"
#include "CField.h"
#include "CFieldFactory.h"
#include <queue>

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

std::vector<CVector> CFieldHolder::Find_Route(CVector start, CVector goal, CAttribute attrDEF)
{
	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = { 1, -1, 0, 0 };

	CVector s((int)((start.x) / 32), (int)((start.y) / 32));
	CVector t((int)((goal.x) / 32), (int)((goal.y) / 32));
	std::vector<CVector> ret;
	using PP = std::pair<double, CVector>;
	std::vector<std::vector<double>> g, dist;
	dist = std::vector<std::vector<double> >(width, std::vector<double>(height, Constant::dbl_INF));
	g = std::vector<std::vector<double> >(width, std::vector<double>(height, 0.0));
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			g[x][y] = (s - CVector(x, y)).getLength2() + (floorlist[index(x, y)]->getDamage() / attrDEF).Sum() * 12;
		}
	}
	std::vector<std::vector<CVector>> pre = std::vector<std::vector<CVector> >(width, std::vector<CVector>(height, CVector(-1, -1)));
	std::priority_queue<PP, std::vector<PP>, std::greater<PP>> pq;
	dist[(int)(start.x / 32)][(int)(start.y / 32)] = 0;
	pq.push(PP(0, s));

	while (!pq.empty()) {
		PP p = pq.top();
		pq.pop();
		double c = p.first;
		int vx = p.second.x;
		int vy = p.second.y;
		for (int i = 0; i < 4; i++) {
			int nx, ny;
			nx = vx + dx[i];
			ny = vy + dy[i];
			if (nx < 0 || ny < 0 || nx >= width || ny >= height)continue;
			if (walllist[index(nx, ny)]->isWall)continue;
			if (dist[nx][ny] <= g[nx][ny] + (nx - t.x) * (nx - t.x) + (ny - t.y) * (ny - t.y) + c) continue;
			dist[nx][ny] = g[nx][ny] + (nx - t.x) * (nx - t.x) + (ny - t.y) * (ny - t.y) + c;
			pre[nx][ny] = CVector(vx, vy);
			pq.push(PP(dist[nx][ny], CVector(nx, ny)));
		}
	}

	CVector v;
	for (; t.x != -1, t.y != -1; t.x = pre[v.x][v.y].x, t.y = pre[v.x][v.y].y) {
		ret.push_back(t);
		v = t;
	}
	for (auto& i : ret) {
		i *= 32.0;
		i += CVector(16, 16);
	}
	*ret.begin() = goal;
	ret.back() = start;
	//std::reverse(ret.begin(), ret.end());

	return ret;
}

int CFieldHolder::index(int x, int y) {
	return y * width + x;
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