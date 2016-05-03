#ifndef __STD_H__
#define __STD_H__

#include <ios>
#include <sstream>
#include <string>
#include <vector>

// Makro(s)
#define SSTR( x ) static_cast< std::ostringstream & >(( std::ostringstream() << std::dec << x ) ).str()

typedef unsigned long long int uint64;

uint64 stoi(std::string);
std::string itos(uint64);
std::string currentDate();
std::vector<std::string> split(const std::string &text, char sep = ' ');
float stof(std::string);
std::string trim(const std::string&);
std::string gethome();
void Log(std::string);

#endif
