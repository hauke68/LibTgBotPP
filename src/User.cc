#include "Telegram/User.h"

Telegram::User::User(Json::Value json) {

  this->id = json["id"].asUInt64();
  this->first_name = json["first_name"].asString();
  this->last_name = json["last_name"].asString();
  this->username = json["username"].asString();
}
