#include "Sticker.h"

Telegram::Sticker::Sticker(Json::Value json) {

  this->file_id = json["file_id"].asString();
  this->width = json["width"].asInt64();
  this->height = json["height"].asInt64();
  this->thumb = new PhotoSize(json["thumb"]);
  this->file_size = json["file_size"].asInt64();
}
