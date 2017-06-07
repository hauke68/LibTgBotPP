# LibTgBotPP
A simple Telegram Bot C++ library

# Requirements

To compile, you just need a C++-Compiler and CMake and some libraries:
* libstdc++-dev
* libcurlpp-dev
* libjsoncpp-dev

and - of course - their dependencies.

To compile and install the lib:
* mkdir build
* cd build/
* cmake ../
* make
* sudo make install
* sudo ldconfig

To use the library, you need:
* libcurlpp
* libjsoncpp

You can use example01.cc to start your own bot or CGI script.

Do not forget to send your web hook URL to Telegram's API network,
otherwise, you cannot send commands to your bot.

In case you build a CGI script, do not forget to add a valid
certificate to your web server, because your bot is only called via
HTTPS!
