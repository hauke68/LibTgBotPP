set (HEADERS
  include/Telegram/Audio.h
  include/Telegram/Document.h
  include/Telegram/json_encode.h
  include/Telegram/PhotoSize.h
  include/Telegram/User.h
  include/Telegram/Chat.h
  include/Telegram/exec.h
  include/Telegram/Location.h
  include/Telegram/std.h
  include/Telegram/Venue.h
  include/Telegram/Contact.h
  include/Telegram/explode.h
  include/Telegram/MessageEntity.h
  include/Telegram/Sticker.h
  include/Telegram/Video.h
  include/Telegram/http_build_query.h
  include/Telegram/Message.h
  include/Telegram/TelegramBot.h
  include/Telegram/Voice.h
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

project(libtgbotpp)

find_package(PkgConfig)

pkg_check_modules(JSONCPP REQUIRED jsoncpp)
pkg_check_modules(CURL REQUIRED curlpp)

include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})

set(LIBS ${LIBS} ${JSONCPP_LIBRARIES})
set(LIBS ${LIBS} ${CURL_LIBRARIES})
set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/pkgconfig")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(tgbotpp SHARED ${SOURCES})

install(TARGETS tgbotpp DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/Telegram)
install(FILES tgbotpp.pc DESTINATION "${INSTALL_PKGCONFIG_DIR}")
