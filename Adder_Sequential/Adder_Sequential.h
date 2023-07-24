#include "systemc.h"

SC_MODULE(Adder_Sequential)     

{
  sc_in  <bool>            clk;// clock in
  sc_in  <bool>          rst_n;    
  sc_in  < sc_int<32> > input1;
  sc_in  < sc_int<32> > input2;
  sc_out < sc_int<32> >      F;                 

  void adder_main();

  SC_CTOR(Adder_Sequential){               
    SC_CTHREAD(adder_main, clk.pos());
    reset_signal_is(rst_n, false);
  }
 
};

void Adder_Sequential::adder_main(void){
  // reset
  F.write(0);
  wait();//wait for one cycle.
  // ========= Sequential logic =========
  while( true ){
    F.write( input1.read() + input2.read() );
    wait();//wait for one cycle.
  }
}

  