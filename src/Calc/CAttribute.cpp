#include "CAttribute.h"

#include <cmath>

CAttribute CAttribute::operator*(double a) {
  CAttribute ret(0.0);
  ret.none_ = this->none_ * a;
  ret.fire_ = this->fire_ * a;
  ret.aqua_ = this->aqua_ * a;
  ret.thunder_ = this->thunder_ * a;
  ret.flower_ = this->flower_ * a;
  ret.ice_ = this->ice_ * a;
  ret.wind_ = this->wind_ * a;
  return ret;
}

CAttribute& CAttribute::operator*=(CAttribute a) {
  *this = *this * a;
  return *this;
}

CAttribute CAttribute::operator/(double a) {
  a = 1.0 / a;
  CAttribute ret(0.0);
  ret = *this * a;
  return ret;
}

CAttribute::CAttribute(double init)
    : none_(init),
      fire_(init),
      aqua_(init),
      thunder_(init),
      flower_(init),
      ice_(init),
      wind_(init) {}

CAttribute& CAttribute::None(double value) {
  this->none_ = value;
  return *this;
}

CAttribute& CAttribute::Fire(double value) {
  this->fire_ = value;
  return *this;
}

CAttribute& CAttribute::Aqua(double value) {
  this->aqua_ = value;
  return *this;
}

CAttribute& CAttribute::Thunder(double value) {
  this->thunder_ = value;
  return *this;
}

CAttribute& CAttribute::Flower(double value) {
  this->flower_ = value;
  return *this;
}

CAttribute& CAttribute::Ice(double value) {
  this->ice_ = value;
  return *this;
}

CAttribute& CAttribute::Wind(double value) {
  this->wind_ = value;
  return *this;
}

CAttribute CAttribute::operator*(CAttribute a) {
  CAttribute ret(0.0);
  ret.none_ = this->none_ * a.none_;
  ret.fire_ = this->fire_ * a.fire_;
  ret.aqua_ = this->aqua_ * a.aqua_;
  ret.thunder_ = this->thunder_ * a.thunder_;
  ret.flower_ = this->flower_ * a.flower_;
  ret.ice_ = this->ice_ * a.ice_;
  ret.wind_ = this->wind_ * a.wind_;
  return ret;
}

CAttribute CAttribute::operator/(CAttribute a) {
  CAttribute ret(0.0);
  ret.none_ = this->none_ / a.none_;
  ret.fire_ = this->fire_ / a.fire_;
  ret.aqua_ = this->aqua_ / a.aqua_;
  ret.thunder_ = this->thunder_ / a.thunder_;
  ret.flower_ = this->flower_ / a.flower_;
  ret.ice_ = this->ice_ / a.ice_;
  ret.wind_ = this->wind_ / a.wind_;
  return ret;
}

CAttribute CAttribute::operator+(CAttribute a) {
  CAttribute ret(0.0);
  ret.none_ = this->none_ + a.none_;
  ret.fire_ = this->fire_ + a.fire_;
  ret.aqua_ = this->aqua_ + a.aqua_;
  ret.thunder_ = this->thunder_ + a.thunder_;
  ret.flower_ = this->flower_ + a.flower_;
  ret.ice_ = this->ice_ + a.ice_;
  ret.wind_ = this->wind_ + a.wind_;
  return ret;
}

CAttribute& CAttribute::operator+=(CAttribute a) {
  *this = *this + a;
  return *this;
}

CAttribute CAttribute::operator-(CAttribute a) { return *this + (a * -1.0); }

bool CAttribute::IsZero() { return Sum() < Constant::kZeroBorder; }

double CAttribute::Sum() {
  return none_ + fire_ + aqua_ + thunder_ + flower_ + ice_ + wind_;
}

void CAttribute::Load(const CDataNode *c) {
  double init = c->GetChild("base")->GetDouble();
  const CDataNode* cur = nullptr;
  cur = c->GetChild("none");
  if (cur == nullptr) {
    none_ = init;
  } else
    none_ = cur->GetDouble();
  cur = c->GetChild("fire");
  if (cur == nullptr) {
    fire_ = init;
  } else
    fire_ = cur->GetDouble();
  cur = c->GetChild("aqua");
  if (cur == nullptr) {
    aqua_ = init;
  } else
    aqua_ = cur->GetDouble();
  cur = c->GetChild("thunder");
  if (cur == nullptr) {
    thunder_ = init;
  } else
    thunder_ = cur->GetDouble();
  cur = c->GetChild("flower");
  if (cur == nullptr) {
    flower_ = init;
  } else
    flower_ = cur->GetDouble();
  cur = c->GetChild("ice");
  if (cur == nullptr) {
    ice_ = init;
  } else
    ice_ = cur->GetDouble();
  cur = c->GetChild("wind");
  if (cur == nullptr) {
    wind_ = init;
  } else
    wind_ = cur->GetDouble();
}
