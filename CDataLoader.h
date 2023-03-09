#pragma once
#include <fstream>
#include <memory>
#include <string>

#include "CDataNode.h"
#include "Singleton.h"

class CDataLoader : public Singleton<CDataLoader> {
 public:
  const CDataNode* const Get() {
    if (!root_) {
      MessageBox(NULL, "Get before Load", "CDataLoader", MB_OK);
      abort();
    }
    return root_.get();
  }

  void Load(std::string path) {
    path_ = path;
    std::ifstream ifstr(path_);
    root_.reset(new CDataNode());
    parseBlock(root_, ifstr);
  }

  void Output() {
    std::ofstream ofstr(path_ + ".log");
    root_->Output(ofstr, 0);
  }

 private:
  CDataLoader() {}

  std::string path_;
  std::shared_ptr<CDataNode> root_;

  std::shared_ptr<CDataNode> parseBlock(std::shared_ptr<CDataNode> parent,
                                        std::ifstream& ifstr);

  std::string GetString(std::ifstream& ifstr);

  friend Singleton<CDataLoader>;
};