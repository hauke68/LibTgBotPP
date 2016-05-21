#include "Telegram/Audio.h"

Telegram::Audio::Audio(Json::Value json) {

  this->file_id = json["file_id"].asString();
  this->duration = json["duration"].asUInt64();
  this->performer = json["performer"].asString();
  this->title = json["title"].asString();
  this->mime_type = json["mime_type"].asString();
  this->file_size = json["file_size"].asUInt64();
}
