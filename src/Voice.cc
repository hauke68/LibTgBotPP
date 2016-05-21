#include "Telegram/Voice.h"

Telegram::Voice::Voice(Json::Value json) {

  this->file_id = json["file_id"].asString();
  this->duration = json["duration"].asInt64();
  this->mime_type = json["mime_type"].asString();
  this->file_size = json["file_size"].asInt64();
}
