## ------------------------------------------------------------------------- ##
def plotsoln1():

    import os;
    import sys;
    import numpy as np;
    import matplotlib.pyplot as plt;
    import parse_parameters1 as pp1;

    curr_dir = os.path.abspath("./");
    sys.path.append(curr_dir);

    plots1_name = "plots1"
    plots1 = getattr(__import__(plots1_name, fromlist=[plots1_name]), plots1_name);

    output_directory = "output";

    ini_params = pp1.parse_ini_parameters(output_directory,
                                          output_directory+'/parameters.ini');

    numframes                = ini_params['numframes'];
    final_time               = ini_params['final_time'];
    cfl                      = ini_params['cfl'];
    max_number_of_time_steps = ini_params['max_number_of_time_steps'];
    order                    = ini_params['order'];
    Neqn                     = ini_params['Neqn'];
    Nx                       = ini_params['Nx'];
    xlow                     = ini_params['xlow'];
    xhigh                    = ini_params['xhigh'];

    # Grid information
    dx  = (xhigh-xlow)/np.float64(Nx);
    xc  = np.linspace( xlow+0.5*dx,   xhigh-0.5*dx,   Nx  );
    xl  = np.linspace( xlow,   xhigh,   Nx+1  );

    quit = -1;
    nplot = numframes;

    nf =  0;    # Frame number
    n1 = -1;    # Frame number

    print(" ------------------------------------------ ");
    print("     [type '-1', 'q', or 'quit' to quit] ");
    print("     [type 'all' for PDF of all frames] ");
    print(" ------------------------------------------ ");
    print(" ")

    plt.ion()
    while (nf!=-1):
        tmp2 = " Plot which frame ( 0 - " + str(nplot) + " )? ";
        nf   = input(tmp2);
        if(not nf):
            n1 = n1 + 1;
            nf = 0;
        elif(nf=="quit" or nf=="q"):
            nf = -1;
        elif(nf=="all"): #Useful for quickly making images of all plots
            nf = "all";
        else:
            nf = int(nf);
            n1 = nf;

        if( n1 > nplot ):
            print("");
            print(" End of plots " );
            print("");
            n1 = nplot;

        if( nf=="all" ):

            for n1 in range(0,nplot+1):
                ## ------------------------------------------------------------- ##
                # Solution -- soln
                # solution should be found in file
                #     output_directory/soln[n1].dat
                ## ------------------------------------------------------------- ##

                # file name (with directory thrown in the mix)
                soln_file   = output_directory + "/soln" + "%04d" % n1 + ".dat";

                # read in the coefficients from file
                time, qsoln = read_soln_file( Nx, Neqn, soln_file );

                # call detailed plotting function
                plots1(output_directory,        # directory where output data lives
                       True,                    # True ==> "show all frames at once"
                       n1,                      # current frame
                       ini_params,              # collection of all parameters read from "parameters.ini"
                       time,                    # current time
                       xc,                      # spatial mesh (cell centers)
                       xl,                      # spatial mesh (cell corners)
                       qsoln);                  # q solution

            nf = -1

        if( nf != -1 ):

            ## ------------------------------------------------------------- ##
            # Solution -- soln
            # solution should be found in file
            #     output_directory/soln[n1].dat
            ## ------------------------------------------------------------- ##

            # file name (with directory thrown in the mix)
            soln_file   = output_directory + "/soln" + "%04d" % n1 + ".dat";

            # read in the coefficients from file
            time, qsoln = read_soln_file( Nx, Neqn, soln_file );

            # call detailed plotting function
            plots1(output_directory,        # directory where output data lives
                   False,                   # True ==> "show all frames at once"
                   n1,                      # current frame
                   ini_params,              # collection of all parameters read from "parameters.ini"
                   time,                    # current time
                   xc,                      # spatial mesh (cell centers)
                   xl,                      # spatial mesh (cell corners)
                   qsoln);                  # q solution

    plt.ioff();
    print("");
## ------------------------------------------------------------------------- ##

#----------------------------------------------------------
def read_soln_file( Nx, Neqn, soln_file ):

    import string
    import numpy as np

    # open file
    Rqfile = open(soln_file,'r');

    # get time
    linestring      = Rqfile.readline();
    linelist        = linestring.split();
    time            = np.float64(linelist[0]);

    # store all Legendre coefficients in qtmp
    qsoln = np.zeros((Nx,Neqn), dtype=np.float64);
    for k in range (0,Neqn):
        for j in range (0,Nx):
            linestring  = Rqfile.readline();
            linelist    = linestring.split();
            qsoln[j,k]  = np.float64(linelist[0]);

    # close file
    Rqfile.close();

    # return time
    return time, qsoln
#----------------------------------------------------------

#----------------------------------------------------------
if __name__== '__main__':

    # Call the main 1D plotting routine
    plotsoln1();
#----------------------------------------------------------
