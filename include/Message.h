#ifndef _TG_MESSAGE_H_
#define _TG_MESSAGE_H_

#include <json/json.h>

#include <string>
#include <vector>

#include "Audio.h"
#include "Chat.h"
#include "Contact.h"
#include "Document.h"
#include "Location.h"
#include "MessageEntity.h"
#include "PhotoSize.h"
#include "Sticker.h"
#include "User.h"
#include "Venue.h"
#include "Video.h"
#include "Voice.h"

namespace Telegram {

  /**
   * See https://core.telegram.org/bots/api#message
   */
  class Message {
  public:
    // Constructors
    Message(void);
    Message(Json::Value);
    Message(std::string);

    void setEntities(Json::Value);
    std::vector<PhotoSize*> setPhotos(Json::Value);

    Telegram::Chat *getChat();
    std::string getText();
    Telegram::TMessageEntities getEntities();

  private:
    Json::UInt64 message_id;
    User *from;
    Json::Int64 date;
    Chat *chat;
    User *forward_from;
    Json::Int64 forward_date;
    Message *reply_to_message;
    std::string text;
    Telegram::TMessageEntities entities;
    Audio *audio;
    Document *document;
    std::vector<PhotoSize*> photo;
    Sticker *sticker;
    Video *video;
    Voice *voice;
    std::string caption;
    Contact *contact;
    Location *location;
    Venue *venue;
    User *new_chat_member;
    User *left_chat_member;
    std::string new_chat_title;
    std::vector<PhotoSize*> new_chat_photo;
    int delete_chat_photo;
    int group_chat_created;
    int supergroup_chat_created;
    Json::Int64 migrate_to_chat_id;
    Json::Int64 migrate_from_chat_id;
    Message *pinned_message;

    // Methods
    void init(void);
    void init(Json::Value);
  };
}

#endif
