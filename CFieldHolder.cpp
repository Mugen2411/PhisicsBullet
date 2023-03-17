#include "CFieldHolder.h"

#include <cassert>
#include <queue>
#include <sstream>
#include <strstream>

#include "CDataLoader.h"
#include "CEffect_Bright.h"
#include "CField.h"
#include "CFieldFactory.h"
#include "CSoundManager.h"

CFieldHolder::CFieldHolder(std::string filepath) : filepath_(filepath) {
  if (Load() == 0) {
    dist_ = std::vector<std::vector<double>>(width_);
    for (auto& i : dist_) {
      i = std::vector<double>(height_, Constant::kDoubleInfinity);
    }
    g_ = std::vector<std::vector<double>>(width_);
    for (auto& i : g_) {
      i = std::vector<double>(height_, 0.0);
    }
    diff_ = std::vector<std::vector<int>>(width_);
    for (auto& i : diff_) {
      i = std::vector<int>(height_, 0);
    }
    pre_ = std::vector<std::vector<CVector>>(
        width_, std::vector<CVector>(height_, CVector(-1, -1)));
    return;
  } else {
    OutputDebugString("Stage Load Error");
    exit(1);
  }
}

CFieldHolder::~CFieldHolder() {}

void CFieldHolder::WriteFloor(CField* f, CVector pos) {
  if (0 > pos.x_ || pos.x_ >= width_ || 0 > pos.y_ || pos.y_ >= height_) return;
  floor_list_[(uint64_t)(width_ * pos.y_ + pos.x_)].reset(f);
}

void CFieldHolder::WriteWall(CField* f, CVector pos) {
  if (0 > pos.x_ || pos.x_ >= width_ || 0 > pos.y_ || pos.y_ >= height_) return;
  wall_list_[(uint64_t)(width_ * pos.y_ + pos.x_)].reset(f);
}

void CFieldHolder::Update() {
  for (auto& i : wall_list_) {
    i->Update();
  }
  for (auto& i : floor_list_) {
    i->Update();
  }
}

void CFieldHolder::Render() const {
  for (auto& i : wall_list_) {
    i->Render();
  }
  for (auto& i : floor_list_) {
    i->Render();
  }
}

void CFieldHolder::readStageData(std::list<std::unique_ptr<CEnemySpawner>>& es,
                                 CGameMediator* med, int level,
                                 CVector& playerPos) {
  std::string fn = filepath_;
  for (int i = 0; i < 3; i++) fn.pop_back();
  fn += "spn";
  CDataLoader::GetIns().Load("stage", fn);
  auto c = CDataLoader::GetIns().Get("stage");
  if (c == nullptr) {
    MessageBox(NULL, "stage data not found", "CFieldHolder", MB_OK);
    abort();
  }
  // read stage def
  auto d = c->GetChild("def");
  auto bgmPath = d->GetChild("bgm")->GetString();
  CSoundManager::GetIns().LoadBGM("media/sound/bgm/" + bgmPath);
  auto br = d->GetChild("bright");
  if (br != nullptr) {
    CEffect_Bright::GetIns().SetBrightLevel(br->GetDouble());
  } else
    CEffect_Bright::GetIns().SetBrightLevel(0);
  std::string tmp;

  // convert enemy spawner
  std::vector<SpawnerDesc> sdList;
  d = c->GetChild("spawn");
  int i = 0;
  while (1) {
    auto e = d->GetChild(std::to_string(i));
    if (e == nullptr) break;
    SpawnerDesc tmpSD;
    tmpSD.gid = e->GetChild("gid")->GetString();
    tmpSD.count_of_spawn_ = e->GetChild("amount")->GetInt();
    tmpSD.time_to_spawn_ = e->GetChild("time")->GetInt();
    auto f = e->GetChild("prob");
    if (f != nullptr)
      tmpSD.spawn_probability_ = f->GetInt();
    else
      tmpSD.spawn_probability_ = 100;

    sdList.push_back(tmpSD);
    i++;
  }
  CFieldFactory field_factory_;
  size_t end = wall_list_.size();
  for (int i = 0; i < end; i++) {
    tmp = wall_list_[i]->GetGID();
    if (tmp[0] == 'E') {
      es.push_back(
          std::make_unique<CEnemySpawner>(med, wall_list_[i]->position_, level,
                                          sdList[std::stoi(tmp.erase(0, 1))]));
      wall_list_[i].reset(
          field_factory_.create(wall_list_[i]->position_, "W_Void"));
    }
    if (tmp[0] == 'P') {
      playerPos = wall_list_[i]->position_;
      wall_list_[i].reset(
          field_factory_.create(wall_list_[i]->position_, "W_Void"));
    }
  }
}

