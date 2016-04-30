#ifndef _TG_MESSAGE_H_
#define _TG_MESSAGE_H_

#include <json/json.h>

#include <string>
#include <vector>

#include <Telegram/Audio.h>
#include <Telegram/Chat.h>
#include <Telegram/Contact.h>
#include <Telegram/Document.h>
#include <Telegram/Location.h>
#include <Telegram/MessageEntity.h>
#include <Telegram/PhotoSize.h>
#include <Telegram/Sticker.h>
#include <Telegram/User.h>
#include <Telegram/Venue.h>
#include <Telegram/Video.h>
#include <Telegram/Voice.h>

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
