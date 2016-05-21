#include "Telegram/Chat.h"

Telegram::Chat::Chat(Json::Value json) {

  this->id = json["id"].asUInt64();
  this->type = json["type"].asString();
  this->title = json["title"].asString();
  this->username = json["username"].asString();
  this->first_name = json["first_name"].asString();
  this->last_name = json["last_name"].asString();
}

Json::Int64 Telegram::Chat::getId() {

  return(this->id);
}

std::string Telegram::Chat::getUsername() {

  return(this->username);
}
