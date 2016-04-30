#include "Telegram/std.h"

#include <pwd.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <sstream>

uint64 stoi(std::string st) {

  uint64 ret;

  if (st == "") {
    st = "0";
  }

  std::istringstream convert(st);
  convert >> ret;

  return(ret);
}

std::string itos(uint64 i) {

  return(static_cast<std::ostringstream*>(&(std::ostringstream() << i))->str());
}

std::string currentDate() {

  time_t now = time(0);
  struct tm tstruct;
  char buf[32];
  tstruct = *localtime(&now);

  strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

  return(buf);
}

std::vector<std::string> split(const std::string &text, char sep) {

  std::vector<std::string> tokens;
  int start = 0, end = 0;
  while ((int)(end = text.find(sep, start)) != (int)std::string::npos) {
    std::string temp = text.substr(start, end - start);
    if(temp != "")
      tokens.push_back(temp);
    start = end + 1;
  }
  std::string temp=text.substr(start);
  if(temp != "")
    tokens.push_back(temp);

  return tokens;
}

float stof(std::string st) {

  // Conver , to . first
  replace(st.begin(), st.end(), ',', '.');

  return(atof(st.c_str()));
}

std::string trim(const std::string &s) {

  std::string::const_iterator it = s.begin();
  while (it != s.end() && isspace(*it))
    it++;

  std::string::const_reverse_iterator rit = s.rbegin();
  while (rit.base() != it && isspace(*rit))
    rit++;

  return std::string(it, rit.base());
}

std::string gethome() {

  std::string homedir = getenv("HOME");
  if (homedir == "") {
    homedir = getpwuid(getuid())->pw_dir;
  }

  return(homedir);
}

// A simple logger
void Log(std::string msg) {

  std::ofstream datei;
  datei.open("/tmp/bot.log", std::ios::out | std::ios::app);
  datei << "Msg: " << msg << std::endl;
  datei.close();
}
