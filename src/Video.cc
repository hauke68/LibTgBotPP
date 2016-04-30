#include "Telegram/Video.h"

Telegram::Video::Video(Json::Value json) {

  this->file_id = json["file_id"].asString();
  this->width = json["width"].asInt64();
  this->height = json["height"].asInt64();
  this->duration = json["duration"].asInt64();
  this->thumb = new PhotoSize(json["thumb"]);
  this->mime_type = json["mime_type"].asString();
  this->file_size = json["file_size"].asInt64();
}
