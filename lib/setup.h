#ifndef _SETUP_H_
#define _SETUP_H_

namespace setup
{
  char* ParseArguments(int argc, char**argv);
  void show_usage(char**argv);
  void PrintWelcome();
  void RunScript(const char* outputdir);
}

#endif
