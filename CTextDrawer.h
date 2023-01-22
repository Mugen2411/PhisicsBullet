#pragma once
#include <list>
#include <string>
#include <vector>

#include "CVector.h"
#include "Singleton.h"

class CTextDrawer : public Singleton<CTextDrawer> {
 public:
  class Text {
   public:
    Text(std::string text, CVector position_, int mainColor, int edgeColor,
         int fontID)
        : text_(text),
          position_(position_),
          main_color_(mainColor),
          edge_color_(edgeColor),
          fontID_(fontID) {}
    Text() {}

    std::string text_;
    CVector position_;
    int main_color_;
    int edge_color_;
    int fontID_;
  };
  void SetPriority(int p) { priority_ = p; }
  void Register(Text txt);
  void RegisterForCostumeDetail(Text txt);
  void Render() const;
  void Clear();

 private:
  CTextDrawer();
  ~CTextDrawer();

  int priority_;  //àÍî‘è„ÇÃÉVÅ[ÉìÇ©ÇÁÇµÇ©éÛÇØéÊÇÁÇ»Ç¢ÅI
  std::vector<int> font_array_;
  std::list<Text> text_queue_;
  std::list<Text> costume_detail_queue_;

  std::string font_path_;

  friend class Singleton<CTextDrawer>;
};
