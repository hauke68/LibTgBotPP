#ifndef _TG_VENUE_H_
#define _TG_VENUE_H_

#include <string>

#include "Location.h"

namespace Telegram {

  class Venue {
  public:
    Venue(Json::Value);

  private:
    Location *location;
    std::string title;
    std::string address;
    std::string foursquare_id;
  };
}

#endif
