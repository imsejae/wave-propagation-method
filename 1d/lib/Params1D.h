#ifndef _PARAMS1D_H_
#define _PARAMS1D_H_

class Params1D
{
  public:
    // Constructor
    Params1D();

    // Destructor
    ~Params1D();

    // Copy-constructor
    Params1D(const Params1D& anotherParams1D);

    // Initializer function that scans [Params1D] section of parameters.ini
    void init(const char* outputdir);

  private:
    void check_parameters();
    void report_parameters();
    void set_derived_parameters();

  public:
    const bool    get_is_initialized()          const { return is_initialized;          };
    const int     get_verbosity()               const { return verbosity;               };
    const int     get_numframes()               const { return numframes;               };
    const double  get_final_time()              const { return final_time;              };
    const double  get_cfl()                     const { return cfl;                     };
    const int     get_order()                   const { return order;                   };
    const int     get_Nx()                      const { return Nx;                      };
    const double  get_xlow()                    const { return xlow;                    };
    const double  get_xhigh()                   const { return xhigh;                   };
    const char*   get_left_bc()                 const { return left_bc;                 };
    const char*   get_right_bc()                const { return right_bc;                };
    const double  get_dx()                      const { return dx;                      };
    const int     get_Neqn()                    const { return Neqn;                    };
    const int     get_max_number_of_time_steps()const { return max_number_of_time_steps;};

  private:
    // parameters
    bool    is_initialized;
    int     verbosity;
    char*   outputdir;
    int     numframes;
    double  final_time;
    double  cfl;
    int     order;
    int     Nx;
    double  xlow;
    double  xhigh;
    char*   left_bc;
    char*   right_bc;
    int     Neqn;
    int     max_number_of_time_steps;
    // derived parameters
    double dx;
};

#endif