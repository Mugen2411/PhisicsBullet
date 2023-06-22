#include "CDataLoader.h"
#include <cstdlib>

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
      if (ch == '\"') {
        std::string tmp = GetString(ifstr);
        parent->AddChild(key, std::make_shared<CDataNode>(tmp));
        key.clear();
        continue;
      }
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
      //OutputDebugString((std::string("Load block:") + key + '\n').c_str());
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

std::string CDataLoader::GetString(std::ifstream& ifstr) {
  std::string ret;
  int ch = 0;
  bool isEscape = false;
  bool isMultByte = false;
  while (1) {
    ch = ifstr.get();
    if (ch == '\"') break;
    if (isEscape) {
      if (ch == 'n')
        ret.push_back('\n');
      else if (ch == 't')
        ret.push_back('\t');
      else if (ch == '\\')
        ret.push_back('\\');
      isEscape = false;
      continue;
    }
    if (ch == '\n' || ch == '\t') continue;
    if (ch == '\\') {
      isEscape = true;
      continue;
    }
    ret.push_back(ch);
  }
  return ret;
}
