#include "CCostumeFactory.h"

#include <algorithm>

#include "CCostume_Archer_Flame.h"
#include "CCostume_Archer_Thunder.h"
#include "CCostume_Festa.h"
#include "CCostume_Swimsuit.h"
#include "CCostume_Uniform.h"
#include "CCostume_Chinese.h"
#include "CCostume_Firefighter.h"
#include "CCostume_Burner.h"

void CCostumeFactory::Register(CCostumeBase* f) {
  list_.push_back(std::shared_ptr<CCostumeBase>(f));
}

CCostumeFactory::CCostumeFactory() {
  Register(new CCostume_Uniform("C_Uniform"));
  Register(new CCostume_Festa("C_Festa"));
  Register(new CCostume_Archer_Flame("C_Archer_Flame"));
  Register(new CCostume_Archer_Thunder("C_Archer_Thunder"));
  Register(new CCostume_Swimsuit("C_Swimsuit"));
  Register(new CCostume_Chinese("C_Chinese"));
  Register(new CCostume_Firefighter("C_Firefighter"));
  Register(new CCostume_Burner("C_Burner"));
}

CCostumeBase* CCostumeFactory::Create(std::string gid_) {
  auto itr = std::find_if(
      list_.begin(), --list_.end(),
      [&](std::shared_ptr<CCostumeBase>& v) { return (*v).gid_ == gid_; });
  return (*itr)->Clone();
}

CCostumeBase* CCostumeFactory::Create(int idx) {
  auto itr = list_[idx];
  return itr->Clone();
}
