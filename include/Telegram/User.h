#ifndef _TG_USER_H_
#define _TG_USER_H_

#include <json/json.h>
#include <string>

namespace Telegram {

  class User {
  public:
    User(Json::Value);

	Json::Int64 getId();
	std::string getFirstName();
	std::string getLastName();
	std::string getUserName();

  private:
    Json::Int64 id;
    std::string first_name;
    std::string last_name;
    std::string username;
  };
}

#endif
