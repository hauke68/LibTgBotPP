#include "Telegram/Message.h"

// Generic constructor
// @TODO: Make this an "init"-Method and call it from the constructor
Telegram::Message::Message(void) {

  this->init();
}

Telegram::Message::Message(Json::Value json) {

  if (json["message"].isNull()) {
    this->init();
    return;
  }

  this->init(json);
}

Telegram::Message::Message(std::string message) {

  Json::Value json;
  Json::Reader reader;

  reader.parse(message, json);

  this->init(json);
}

void Telegram::Message::init(void) {

  this->message_id = 0;
  this->from = NULL;
  this->date = 0;
  this->chat = NULL;
  this->forward_from = NULL;
  this->forward_date = 0;
  this->reply_to_message = NULL;
  this->text = "";
  this->entities.clear();
  this->audio = NULL;
  this->document = NULL;
  this->photo.clear();
  this->sticker = NULL;
  this->video = NULL;
  this->voice = NULL;
  this->caption = "";
  this->contact = NULL;
  this->location = NULL;
  this->venue = NULL;
  this->new_chat_member = NULL;
  this->left_chat_member = NULL;
  this->new_chat_title = "";
  this->new_chat_photo.clear();
  this->delete_chat_photo = 0;
  this->group_chat_created = 0;
  this->supergroup_chat_created = 0;
  this->migrate_to_chat_id = 0;
  this->pinned_message = NULL;
}

void Telegram::Message::init(Json::Value json) {

  Json::Value msg = json["message"];

  this->message_id = msg["message_id"].asUInt64();
  this->from = new Telegram::User(msg["from"]);
  this->date = msg["date"].asUInt64();
  this->chat = new Telegram::Chat(msg["chat"]);
  this->forward_from = new Telegram::User(msg["forward_from"]);
  this->forward_date = msg["forward_date"].asUInt64();
  this->reply_to_message = new Telegram::Message(msg["reply_to_message"]);
  this->text = msg["text"].asString();
  this->setEntities(msg["entities"]);
  this->audio = new Audio(msg["audio"]);
  this->document = new Document(msg["document"]);
  this->photo = this->setPhotos(msg["photo"]);
  this->sticker = new Sticker(msg["sticker"]);
  this->video = new Video(msg["video"]);
  this->voice = new Voice(msg["voice"]);
  this->caption = msg["caption"].asString();
  this->contact = new Contact(msg["contact"]);
  this->location = new Location(msg["location"]);
  this->venue = new Venue(msg["venue"]);
  this->new_chat_member = new User(msg["new_chat_member"]);
  this->left_chat_member = new User(msg["left_chat_member"]);
  this->new_chat_title = msg["new_chat_title"].asString();
  this->new_chat_photo = this->setPhotos(msg["new_chat_photo"]);
  this->delete_chat_photo = msg["delete_chat_photo"].asInt64();
  this->group_chat_created = msg["group_chat_created"].asInt64();
  this->supergroup_chat_created = msg["supergroup_chat_created"].asInt64();
  this->migrate_to_chat_id = msg["migrate_to_chat_id"].asUInt64();
  this->migrate_from_chat_id = msg["migrate_from_chat_id"].asUInt64();
  this->pinned_message = new Message(msg["pinned_message"]);
}

// Setter
void Telegram::Message::setEntities(Json::Value entities) {

  Json::ArrayIndex size = entities.size();
  for(Json::ArrayIndex i = 0; i < size; i++) {
    Telegram::MessageEntity *entity = new Telegram::MessageEntity(entities[i]);
    this->entities.push_back(entity);
  }
}

std::vector<Telegram::PhotoSize*> Telegram::Message::setPhotos(Json::Value photos) {

  Json::ArrayIndex size = photos.size();
  std::vector<PhotoSize*> vPhotos;

  for(Json::ArrayIndex i = 0; i < size; i++) {
    Telegram::PhotoSize *photo_size = new Telegram::PhotoSize(photos[i]);
    vPhotos.push_back(photo_size);
  }

  return(vPhotos);
}

// Getter
Telegram::Chat *Telegram::Message::getChat() {

  return(this->chat);
}

std::string Telegram::Message::getText() {

  return(this->text);
}

Telegram::TMessageEntities Telegram::Message::getEntities() {

  return(this->entities);
}
