#ifndef _TG_CHAT_H_
#define _TG_CHAT_H_

#include <json/json.h>
#include <string>

namespace Telegram {

  class Chat {
  public:
    Chat(Json::Value);

    Json::Int64 getId();
    std::string getUsername();

  private:
    Json::Int64 id;
    std::string type;
    std::string title;
    std::string username;
    std::string first_name;
    std::string last_name;
  };
}

#endif
