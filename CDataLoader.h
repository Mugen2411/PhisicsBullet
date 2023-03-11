#pragma once
#include <fstream>
#include <memory>
#include <string>

#include "CDataNode.h"
#include "Singleton.h"

class CDataLoader : public Singleton<CDataLoader> {
 public:
  const CDataNode* const Get(std::string key) {
    auto ret = root_.find(key);
    if (ret == root_.end()) {
      MessageBox(NULL, "Get before Load", "CDataLoader", MB_OK);
      abort();
    }
    return root_[key].get();
  }

  void Load(std::string key, std::string path) {
    path_[key] = path;
    std::ifstream ifstr(path_[key]);
    root_[key].reset(new CDataNode());
    parseBlock(root_[key], ifstr);
  }

  void Output(std::string key) {
    std::ofstream ofstr(path_[key] + ".log");
    root_[key]->Output(ofstr, 0);
  }

 private:
  CDataLoader() {}

  std::unordered_map<std::string, std::string> path_;
  std::unordered_map<std::string, std::shared_ptr<CDataNode>> root_;

  std::shared_ptr<CDataNode> parseBlock(std::shared_ptr<CDataNode> parent,
                                        std::ifstream& ifstr);

  std::string GetString(std::ifstream& ifstr);

  friend Singleton<CDataLoader>;
};