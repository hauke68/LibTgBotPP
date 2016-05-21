#ifndef _TG_CONTACT_H_
#define _TG_CONTACT_H_

#include <json/json.h>
#include <string>

namespace Telegram {

  class Contact {
  public:
    Contact(Json::Value);

  private:
    std::string phone_number;
    std::string first_name;
    std::string last_name;
    Json::Int64 user_id;
  };
}

#endif
