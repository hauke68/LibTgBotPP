#ifndef _TELEGRAM_BOT_H_
#define _TELEGRAM_BOT_H_

#include <string>
#include <map>

#include <curlpp/cURLpp.hpp>
#include <json/json.h>

#include <Telegram/Message.h>
#include <Telegram/User.h>

/**
 * Namespace Telegram used for the bot project
 */
namespace Telegram {

  class TelegramBot;

  // Typedef for callbacks
  typedef std::vector<std::string> TCommandLine; //!< Arguments for the bot's commands
  typedef std::string(*CommandCallback)(TelegramBot*, TCommandLine); //!< Definition for a callback routine
  /**
   * Structure to hold data for callbacks
   */
  typedef struct {
    std::string command; //!< The command, e.g. /help
    CommandCallback callback; //!< Pointer to the callback function
    std::string help_text; //!< Help text of the command
  } TCommand;
  typedef std::map<std::string, TCommand> TCommandMap; //!< Map that stores the known commands

  class TelegramBot {

  public:
    TelegramBot();
    TelegramBot(std::string);

    void addCommand(TCommand);
    void setWebhook(std::string);
    void processMessage(std::string);

    Telegram::User* getMe(void);

    Telegram::Message* sendMessage(std::string, Json::Int64);
    Telegram::Message* sendMessage(std::string, std::string);

    Telegram::Message *sendPhoto(std::string, Json::Int64);
    Telegram::Message *sendPhoto(std::string, std::string);

    Telegram::Message *getMessage();
    std::map<std::string, TCommand> getCommandMap();

  private:
    std::string api_url;
    Telegram::Message *msg;
    TCommandMap command_map;
    Json::Int64 chat_id;

    void init();
    void apiRequest(std::string, std::map<std::string, std::string>);
    Json::Value apiRequestJson(std::string, std::map<std::string, std::string>);
    Json::Value apiRequestFile(std::string, std::string, std::string);
    std::string processCommand(std::string);
  };
}

#endif
