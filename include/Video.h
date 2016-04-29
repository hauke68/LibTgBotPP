#ifndef _TG_VIDEO_H_
#define _TG_VIDEO_H_

#include <json/json.h>
#include <string>

#include "PhotoSize.h"

namespace Telegram {

  class Video {
  public:
    Video(Json::Value);

  private:
    std::string file_id;
    Json::Int64 width;
    Json::Int64 height;
    Json::Int64 duration;
    PhotoSize *thumb;
    std::string mime_type;
    Json::Int64 file_size;
  };
}

#endif
