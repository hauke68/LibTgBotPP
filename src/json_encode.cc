#include "json_encode.h"

std::string json_encode(std::map<std::string, std::string> parameters) {

  Json::Value jValues;
  Json::StyledWriter w;

  for(std::map<std::string, std::string>::iterator it = parameters.begin(); it != parameters.end(); ++it) {
    jValues[(*it).first] = (*it).second;
  }

  return(w.write(jValues));
}