std::list<CVector> CFieldHolder::FindRoute(CVector start, CVector goal,
                                           CAttribute attrDEF, int distance) {
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  if (start.x_ < 0 || start.y_ < 0 || start.x_ > width_ * 32 ||
      start.y_ > height_ * 32)
    return std::list<CVector>();

  CVector s((int)((start.x_) / 32), (int)((start.y_) / 32));
  CVector t((int)((goal.x_) / 32), (int)((goal.y_) / 32));
  std::list<CVector> ret;
  using PP = std::pair<double, CVector>;

  for (uint32_t x = 0; x < width_; x++) {
    for (uint32_t y = 0; y < height_; y++) {
      CAttribute dmg = floor_list_[Index(x, y)]->GetDamage() +
                       wall_list_[Index(x, y)]->GetDamage();
      if ((dmg / attrDEF).Sum() > (dmg / CAttribute(1.0)).Sum())
        g_[x][y] = (dmg / attrDEF).Sum() * 24;
      else
        g_[x][y] = 0;
      dist_[x][y] = Constant::kDoubleInfinity;
      pre_[x][y] = CVector(-1, -1);
    }
  }
  std::priority_queue<PP, std::vector<PP>, std::greater<PP>> pq;
  dist_[(int)(start.x_ / 32)][(int)(start.y_ / 32)] = 0;
  pq.push(PP(0, s));

  while (!pq.empty()) {
    PP p = pq.top();
    pq.pop();
    if (p.second == t) break;
    double c = p.first;
    int vx = (int)p.second.x_;
    int vy = (int)p.second.y_;
    for (int i = 0; i < 4; i++) {
      uint32_t nx, ny;
      nx = vx + dx[i];
      ny = vy + dy[i];
      if (nx < 0 || ny < 0 || nx >= width_ || ny >= height_) continue;
      if (wall_list_[Index(nx, ny)]->is_wall_) continue;
      if (dist_[nx][ny] <= g_[nx][ny] + abs(nx - t.x_) + abs(ny - t.y_) + c)
        continue;
      dist_[nx][ny] = g_[nx][ny] + abs(nx - t.x_) + abs(ny - t.y_) + c;
      pre_[nx][ny] = CVector(vx, vy);
      pq.push(PP(dist_[nx][ny], CVector((int)nx, (int)ny)));
    }
  }

  CVector v;
  for (; t.x_ != -1 || t.y_ != -1;
       t.x_ = pre_[(uint32_t)v.x_][(uint32_t)v.y_].x_,
       t.y_ = pre_[(uint32_t)v.x_][(uint32_t)v.y_].y_) {
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
    if (ret.empty()) break;
    ret.pop_back();
  }

  return ret;
}

std::vector<CVector> CFieldHolder::FindTargetByDistance(CVector start,
                                                        int distance) {
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  std::vector<CVector> ret;
  CVector s((int)((start.x_) / 32), (int)((start.y_) / 32));

  for (uint32_t x = 0; x < width_; x++) {
    for (uint32_t y = 0; y < height_; y++) {
      diff_[x][y] = 9999999;
    }
  }
  std::priority_queue<CVector> pq;
  pq.push(s);
  diff_[(uint32_t)s.x_][(uint32_t)s.y_] = 0;
  while (!pq.empty()) {
    CVector now = pq.top();
    pq.pop();
    int vx = (int)now.x_;
    int vy = (int)now.y_;
    for (int i = 0; i < 4; i++) {
      int nx = vx + dx[i];
      int ny = vy + dy[i];
      if (nx < 0 || ny < 0 || nx >= (int)width_ || ny >= (int)height_) continue;
      if (wall_list_[Index(nx, ny)]->is_wall_) continue;
      if (diff_[nx][ny] <= diff_[vx][vy] + 1) continue;
      diff_[nx][ny] = diff_[vx][vy] + 1;
      if (diff_[nx][ny] == distance) ret.push_back(CVector(nx, ny));
      pq.push(CVector(nx, ny));
    }
  }
  for (auto& i : ret) {
    i *= 32.0;
    i += CVector(16, 16);
  }
  return ret;
}

void CFieldHolder::Save() {
  std::ofstream fout;
  fout.open(filepath_);
  fout << width_ << "\n" << height_ << "\n";
  for (auto& i : floor_list_) {
    i->Save(fout);
  }
  for (auto& i : wall_list_) {
    i->Save(fout);
  }
}

int CFieldHolder::Load() {
  std::ifstream fin(filepath_);
  if (!fin) return 1;

  fin >> width_;
  fin >> height_;
  if (width_ == 0 || height_ == 0) return 1;

  floor_list_.resize(height_ * width_);
  wall_list_.resize(height_ * width_);

  CAnchor::GetIns().SetScrollLimit(CVector((int)width_, (int)height_));

  CFieldFactory field_factory_;
  std::vector<std::string> bufF(floor_list_.size());
  std::vector<std::string> bufW(floor_list_.size());

  for (uint32_t y = 0; y < height_; y++) {
    for (uint32_t x = 0; x < width_; x++) {
      fin >> bufF[(uint64_t)(width_ * y + x)];
    }
  }
  for (uint32_t y = 0; y < height_; y++) {
    for (uint32_t x = 0; x < width_; x++) {
      fin >> bufW[(uint64_t)(width_ * y + x)];
    }
  }

  CheckDirection(bufF, bufW);

  for (uint32_t y = 0; y < height_; y++) {
    for (uint32_t x = 0; x < width_; x++) {
      this->WriteFloor(
          field_factory_.create(x, y, bufF[(uint64_t)(width_ * y + x)]),
          CVector((int)x, (int)y));
    }
  }
  for (uint32_t y = 0; y < height_; y++) {
    for (uint32_t x = 0; x < width_; x++) {
      this->WriteWall(
          field_factory_.create(x, y, bufW[(uint64_t)(width_ * y + x)]),
          CVector((int)x, (int)y));
    }
  }
  return 0;
}

