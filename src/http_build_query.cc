#include "Telegram/http_build_query.h"

std::string http_build_query(std::map<std::string, std::string> data) {

  std::string result = "";

  std::map<std::string, std::string>::iterator it;

  for (it = data.begin(); it != data.end(); it++) {
    result = result + it->first + "=" + it->second + "&";
  }

  return result;
}
