#include "Telegram/MessageEntity.h"

Telegram::MessageEntity::MessageEntity(Json::Value json) {

  this->type = json["type"].asString();
  this->offset = json["offset"].asUInt64();
  this->length = json["length"].asUInt64();
  this->url = json["url"].asString();
}

std::string Telegram::MessageEntity::getType() {

  return(this->type);
}
