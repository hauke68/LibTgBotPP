#include "Telegram/TelegramBot.h"

#include <iostream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>

#include "http_build_query.h"
#include "json_encode.h"
#include "std.h"

#include "Telegram/Message.h"
#include "Telegram/MessageEntity.h"

#define API_URL "https://api.telegram.org/bot"

/**
 *Constructor of Bot
 */
Telegram::TelegramBot::TelegramBot() {

  this->api_url = "";
  this->init();
}

/**
 * Constructor of bot
 *
 * @param token a std::string
 */
Telegram::TelegramBot::TelegramBot(std::string token) {

  this->api_url = API_URL + token + "/";
  this->init();
}

/**
 * Adds a callback to the command list of the bot
 *
 * @param cmd a structure of type TCommand
 */
void Telegram::TelegramBot::addCommand(TCommand cmd) {

  if (cmd.command[0] != '/') {
    cmd.command = "/" + cmd.command;
  }
  this->command_map[cmd.command] = cmd;
}

/**
 * Set the webhook
 * The web hook URL is like https://<your domain>/cgi-bin/mybot.cgi
 * A web hook must be set before you can get any messages from the Telegram
 * network!
 *
 * @param url a std::string with the URL of the hook
 */
void Telegram::TelegramBot::setWebhook(std::string url) {

  std::map<std::string, std::string> params;

  params["url"] = url;
  this->apiRequest("setWebhook", params);
}

/**
 * Process incoming message
 *
 * @param message a std::string storing the message sent by the Telegram system
 *
 */
void Telegram::TelegramBot::processMessage(std::string message) {

  this->msg = new Telegram::Message(message);

  Telegram::TMessageEntities entities = this->msg->getEntities();

  if (entities.size() && (entities[0]->getType() == "bot_command")) {
    this->sendMessage(this->processCommand(this->msg->getText()), this->msg->getChat()->getId());
  } else {
    this->sendMessage("Hello " + this->msg->getChat()->getUsername() + ", you told me: '" + msg->getText() + "'", this->msg->getChat()->getId());
  }
}

/**
 * Send a text message to a user
 */
Telegram::Message *Telegram::TelegramBot::sendMessage(std::string message, Json::Int64 chat_id) {

  return(this->sendMessage(message, SSTR(chat_id)));
}

/**
 * sendMessage sends a simple text message to a given chat (might be a user or a group)
 */
Telegram::Message* Telegram::TelegramBot::sendMessage(std::string message, std::string chat_id) {

	std::map<std::string, std::string> params;
	Json::Value obj;

	params["chat_id"] = chat_id;
	params["text"] = message;

	obj = this->apiRequestJson("sendMessage", params);

	return(new Telegram::Message(obj["result"]));
}

/**
 * Sends a picture from the internet to a chat
 */
Telegram::Message* Telegram::TelegramBot::sendPhoto(std::string URL, Json::Int64 chat_id) {

	return(this->sendPhoto(URL, SSTR(chat_id)));
}

/**
 * Sends a picture from the internet to a chat
 */
Telegram::Message* Telegram::TelegramBot::sendPhoto(std::string URL, std::string chat_id) {

	Json::Value obj;

	std::map<std::string, std::string> params;

	params["chat_id"] = chat_id;
	params["photo"] = URL;

	obj = this->apiRequestJson("sendPhoto", params);

	return(new Telegram::Message(obj["result"]));
}

Telegram::Message *Telegram::TelegramBot::getMessage() {

  return(this->msg);
}

Telegram::TCommandMap Telegram::TelegramBot::getCommandMap() {

  return(this->command_map);
}

// Private methods
void Telegram::TelegramBot::init() {

  std::cout << "Content-type: text/html\r\n\r\n" << std::endl;
}

/**
 * A generic API request
 */
void Telegram::TelegramBot::apiRequest(std::string method, std::map<std::string, std::string> parameters) {

  parameters["method"] = method;

  Json::Value jValues;
  Json::StyledWriter w;

  for(std::map<std::string, std::string>::iterator it = parameters.begin(); it != parameters.end(); ++it) {
    jValues[(*it).first] = (*it).second;
  }

  try {
    cURLpp::Easy handle;
    std::string url = this->api_url + method + "?" + http_build_query(parameters);

    handle.setOpt(cURLpp::Options::Url(url));
    handle.setOpt(cURLpp::Options::ConnectTimeout(5));
    handle.setOpt(cURLpp::Options::Timeout(60));
    handle.perform(); // Do the curl request

    int code;
    code = cURLpp::Infos::ResponseCode::get(handle);
  }
  catch(cURLpp::LogicError &e) {
    Log(e.what());
  }
  catch(cURLpp::RuntimeError &e) {
    Log(e.what());
  }
  catch(std::exception &e) {
    Log(e.what());
  }
}

/**
 * An API request, posting JSON data
 */
Json::Value Telegram::TelegramBot::apiRequestJson(std::string method, std::map<std::string, std::string> parameters) {

	std::stringstream result; // Stores the result of the api call
	parameters["method"] = method;

	try {
		cURLpp::Easy handle;
		std::list<std::string> header;
		header.push_back("Content-Type: application/json");

		handle.setOpt(cURLpp::Options::Url(this->api_url));
		handle.setOpt(cURLpp::Options::ConnectTimeout(5));
		handle.setOpt(cURLpp::Options::Timeout(60));
		handle.setOpt(cURLpp::Options::HttpHeader(header));
		handle.setOpt(cURLpp::Options::PostFields(json_encode(parameters)));
		handle.setOpt(cURLpp::Options::WriteStream(&result));

		handle.perform(); // Do the curl request
	}
	catch(cURLpp::LogicError &e) {
		Log(e.what());
	}
	catch(cURLpp::RuntimeError &e) {
		Log(e.what());
	}
	catch(std::exception &e) {
		Log(e.what());
	}

	Json::Reader jreader;
	Json::Value obj;
	jreader.parse(result.str(), obj);

	return (obj);
}

std::string Telegram::TelegramBot::processCommand(std::string cmd) {

  // Process command
  std::string sCommand;
  std::string sResult;
  std::vector<std::string> vCmdLine = split(cmd, ' ');

  if((vCmdLine.size() > 0) && (this->command_map.find(vCmdLine[0]) != this->command_map.end())) {
    sCommand = vCmdLine[0];
    vCmdLine.erase(vCmdLine.begin()); // First value is the command itself
    TCommand cs = this->command_map[sCommand];
    sResult = (*cs.callback)(this, vCmdLine);
  } else {
    sResult = "Unknown command";
  }

  return(sResult);
}
