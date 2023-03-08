#include "CDataLoader.h"

std::shared_ptr<CDataNode> CDataLoader::parseBlock(
    std::shared_ptr<CDataNode> parent, std::ifstream& ifstr) {
  std::string key;
  int ch = 0;
  while (ch != -1) {
    ch = ifstr.get();
    if (ch == ' ' || ch == '\n' || ch == '\t') continue;
    if (ch == ':') {
      if (key.size() == 0) {
        MessageBox(NULL, "key is none", "CDataLoader", MB_OK);
        abort();
      }
      std::string num;
      ch = ifstr.get();
      bool isDbl = false;
      while (ch != ' ' && ch != '\n') {
        if (ch == '.') isDbl |= true;
        num.push_back(ch);
        ch = ifstr.get();
      }
      if (isDbl) {
        double d = std::stod(num);
        parent->AddChild(key, std::make_shared<CDataNode>(d));
      } else {
        int d = std::stoi(num, nullptr, 0);
        parent->AddChild(key, std::make_shared<CDataNode>(d));
      }
      //OutputDebugString((key + '\n').c_str());
      key.clear();
      continue;
    }
    if (ch == '{') {
      if (key.size() == 0) {
        MessageBox(NULL, "key is none", "CDataLoader", MB_OK);
        abort();
      }
      std::shared_ptr<CDataNode> child = std::make_shared<CDataNode>();
      parseBlock(child, ifstr);
      parent->AddChild(key, child);
      //OutputDebugString((key +'\n').c_str());
      key.clear();
      continue;
    }
    if (ch == '}') {
      ifstr.get();
      break;
    }
    key.push_back(ch);
  }
  return parent;
}
