#include "Venue.h"

Telegram::Venue::Venue(Json::Value json) {

  this->location = new Location(json["location"]);
  this->title = json["title"].asString();
  this->address = json["address"].asString();
  this->foursquare_id = json["foursquare_id"].asString();
}
