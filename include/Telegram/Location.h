#ifndef __TG_LOCATION_H_
#define __TG_LOCATION_H_

#include <json/json.h>

namespace Telegram {

  class Location {
  public:
    Location(Json::Value);

  private:
    float longitude;
    float latitude;
  };
}

#endif
