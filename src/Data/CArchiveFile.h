#pragma once
#include "CDataLoader.h"
#include <map>

class CArchiveFile{
 public:
 private:
  struct FILE_CONTENTS{
   std::unique_ptr<std::vector<BYTE>> bin;
  }
  std::map<std::string, FILE_CONTENTS> indices;
  int num_files;

}