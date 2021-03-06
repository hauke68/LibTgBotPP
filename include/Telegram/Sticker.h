#ifndef _TG_STICKER_H_
#define _TG_STICKER_H_

#include <json/json.h>
#include <string>

#include <Telegram/PhotoSize.h>

namespace Telegram {

  class Sticker {
  public:
    Sticker(Json::Value);

  private:
    std::string file_id;
    Json::Int64 width;
    Json::Int64 height;
    PhotoSize *thumb;
    std::string emoji;
    Json::Int64 file_size;
  };
}

#endif
