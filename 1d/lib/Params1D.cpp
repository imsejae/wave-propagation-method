#include "Params1D.h"
#include "IniDocument.h"
#include "dog_str.h"
#include "dog_math.h"
#include <stdlib.h>
#include <string>
#include <cstring>
#include "debug.h"
#include <stdio.h>
#include <cmath>

// -------------------------------------------------------------------------- //
// Constructor
Params1D::Params1D()
{
  is_initialized   =  false;
  verbosity        =  0;
  outputdir        =  NULL;
  numframes        =  -1;
  final_time       =  -1.0;
  cfl              =  -1.0;
  order            =  -1;
  Nx               =  -1;
  xlow             =  -1.0;
  xhigh            =  -2.0;
  left_bc          =  NULL;
  right_bc         =  NULL;
  Neqn             =  -1;
  max_number_of_time_steps = -1;
  use_limiter      = false;
  use_entropy_fix  = false;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Destructor
Params1D::~Params1D()
{
  free(outputdir);
  free(left_bc);
  free(right_bc);
  is_initialized = false;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Copy constructor
Params1D::Params1D(const Params1D& anotherParams1D)
{
  eprintf("\n  ERROR: Params1D copy constructor has been disabled.\n");
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
// Initialize routine: read "parameters.ini" file and read "Params1D" section
void Params1D::init(const char* outputdir_in)
{
  // if already initialized, don't do anything
  if(is_initialized)
    { return; }

  // copy output directory string
  outputdir = strdup(outputdir_in);

  IniDocument iniDoc;
  iniDoc.initFromFile("parameters.ini");
  std::string section_label = "Params1D";
  IniDocument::Section ini_sec = iniDoc[section_label];

  // list of the options with user-configurable defaults
  // (options not listed here are empty strings by default)
  std::vector<std::string> option_names_list;
  option_names_list.push_back("numframes"                );
  option_names_list.push_back("verbosity"                );
  option_names_list.push_back("final_time"               );
  option_names_list.push_back("cfl"                      );
  option_names_list.push_back("Neqn"                     );
  option_names_list.push_back("order"                    );
  option_names_list.push_back("Nx"                       );
  option_names_list.push_back("xlow"                     );
  option_names_list.push_back("xhigh"                    );
  option_names_list.push_back("left_bc"                  );
  option_names_list.push_back("right_bc"                 );
  option_names_list.push_back("Neqn"                     );
  option_names_list.push_back("max_number_of_time_steps" );
  option_names_list.push_back("use_limiter"              );
  option_names_list.push_back("use_entropy_fix"          );

  // read-in strings
  const std::string s_numframes         = ini_sec["numframes"        ];
  const std::string s_verbosity         = ini_sec["verbosity"        ];
  const std::string s_final_time        = ini_sec["final_time"       ];
  const std::string s_cfl               = ini_sec["cfl"              ];
  const std::string s_Neqn              = ini_sec["Neqn"             ];
  const std::string s_order             = ini_sec["order"            ];
  const std::string s_Nx                = ini_sec["Nx"               ];
  const std::string s_xlow              = ini_sec["xlow"             ];
  const std::string s_xhigh             = ini_sec["xhigh"            ];
  const std::string s_left_bc           = ini_sec["left_bc"          ];
  const std::string s_right_bc          = ini_sec["right_bc"         ];
  const std::string s_max_number_of_time_steps    = ini_sec["max_number_of_time_steps"   ];
  const std::string s_use_limiter       = ini_sec["use_limiter"      ];
  const std::string s_use_entropy_fix   = ini_sec["use_entropy_fix"  ];

  // convert to proper date types
  iniDoc.scanner("numframes",            s_numframes,            numframes            );
  iniDoc.scanner("verbosity",            s_verbosity,            verbosity            );
  iniDoc.scanner("final_time",           s_final_time,           final_time           );
  iniDoc.scanner("cfl",                  s_cfl,                  cfl                  );
  iniDoc.scanner("Neqn",                 s_Neqn,                 Neqn                 );
  iniDoc.scanner("order",                s_order,                order                );
  iniDoc.scanner("Nx",                   s_Nx,                   Nx                   );
  iniDoc.scanner("xlow",                 s_xlow,                 xlow                 );
  iniDoc.scanner("xhigh",                s_xhigh,                xhigh                );
  left_bc  = strdup(s_left_bc.c_str());
  right_bc = strdup(s_right_bc.c_str());
  iniDoc.scanner("max_number_of_time_steps",       s_max_number_of_time_steps,   max_number_of_time_steps       );
  int int_use_limiter;
  int int_use_entropy_fix;
  iniDoc.scanner("use_limiter",          s_use_limiter,          int_use_limiter      );
  iniDoc.scanner("use_entropy_fix",      s_use_entropy_fix,      int_use_entropy_fix  );
  if (int_use_limiter==1)     { use_limiter     = true; };
  if (int_use_entropy_fix==1) { use_entropy_fix = true; };

  // check parameters
  check_parameters();

  // set derived parameters
  set_derived_parameters();

  // report parameters
  report_parameters();

  // remember that Params1D has been initialized
  is_initialized = true;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void Params1D::check_parameters()
{
  if (numframes<1)
    { eprintf("\n numframes must be at least 1: numframes = %i.\n",numframes); }

  if (final_time<=0.0)
    { eprintf("\n final_time must be > 0.0: final_time = %22.15e.\n",final_time); }

  if (cfl<=0.0)
    { eprintf("\n cfl must be > 0.00: cfl = %22.15e.\n",cfl); }

  if (cfl>=0.99)
    { eprintf("\n cfl must be < 0.99: cfl = %22.15e.\n",cfl); }

  if (order<1)
    { eprintf("\n order must be at least 1: order = %i.\n",order); }

  if (Nx<1)
    { eprintf("\n Nx must be at least 1: Nx = %i.\n",Nx); }

  if (xlow>=xhigh)
    { eprintf("\n must have xlow < xhigh: (xlow,xhigh) = (%22.15e,%22.15e).\n",xlow,xhigh); }

  if (((!dog_str::str_eq(left_bc, "periodic"))&&
       (!dog_str::str_eq(left_bc, "extrapolation")))&&
       (!dog_str::str_eq(left_bc, "wall")))
    {
      eprintf("\n"
              " The left BC %s is not a valid choice.\n"
              " The available options are\n"
              "   1. extrapolation\n"
              "   2. periodic\n"
              "   3. wall\n",
              left_bc);
    }

  if (((!dog_str::str_eq(right_bc, "periodic"))&&
       (!dog_str::str_eq(right_bc, "extrapolation")))&&
       (!dog_str::str_eq(right_bc, "wall")))
    {
      eprintf("\n"
              " The right BC %s is not a valid choice.\n"
              " The available options are\n"
              "   1. extrapolation\n"
              "   2. periodic\n"
              "   3. wall\n",
              right_bc);
    }

  if ((dog_str::str_eq(right_bc, "periodic"))&&
      (!dog_str::str_eq(left_bc, "periodic")))
    {
      eprintf("\n"
              " If the right BC is perodic, then\n"
              " the left BC must also be periodic.\n"
              "    left_bc = %s\n"
              "   right_bc = %s\n",
              left_bc,
              right_bc);
    }

  if ((dog_str::str_eq(left_bc, "periodic"))&&
      (!dog_str::str_eq(right_bc, "periodic")))
    {
      eprintf("\n"
              " If the left BC is perodic, then\n"
              " the right BC must also be periodic.\n"
              "    left_bc = %s\n"
              "   right_bc = %s\n",
              left_bc,
              right_bc);
    }

  if (Neqn<1)
    { eprintf("\n Neqn must be at least 1: Neqn = %i.\n",Neqn); }

  if (max_number_of_time_steps<1)
    { eprintf("\n max_number_of_time_steps must be at least 1: max_number_of_time_steps = %i.\n",max_number_of_time_steps); }
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void Params1D::set_derived_parameters()
{
  dx  = (xhigh-xlow)/double(Nx);
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
void Params1D::report_parameters()
{
  // Output parameters to screen
  printf("   ============ parameters from [Params1D] ===========\n"
         "                  Number of Frames:  %d\n"
         "     Using Verbosity (1-yes, 0-no):  %d\n"
         "                        Final Time:  %f\n"
         "          max_number_of_time_steps:  %d\n"
         "                              Neqn:  %d\n"
         "                 Order of Accuracy:  %d\n"
         "                                Nx:  %d\n"
         "                              xlow:  %f\n"
         "                             xhigh:  %f\n"
         "                                dx:  %f\n"
         "           Left Boundary Condition:  %s\n"
         "          Right Boundary Condition:  %s\n"
         "                       use_limiter:  %s\n"
         "                   use_entropy_fix:  %s\n\n",
         numframes,
         verbosity,
         final_time,
         max_number_of_time_steps,
         Neqn,
         order,
         Nx,
         xlow,
         xhigh,
         dx,
         left_bc,
         right_bc,
         use_limiter ? "true" : "false",
         use_entropy_fix ? "true" : "false");
}
// -------------------------------------------------------------------------- //
