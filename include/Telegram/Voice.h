#ifndef _TG_VOICE_H_
#define _TG_VOICE_H_

#include <json/json.h>
#include <string>

namespace Telegram {

  class Voice {
  public:
    Voice(Json::Value);

  private:
    std::string file_id;
    Json::Int64 duration;
    std::string mime_type;
    Json::Int64 file_size;
  };
}

#endif
