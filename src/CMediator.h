#pragma once

class CParts;

class CMediator {
 public:
  virtual ~CMediator(){};
  virtual void Update() = 0;
  virtual void Render() const = 0;
  virtual void PartsChanged(CParts*) = 0;

 protected:
  CMediator(){};
  virtual void CreateParts() = 0;
};
