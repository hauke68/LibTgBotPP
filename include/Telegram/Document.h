#ifndef _TG_DOCUMENT_H_
#define _TG_DOCUMENT_H_

#include <json/json.h>
#include <string>

#include <Telegram/PhotoSize.h>

namespace Telegram {

  class Document {
  public:
    Document(Json::Value);

  private:
    std::string file_id;
    PhotoSize *thumb;
    std::string file_name;
    std::string mime_type;
    Json::Int64 file_size;
  };
}

#endif
