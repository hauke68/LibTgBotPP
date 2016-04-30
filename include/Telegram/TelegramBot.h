#ifndef _TELEGRAM_BOT_H_
#define _TELEGRAM_BOT_H_

#include <string>
#include <map>

#include <curl/curl.h>
#include <json/json.h>

#include <Telegram/Message.h>

namespace Telegram {

  class TelegramBot;

  // Typedef for callbacks
  typedef std::vector<std::string> TCommandLine;
  typedef std::string(*CommandCallback)(TelegramBot*, TCommandLine);
  typedef struct {
    std::string command;
    CommandCallback callback;
    std::string help_text;
  } TCommand;
  typedef std::map<std::string, TCommand> TCommandMap;

  class TelegramBot {

  public:
    TelegramBot();
    TelegramBot(std::string);

    void addCommand(TCommand);
    void setWebhook(std::string);
    void processMessage(std::string);
    void sendMessage(std::string, Json::Int64);
    void sendMessage(std::string, std::string);

    Telegram::Message *getMessage();
    std::map<std::string, TCommand> getCommandMap();

    // Callback methods
    /*
    std::string start(Telegram::TelegramBot, tvCommandLine);
    std::string help(tvCommandLine);
    std::string whoami(tvCommandLine);
    std::string loadavg(tvCommandLine);
    std::string proc(tvCommandLine);
    */

  private:
    std::string api_url;
    Telegram::Message *msg;
    TCommandMap command_map;
    Json::Int64 chat_id;

    void init();
    void apiRequest(std::string, std::map<std::string, std::string>);
    void apiRequestJson(std::string, std::map<std::string, std::string>);
    std::string processCommand(std::string);
  };
}

#endif
