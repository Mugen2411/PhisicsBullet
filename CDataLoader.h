#pragma once
#include <fstream>
#include <memory>
#include <string>

#include "CDataNode.h"
#include "Singleton.h"

class CDataLoader : public Singleton<CDataLoader> {
 public:
  std::weak_ptr<CDataNode> Get() { return root_; }

  void Load(std::string path) {
    path_ = path;
    std::ifstream ifstr(path_);
    root_.reset(new CDataNode());
    parseBlock(root_, ifstr);
  }

  void Output() { root_->Output(0); }

 private:
  CDataLoader(){}

  std::string path_;
  std::shared_ptr<CDataNode> root_;

  std::shared_ptr<CDataNode> parseBlock(std::shared_ptr<CDataNode> parent,
                                        std::ifstream& ifstr);

  friend Singleton<CDataLoader>;
};