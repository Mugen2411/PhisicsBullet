#include "CFieldHolder.h"
#include "CField.h"
#include "CFieldFactory.h"
#include <queue>
#include <strstream>
#include <sstream>
#include <cassert>
#include "CSoundManager.h"
#include "CEffect_Bright.h"

CFieldHolder::CFieldHolder(std::string filepath) : filePath(filepath)
{
	if (Load() == 0) {
		dist = std::vector<std::vector<double> >(width);
		for (auto& i : dist) {
			i = std::vector<double>(height, Constant::dbl_INF);
		}
		g = std::vector<std::vector<double> >(width);
		for (auto& i : g) {
			i = std::vector<double>(height, 0.0);
		}
		diff = std::vector<std::vector<int>>(width);
		for (auto& i : diff) {
			i = std::vector<int>(height, 0);
		}
		pre = std::vector<std::vector<CVector> >(width, std::vector<CVector>(height, CVector(-1, -1)));
		return;
	}
	else {
		OutputDebugString("Stage Load Error");
		exit(1);
	}
}

CFieldHolder::~CFieldHolder()
{
}

void CFieldHolder::writefloor(CField* f, unsigned int x, unsigned int y)
{
	if (0 > x || x >= width || 0 > y || y >= height)return;
	floorlist[width * y + x].reset(f);
}

void CFieldHolder::writewall(CField* f, unsigned int x, unsigned int y)
{
	if (0 > x || x >= width || 0 > y || y >= height)return;
	walllist[width * y + x].reset(f);
}

void CFieldHolder::Update()
{
	for (auto& i : walllist) {
		i->Update();
	}
	for (auto& i : floorlist) {
		i->Update();
	}
}

void CFieldHolder::Render() const
{
	for (auto& i : walllist) {
		i->Render();
	}
	for (auto& i : floorlist) {
		i->Render();
	}
}

void CFieldHolder::convertSpawner(std::list<std::unique_ptr<CEnemySpawner>>& es, CGameMediator* med, int level, CVector& playerPos)
{
	std::string fn = filePath;
	std::vector<Spawner_Desc> sdList;
	for (int i = 0; i < 3; i++)fn.pop_back();
	fn += "spn";
	int fp = FileRead_open(fn.c_str());
	int ver;
	char buf[256];
	std::string tmp;
	for (int i = 0; i < Constant::NumEnemySpawner; i++) {
		for (auto& b : buf) {
			b = '\0';
		}
		if (FileRead_gets(buf, 256, fp) == -1)break;
		int cnt = 0;
		Spawner_Desc desc = Spawner_Desc();
		std::stringstream stream(std::string(buf, 256), std::ios::in);
		while (std::getline(stream, tmp, ',')) {
			if (tmp.empty())break;
			switch (cnt) {
			case 0:
				break;
			case 1:
				desc.GID = tmp;
				break;
			case 2:
				desc.timeToSpawn = std::stoi(tmp);
				break;
			case 3:
				desc.countOfSpawn = std::stoi(tmp);
				break;
			case 4:
				desc.spawnProbability = std::stoi(tmp);
				break;
			}
			++cnt;
		}
		sdList.emplace_back(desc);
	}
	FileRead_close(fp);
	CFieldFactory CFF;
	size_t end = walllist.size();
	for (int i = 0; i < end; i++) {
		tmp = walllist[i]->getGID();
		if (tmp[0] == 'E') {
			es.push_back(std::make_unique<CEnemySpawner>(med, walllist[i]->Position, level, sdList[std::stoi(tmp.erase(0, 1))]));
			walllist[i].reset(CFF.create(walllist[i]->Position.x, walllist[i]->Position.y, "W_Void"));
		}
		if (tmp[0] == 'P') {
			playerPos = walllist[i]->Position;
			walllist[i].reset(CFF.create(walllist[i]->Position.x, walllist[i]->Position.y, "W_Void"));
		}
	}
}

void CFieldHolder::readDefine()
{
	std::string fn = filePath;
	std::vector<Spawner_Desc> sdList;
	for (int i = 0; i < 3; i++)fn.pop_back();
	fn += "def";
	int fp = FileRead_open(fn.c_str());
	char buf[256];
	std::string tmp;
	CEffect_Bright::getIns().setBrightLevel(0);
	for (int i = 0; i < Constant::NumEnemySpawner; i++) {
		for (auto& b : buf) {
			b = '\0';
		}
		if (FileRead_gets(buf, 256, fp) == -1)break;
		std::stringstream stream(std::string(buf, 256), std::ios::in);
		switch (i) {
		case 0:
			CSoundManager::getIns().LoadBGM(buf);
			break;
		case 1:
			CEffect_Bright::getIns().setBrightLevel(atof(buf));
			break;
		}
	}
	FileRead_close(fp);
}

