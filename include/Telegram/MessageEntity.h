#ifndef _TG_MESSAGEENTITY_H_
#define _TG_MESSAGEENTITY_H_

#include <string>
#include <json/json.h>
#include <vector>

namespace Telegram {

  class MessageEntity {
  public:
    MessageEntity(Json::Value);

    std::string getType();

  private:
    std::string type;
    Json::Int64 offset;
    Json::Int64 length;
    std::string url;
  };

  typedef std::vector<Telegram::MessageEntity*> TMessageEntities;

}

#endif
