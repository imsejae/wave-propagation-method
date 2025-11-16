#include <stdlib.h>
#include <stdio.h>
#include "setup.h"
#include "debug.h"
#include "assert.h"

// -------------------------------------------------------------------------- //
char* setup::ParseArguments(int argc, char**argv)
{
  // default output directory:
  char* outputdir=(char*)"output";

  // parse arguments
  if(argc>1)
    {
      for(int arg_idx=1; arg_idx<argc; arg_idx++)
        {
          if(argv[arg_idx][0]=='-')
            {
              // "-o" specifies which output directory to use.
              if(argv[arg_idx][1]=='o' && ++arg_idx < argc)
                { outputdir=argv[arg_idx]; }

              // "-d" specifies which debug level to use.   What are the legal
              // options that can be used here? (-DS)
              else if(argv[arg_idx][1]=='d' && ++arg_idx < argc)
                {
                  int debug_level;
                  int success = sscanf(argv[arg_idx],"%d",&debug_level);

                  if(success!=1)
                    { show_usage(argv); }
                }
              else
                { show_usage(argv); }
            }
          else
            { show_usage(argv); }
        }
    }

  return outputdir;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void setup::show_usage(char**argv)
{
  eprintf("\n"
          "usage: %s [-o outputdir]\n"
          "  -o outputdir : use outputdir as output directory [default: output]\n",
          argv[0]);
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void setup::PrintWelcome()
{
  printf("\n"
         "       ----------------------------------------------      \n"
         "       |    LeVeque's Wave Propagation Method       |      \n"
         "       ----------------------------------------------      \n"
         "       | Developed by the research group of         |      \n"
         "       |            James A. Rossmanith             |      \n"
         "       |            Iowa State University           |      \n"
         "       |            Department of Mathematics       |      \n"
         "       ----------------------------------------------      \n\n");
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void setup::RunScript(const char* outputdir)
{
  char command_str[1024];
  int numchars;
  int exit_status;

  // run startscript
  // to create output directory if it does not exist
  // and copy data files to output directory
  numchars = snprintf(command_str,
                      1024,
                      "if test -f startscript && test -x startscript;\n"
                      "then ./startscript %s\n"
                      "else ../../scripts/startscript %s\n"
                      "fi", outputdir, outputdir);

  assert_lt(numchars,1023);
  assert_gt(numchars,0);

  exit_status = system(command_str);
  if (exit_status!=0)
    {
      printf("\n");
      printf(" Error in RunStartScript.cpp\n");
      printf(" exit_status = %i\n",exit_status);
      printf("\n");
      exit(1);
    }
}
// -------------------------------------------------------------------------- //