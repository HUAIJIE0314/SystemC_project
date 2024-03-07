#include "systemc.h"
#include "time.h"

SC_MODULE(testbench){
  sc_in  <bool>   clock;
  sc_out <bool>   start;
  sc_in  <bool> timeout;

  //output to timer module
  void source();
  
  SC_CTOR(testbench){
    SC_CTHREAD( source, clock.pos() );
    
  }

};


