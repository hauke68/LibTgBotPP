#include "Telegram/Location.h"

Telegram::Location::Location(Json::Value json) {

  this->longitude = json["longitude"].asFloat();
  this->latitude = json["latitude"].asFloat();
}
