#include "Telegram/Document.h"

Telegram::Document::Document(Json::Value json) {

  this->file_id = json["file_id"].asString();
  this->thumb = new PhotoSize(json["thumb"]);
  this->file_name = json["file_name"].asString();
  this->mime_type = json["mime_type"].asString();
  this->file_size = json["file_size"].asInt64();
}
