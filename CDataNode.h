#pragma once
#include <Windows.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <fstream>

class CDataLoader;

class CDataNode {
 public:
  CDataNode() : contents(), childs_() {}
  CDataNode(int value) : contents(value) {}
  CDataNode(double value) : contents(value) {}
  CDataNode(std::string value) : contents(value) {}
  enum class Type { kParent, kInt, kDbl, kStr };
  struct Contents {
    Contents() : tag(Type::kParent) {}
    Contents(int value) : tag(Type::kInt) { data.intData = value; }
    Contents(double value) : tag(Type::kDbl) { data.dblData = value; }
    Contents(std::string value) : tag(Type::kStr) {
      strData = value;
    }
    Type tag;
    std::string strData;
    union data_t {
      int intData;
      double dblData;
    } data;
  };
  CDataNode* const GetChild(std::string key) const {
    if (contents.tag != Type::kParent) {
      MessageBox(NULL, "operator[] used in not parent object.", "CDataNode",
                 MB_OK);
      abort();
    }
    auto ret = childs_.find(key);
    if (ret == childs_.end()) return nullptr;
    return ret->second.get();
  }

  //多分重いので毎フレーム呼び出すべきでは無さそう
  const std::pair<std::string, std::shared_ptr<CDataNode>> GetChild(int order) const {
    if (contents.tag != Type::kParent) {
      MessageBox(NULL, "operator[] used in not parent object.", "CDataNode",
                 MB_OK);
      abort();
    }
    auto ret = childs_.begin();
    for (int i = 0; i < order; i++) {
      if (ret == childs_.end()) return {"__NULL__", nullptr};
      ret++;
    }
    if (ret == childs_.end()) return {"__NULL__", nullptr};
    return *ret;
  }
  int GetInt() const {
    if (contents.tag != Type::kInt) {
      MessageBox(NULL, "GetInt used in not int object.", "CDataNode", MB_OK);
      abort();
    }
    return contents.data.intData;
  }
  void SetInt(int value){
    if (contents.tag != Type::kInt) {
      MessageBox(NULL, "GetInt used in not int object.", "CDataNode", MB_OK);
      abort();
    }
    contents.data.intData = value;
  }
  double GetDouble() const {
    if (contents.tag != Type::kDbl) {
      MessageBox(NULL, "GetDouble used in not double object.", "CDataNode",
                 MB_OK);
      abort();
    }
    return contents.data.dblData;
  }
  std::string GetString() const {
    if (contents.tag != Type::kStr) {
      MessageBox(NULL, "GetString used in not string object.", "CDataNode",
                 MB_OK);
      abort();
    }
    return contents.strData;
  }

  void AddChild(std::string key, std::shared_ptr<CDataNode> node) {
    childs_.emplace(key, node);
  }

  void Output(std::ofstream& ofstr, int depth) {
    for (auto& i : childs_) {
      for (int j = 0; j < depth; j++) ofstr << "  ";
      ofstr << i.first;
      if (i.second->contents.tag == Type::kParent) {
        ofstr << "{\n";
        i.second->Output(ofstr, depth + 1);
        for (int j = 0; j < depth; j++) ofstr << "  ";
        ofstr << "}\n";
      } else {
        ofstr << ":";
        if (i.second->contents.tag == Type::kInt)
          ofstr << std::to_string(i.second->contents.data.intData) << std::endl;
        if (i.second->contents.tag == Type::kDbl)
          ofstr << std::to_string(i.second->contents.data.dblData) << std::endl;
        if (i.second->contents.tag == Type::kStr) {
          ofstr << i.second->contents.strData << std::endl;
        }
      }
    }
  }

 private:
  Contents contents;
  std::unordered_map<std::string, std::shared_ptr<CDataNode>> childs_;

  friend CDataLoader;
};