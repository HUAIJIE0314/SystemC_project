#include "systemc.h"
#include "time.h"

SC_MODULE(testbench){
  sc_in  <bool>   clock;
  sc_out <bool>   start;
  sc_in  <bool> timeout;

  //output to timer module
  void source();
  
  // input from timer momdule
  //void checkAns();
  //int cycle;

  SC_CTOR(testbench){
    SC_CTHREAD( source, clock.pos() );
    //SC_CTHREAD (checkAns, clock.pos() );
    //cycle = 0;
  }

};


