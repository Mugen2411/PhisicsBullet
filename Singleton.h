#pragma once

template <class T>
class Singleton {
 protected:
  Singleton() = default;

 public:
  virtual ~Singleton() {}
  static T& getIns() {
    static T instance;
    return instance;
  }

 private:
  void operator=(const Singleton& obj) = delete;
  Singleton(const Singleton& obj) = delete;
};