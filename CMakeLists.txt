set (HEADERS
  include/Audio.h
  include/Document.h
  include/json_encode.h
  include/PhotoSize.h
  include/User.h
  include/Chat.h
  include/exec.h
  include/Location.h
  include/std.h
  include/Venue.h
  include/Contact.h
  include/explode.h
  include/MessageEntity.h
  include/Sticker.h
  include/Video.h
  include/http_build_query.h
  include/Message.h
  include/TelegramBot.h
  include/Voice.h
)

set (SOURCES
  src/Audio.cc
  src/Document.cc
  src/json_encode.cc
  src/PhotoSize.cc
  src/User.cc
  src/Chat.cc
  src/exec.cc
  src/Location.cc
  src/std.cc
  src/Venue.cc
  src/Contact.cc
  src/explode.cc
  src/MessageEntity.cc
  src/Sticker.cc
  src/Video.cc
  src/http_build_query.cc
  src/Message.cc
  src/TelegramBot.cc
  src/Voice.cc
)

cmake_minimum_required(VERSION 2.8)

project(libtg)

find_package(PkgConfig)

pkg_check_modules(JSONCPP REQUIRED jsoncpp)
pkg_check_modules(CURL REQUIRED curlpp)

include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})

set(LIBS ${LIBS} ${JSONCPP_LIBRARIES})
set(LIBS ${LIBS} ${CURL_LIBRARIES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(tg SHARED ${SOURCES})

install(TARGETS tg DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)

