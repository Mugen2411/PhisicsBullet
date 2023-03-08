#pragma once
#include <Windows.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <stdexcept>

class CDataNode {
 public:
  CDataNode() : contents(), childs_() {}
  CDataNode(int value) : contents(value) {}
  CDataNode(double value) : contents(value) {}
  enum class Type { kParent, kInt, kDbl };
  struct Contents {
    Contents() : tag(Type::kParent) {}
    Contents(int value) : tag(Type::kInt), data{.intData = value} {}
    Contents(double value) : tag(Type::kDbl), data{.dblData = value} {}
    Type tag;
    union data_t {
      int intData;
      double dblData;
    } data;
  };
  const CDataNode* GetChild(std::string key) const{
    if (contents.tag != Type::kParent) {
      MessageBox(NULL, "operator[] used in not parent object.", "CDataNode",
                 MB_OK);
      abort();
    }
    auto ret = childs_.find(key);
    if (ret == childs_.end()) return nullptr;
    return ret->second.get();
  }
  int getInt() const {
    if (contents.tag != Type::kInt) {
      MessageBox(NULL, "getInt used in not int object.", "CDataNode", MB_OK);
      abort();
    }
    return contents.data.intData;
  }
  double getDouble() const{
    if (contents.tag != Type::kDbl) {
      MessageBox(NULL, "getDouble used in not double object.", "CDataNode",
                 MB_OK);
      abort();
    }
    return contents.data.dblData;
  }

  void AddChild(std::string key, std::shared_ptr<CDataNode> node) {
    childs_.emplace(key, node);
  }

  void Output(int depth) {
    for (auto &i : childs_) {
      for (int j = 0; j < depth; j++) OutputDebugString("  ");
      OutputDebugString((i.first).c_str());
      if (i.second->contents.tag == Type::kParent) {
        OutputDebugString("{\n");
        i.second->Output(depth + 1);
        for (int j = 0; j < depth; j++) OutputDebugString("  ");
        OutputDebugString("}\n");
      } else {
        OutputDebugString(":");
        if (i.second->contents.tag == Type::kInt)
          OutputDebugString(
              (std::to_string(i.second->contents.data.intData) + '\n').c_str());
        if (i.second->contents.tag == Type::kDbl)
          OutputDebugString(
              (std::to_string(i.second->contents.data.dblData) + '\n').c_str());
      }
    }
  }

 private:
  Contents contents;
  std::unordered_map<std::string, std::shared_ptr<CDataNode>> childs_;
};