std::list<CVector> CFieldHolder::Find_Route(CVector start, CVector goal, CAttribute attrDEF, int distance)
{
	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = { 1, -1, 0, 0 };

	CVector s((int)((start.x) / 32), (int)((start.y) / 32));
	CVector t((int)((goal.x) / 32), (int)((goal.y) / 32));
	std::list<CVector> ret;
	using PP = std::pair<double, CVector>;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			CAttribute dmg = floorlist[index(x, y)]->getDamage() + walllist[index(x, y)]->getDamage();
			if ((dmg / attrDEF).Sum() > (dmg / CAttribute(1.0)).Sum())g[x][y] = (dmg / attrDEF).Sum() * 24;
			else g[x][y] = 0;
			dist[x][y] = Constant::dbl_INF;
			pre[x][y] = CVector(-1, -1);
		}
	}
	std::priority_queue<PP, std::vector<PP>, std::greater<PP>> pq;
	dist[(int)(start.x / 32)][(int)(start.y / 32)] = 0;
	pq.push(PP(0, s));

	while (!pq.empty()) {
		PP p = pq.top();
		pq.pop();
		if (p.second == t)break;
		double c = p.first;
		int vx = p.second.x;
		int vy = p.second.y;
		for (int i = 0; i < 4; i++) {
			int nx, ny;
			nx = vx + dx[i];
			ny = vy + dy[i];
			if (nx < 0 || ny < 0 || nx >= width || ny >= height)continue;
			if (walllist[index(nx, ny)]->isWall)continue;
			if (dist[nx][ny] <= g[nx][ny] + abs(nx - t.x) + abs(ny - t.y) + c) continue;
			dist[nx][ny] = g[nx][ny] + abs(nx - t.x) + abs(ny - t.y) + c;
			pre[nx][ny] = CVector(vx, vy);
			pq.push(PP(dist[nx][ny], CVector(nx, ny)));
		}
	}

	CVector v;
	for (; t.x != -1 || t.y != -1; t.x = pre[v.x][v.y].x, t.y = pre[v.x][v.y].y) {
		ret.push_front(t);
		v = t;
	}
	for (auto& i : ret) {
		i *= 32.0;
		i += CVector(16, 16);
	}
	*ret.begin() = start;
	ret.back() = goal;
	for (int i = 0; i < distance; i++) {
		if (ret.empty())break;
		ret.pop_back();
	}

	return ret;
}

std::vector<CVector> CFieldHolder::findTargetByDistance(CVector start, int distance)
{
	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = { 1, -1, 0, 0 };
	std::vector<CVector> ret;
	CVector s((int)((start.x) / 32), (int)((start.y) / 32));

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			diff[x][y] = 9999999;
		}
	}
	std::priority_queue<CVector> pq;
	pq.push(s);
	diff[s.x][s.y] = 0;
	while (!pq.empty()) {
		CVector now = pq.top();
		pq.pop();
		int vx = now.x;
		int vy = now.y;
		for (int i = 0; i < 4; i++) {
			int nx = vx + dx[i];
			int ny = vy + dy[i];
			if (nx < 0 || ny < 0 || nx >= width || ny >= height)continue;
			if (walllist[index(nx, ny)]->isWall)continue;
			if (diff[nx][ny] <= diff[vx][vy] + 1)continue;
			diff[nx][ny] = diff[vx][vy] + 1;
			assert(nx >= 0 && ny >= 0 && nx < width&& ny < height);
			if (diff[nx][ny] == distance)ret.push_back(CVector(nx, ny));
			pq.push(CVector(nx, ny));
		}
	}
	for (auto& i : ret) {
		i *= 32.0;
		i += CVector(16, 16);
	}
	return ret;
}

void CFieldHolder::Save()
{
	std::ofstream fout;
	fout.open(filePath);
	fout << width << "\n" << height << "\n";
	for (auto& i : floorlist) {
		i->Save(fout);
	}
	for (auto& i : walllist) {
		i->Save(fout);
	}
}

int CFieldHolder::Load() {
	std::ifstream fin(filePath);
	if (!fin)return 1;

	fin >> width;
	fin >> height;
	if (width == 0 || height == 0)return 1;

	floorlist.resize(height * width);
	walllist.resize(height * width);

	CAnchor::getIns().setScrollLimit(CVector((int)width, (int)height));

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
	return 0;
}