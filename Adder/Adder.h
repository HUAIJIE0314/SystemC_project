#include "systemc.h"

SC_MODULE(Adder)                // declare AND_Gate sc_module

{

  sc_in  < sc_int<32> > input1;
  sc_in  < sc_int<32> > input2;
  sc_out < sc_int<32> > F;     

  SC_CTOR(Adder){               // constructor for AND_Gate
    SC_METHOD(adder_main);            
    sensitive << input1 << input2; // sensitivity list
  }

  void adder_main(void){
    F.write( (input1.read() + input2.read()) );
  }

};