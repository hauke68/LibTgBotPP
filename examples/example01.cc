/**
 *
 * This is a simple bot that can echo a message, piped to its
 * binary and is usable as a cgi script to react on some
 * simple commands.
 *
 * Before you first use this example, change WEBHOOK_URL and
 * BOT_TOKEN according to your needs and your web server!
 *
 * Example:
 * WEBHOK_URL: https://bot.foobar.tld/cgi-bin/bot.cgi
 * BOT_TOKEN: Your token given by Telegram's Bot Father!
 *
 * To compile do:
 * g++ -c -o example01.o -I/usr/include/jsoncpp example01.cc
 * g++ -o example01 example01.o -ltgbotpp
 *
 * Run:
 * echo "Your message" | ./example01  -u <your user id>
 */

#include <Telegram/TelegramBot.h>

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <termios.h>
#include <stdbool.h>
#include <unistd.h>

#define WEBHOOK_URL "https://<your-web-server>/cgi-bin/<binary name>"
#define BOT_TOKEN "<your token>"
#define SSTR( x ) static_cast< std::ostringstream & >(( std::ostringstream() << std::dec << x ) ).str()

std::string exec(const char* cmd) {

  FILE* pipe = popen(cmd, "r");
  if (!pipe)
    return "ERROR";

  char buffer[128];
  std::string result = "";
  while (!feof(pipe)) {
    if (fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }
  pclose(pipe);

  return result;
}

std::vector<std::string> explode( const std::string &delimiter, const std::string &str) {

  std::vector<std::string> arr;

  int strleng = str.length();
  int delleng = delimiter.length();
  if (delleng == 0)
    return arr; //no change

  int i = 0;
  int k = 0;
  while(i < strleng) {
    int j = 0;
    while ((i+j < strleng) && (j < delleng) && (str[i+j] == delimiter[j]))
      j++;
    if (j == delleng) {
      arr.push_back(str.substr(k, i-k));
      i += delleng;
      k = i;
    } else {
      i++;
    }
  }
  arr.push_back(str.substr(k, i-k));
  return arr;
}

// Command methods (callbacks)
std::string start(Telegram::TelegramBot *tg, Telegram::TCommandLine args) {

  return("I am a simple Bot, written in C++\nHave fun.");
}

std::string help(Telegram::TelegramBot *tg, Telegram::TCommandLine args) {

  std::map<std::string, Telegram::TCommand>::iterator it;
  std::string help_list = "Commands:\n";
  Telegram::TCommandMap command_map = tg->getCommandMap();

  for (it = command_map.begin(); it != command_map.end(); it++) {
    help_list = help_list + it->first + ": " + it->second.help_text + "\n";
  }

  return(help_list);
}

std::string whoami(Telegram::TelegramBot *tg, Telegram::TCommandLine args) {

  return("Your ID is " + SSTR(tg->getMessage()->getChat()->getId()));
}

std::string loadavg(Telegram::TelegramBot *tg, Telegram::TCommandLine args) {

  return(exec("cat /proc/loadavg"));
}

std::string proc(Telegram::TelegramBot *tg, Telegram::TCommandLine args) {

  return(exec("pstree"));
}

// main function
int main(int argc, char** argv) {
  std::vector<std::string> sExploded = explode(".", argv[0]);

  // @TODO: Check if we are called as .cgi!
  if ((sExploded.size() > 1) && (sExploded[1] == "cgi")) {
    // Do bot stuff!
    std::string line = "";
    while(std::cin) {
      std::string s;
      std::getline(std::cin, s);
      line = line + s;
    }
    Telegram::TelegramBot tg(BOT_TOKEN);

    // Set the commands
    Telegram::TCommand sc;
    sc.command = "/start";
    sc.callback = &start;
    sc.help_text = "This is the start command";
    tg.addCommand(sc);

    sc.command = "/help";
    sc.callback = &help;
    sc.help_text = "Shows you the commands this bot knows";
    tg.addCommand(sc);

    sc.command = "/whoami";
    sc.callback = &whoami;
    sc.help_text = "Tells you your Telegram ID";
    tg.addCommand(sc);

    sc.command = "/loadavg";
    sc.callback = &loadavg;
    sc.help_text = "Shows average load of the system this bot is running on";
    tg.addCommand(sc);

    sc.command = "/proc";
    sc.callback = &proc;
    sc.help_text = "Shows the process list of the system the bot is running on";
    tg.addCommand(sc);

    tg.processMessage(line);

  } else {
    // Process options
    std::string user_id = ""; // ID of the receiving user

    char c;
    while ((c = getopt(argc, argv, "u:")) != -1) {
      switch(c) {
      case 'u':
	user_id = (std::string)optarg;
	break;
      case ':':
	std::cerr << optopt << " without argument" << std::endl;
	break;
      }
    }

    if (user_id == "") {
      std::cerr << "No user ID given!" << std::endl;
      return 1;
    }

    // Read from stdin
    struct termios t;
    std::string s = "";
    if (tcgetattr(STDIN_FILENO, &t) < 0) {
      // If we have a text piped in, read from std::cin
      while(std::cin) {
	std::string line;
	std::getline(std::cin, line);
	s = s + line + "\n";
      }
      s.erase(s.end()-1);
    }

    if (s != "") {
      Telegram::TelegramBot tg(BOT_TOKEN);
      tg.sendMessage(s, user_id);
    }

  }

  return 0;
}
