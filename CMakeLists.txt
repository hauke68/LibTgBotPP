set (HEADERS
	Audio.h
	Document.h
	json_encode.h
	PhotoSize.h
	User.h
	Chat.h
	exec.h
	Location.h
	std.h
	Venue.h
	Contact.h
	explode.h
	MessageEntity.h
	Sticker.h
	Video.h
	defines.h
  http_build_query.h
	Message.h
	TelegramBot.h
	Voice.h
)

cmake_minimum_required(VERSION 2.8)

project(libtg)

include_directories(${CMAKE_CURRENT_SOURCE_DIR/include)
add_library(tg SHARED main.cc)

install(TARGETS tg DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)

