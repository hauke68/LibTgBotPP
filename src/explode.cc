#include "Telegram/explode.h"

std::vector<std::string> explode( const std::string &delimiter, const std::string &str) {

  std::vector<std::string> arr;

  int strleng = str.length();
  int delleng = delimiter.length();
  if (delleng == 0)
    return arr;//no change

  int i = 0;
  int k = 0;
  while(i < strleng) {
    int j = 0;
    while ((i+j < strleng) && (j < delleng) && (str[i+j] == delimiter[j]))
      j++;
    if (j == delleng) {
      arr.push_back(str.substr(k, i-k));
      i += delleng;
      k = i;
    } else {
      i++;
    }
  }
  arr.push_back(str.substr(k, i-k));
  return arr;
}