void CFieldHolder::CheckDirection(std::vector<std::string>& bufF,
                                  std::vector<std::string>& bufW) {
  auto aug = bufF;
  auto f = CDataLoader::GetIns().Get("field")->GetChild("directional");
  for (uint32_t y = 0; y < height_; y++) {
    for (uint32_t x = 0; x < width_; x++) {
      {
        auto c = f->GetChild(aug[(uint64_t)(width_ * y + x)]);
        if (c == nullptr) continue;
        std::string urdl = "URDL";
        std::string dir = "_";
        int t = 0xF;
        bool isHit = false;
        for (int i = 0;; i++) {
          if (x <= 0) break;
          if (c->GetChild(std::to_string(i)) == nullptr) break;
          if (aug[(uint64_t)(width_ * y + (x - 1))] ==
              c->GetChild(std::to_string(i))->GetString())
            isHit |= true;
        }
        if (isHit) t &= 0b0111;
        isHit = false;
        for (int i = 0;; i++) {
          if (y >= height_ - 1) break;
          if (c->GetChild(std::to_string(i)) == nullptr) break;
          if (aug[(uint64_t)(width_ * (y + 1) + x)] ==
              c->GetChild(std::to_string(i))->GetString())
            isHit |= true;
        }
        if (isHit) t &= 0b1011;
        isHit = false;
        for (int i = 0;; i++) {
          if (x >= width_ - 1) break;
          if (c->GetChild(std::to_string(i)) == nullptr) break;
          if (aug[(uint64_t)(width_ * y + (x + 1))] ==
              c->GetChild(std::to_string(i))->GetString())
            isHit |= true;
        }
        if (isHit) t &= 0b1101;
        isHit = false;
        for (int i = 0;; i++) {
          if (y <= 0) break;
          if (c->GetChild(std::to_string(i)) == nullptr) break;
          if (aug[(uint64_t)(width_ * (y - 1) + x)] ==
              c->GetChild(std::to_string(i))->GetString())
            isHit |= true;
        }
        if (isHit) t &= 0b1110;
        isHit = false;
        for (int i = 0; i < 4; i++)
          if (t & (1 << i)) dir.push_back(urdl[i]);
        bufF[(uint64_t)(width_ * y + x)] =
            aug[(uint64_t)(width_ * y + x)] + dir;
      }
    }
  }
  aug = bufW;
  for (uint32_t y = 0; y < height_; y++) {
    for (uint32_t x = 0; x < width_; x++) {
      {
        auto c = f->GetChild(aug[(uint64_t)(width_ * y + x)]);
        if (c == nullptr) continue;
        std::string urdl = "URDL";
        std::string dir = "_";
        int t = 0xF;
        bool isHit = false;
        for (int i = 0;; i++) {
          if (x <= 0) break;
          if (c->GetChild(std::to_string(i)) == nullptr) break;
          if (aug[(uint64_t)(width_ * y + (x - 1))] ==
              c->GetChild(std::to_string(i))->GetString())
            isHit |= true;
        }
        if (isHit) t &= 0b0111;
        isHit = false;
        for (int i = 0;; i++) {
          if (y >= height_ - 1) break;
          if (c->GetChild(std::to_string(i)) == nullptr) break;
          if (aug[(uint64_t)(width_ * (y + 1) + x)] ==
              c->GetChild(std::to_string(i))->GetString())
            isHit |= true;
        }
        if (isHit) t &= 0b1011;
        isHit = false;
        for (int i = 0;; i++) {
          if (x >= width_ - 1) break;
          if (c->GetChild(std::to_string(i)) == nullptr) break;
          if (aug[(uint64_t)(width_ * y + (x + 1))] ==
              c->GetChild(std::to_string(i))->GetString())
            isHit |= true;
        }
        if (isHit) t &= 0b1101;
        isHit = false;
        for (int i = 0;; i++) {
          if (y <= 0) break;
          if (c->GetChild(std::to_string(i)) == nullptr) break;
          if (aug[(uint64_t)(width_ * (y - 1) + x)] ==
              c->GetChild(std::to_string(i))->GetString())
            isHit |= true;
        }
        if (isHit) t &= 0b1110;
        isHit = false;
        for (int i = 0; i < 4; i++)
          if (t & (1 << i)) dir.push_back(urdl[i]);
        bufW[(uint64_t)(width_ * y + x)] =
            aug[(uint64_t)(width_ * y + x)] + dir;
      }
    }
  }
}
