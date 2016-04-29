#ifndef _TG_USER_H_
#define _TG_USER_H_

#include <json/json.h>
#include <string>

namespace Telegram {

  class User {
  public:
    User(Json::Value);

  private:
    Json::Int64 id;
    std::string first_name;
    std::string last_name;
    std::string username;
  };
}

#endif
