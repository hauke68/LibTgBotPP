#include "exec.h"

#include <iostream>
#include <stdio.h>

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
