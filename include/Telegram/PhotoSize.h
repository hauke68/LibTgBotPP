#ifndef _TG_PHOTOSIZE_H_
#define _TG_PHOTOSIZE_H_

#include <json/json.h>
#include <string>

namespace Telegram {

  class PhotoSize {
  public:
    PhotoSize(Json::Value);

  private:
    std::string file_id;
    Json::Int64 width;
    Json::Int64 height;
    Json::Int64 file_size;
  };
}

#endif
