#include "Telegram/User.h"

/**
 * Constructor of class User
 */
Telegram::User::User(Json::Value json) {

  this->id = json["id"].asUInt64();
  this->first_name = json["first_name"].asString();
  this->last_name = json["last_name"].asString();
  this->username = json["username"].asString();
}

// Getter
Json::Int64 Telegram::User::getId() {

	return(this->id);
}

std::string Telegram::User::getFirstName() {

	return(this->first_name);
}

std::string Telegram::User::getLastName() {

	return(this->last_name);
}

std::string Telegram::User::getUserName() {

	return(this->username);
}
