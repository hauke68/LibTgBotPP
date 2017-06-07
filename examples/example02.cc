/**
 *
 * This is a simple Telegram client that can echo a message, piped to its
 * binary and to set your web hook.
 *
 * If you want to use this example to send your web hook to Telegram's
 * API, change BOT_TOKEN according to your needs and your web server!
 *
 * Example:
 * BOT_TOKEN: Your token given by Telegram's Bot Father!
 *
 * To compile do:
 * g++ -c -o example02.o -I/usr/include/jsoncpp example02.cc
 * g++ -o example02 example02.o -ltgbotpp
 *
 * Run:
 * echo "Your message" | ./example02  -u <your user id>
 *
 * To set your web hook to Telegram's network:
 * ./example02 -w
 *
 * To send a photo to a user or group:
 * ./example02 -p file:///path/to/pic.jpg -u <user id>
 */

#include <Telegram/TelegramBot.h>

#include <sstream>
#include <string>

#include <termios.h>
#include <unistd.h>

#define WEBHOOK_URL "https://your-domain/cgi-bin/bot.cgi"
#define BOT_TOKEN "your secret token"

// main function
int main(int argc, char** argv) {

	// Process options
	std::string user_id = ""; // ID of the receiving user
	std::string filename = ""; // File name of file to  be sent

	Telegram::TelegramBot tg(BOT_TOKEN);

#ifdef __arm__
	int c;
#else
	char c;
#endif

	while ((c = getopt(argc, argv, "wu:p:")) != -1) {
		switch(c) {
			case 'u':
				user_id = (std::string)optarg;
				break;
			case 'w':
				tg.setWebhook(WEBHOOK_URL);
				return 0;
				break; // Never reached
			case 'p':
				filename = (std::string)optarg;
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

	if (filename != "") {
		// Currently only photos are supported
		tg.sendPhoto(filename, user_id);
		return 0;
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
		tg.sendMessage(s, user_id); // Send the message to the user
	}

	return 0;
}
