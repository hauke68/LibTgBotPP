#ifndef _TG_AUDIO_H_
#define _TG_AUDIO_H_

#include <json/json.h>
#include <string>

namespace Telegram {

  class Audio {
  public:
    Audio(Json::Value);

  private:
    std::string file_id;
    Json::Int64 duration;
    std::string performer;
    std::string title;
    std::string mime_type;
    Json::Int64 file_size;
  };
}

#endif
