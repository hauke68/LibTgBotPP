#include "Telegram/Contact.h"

Telegram::Contact::Contact(Json::Value json) {

  this->phone_number = json["phone_number"].asString();
  this->first_name = json["first_name"].asString();
  this->last_name = json["last_name"].asString();
  this->user_id = json["user_id"].asInt64();
}
