#include "systemc.h"
/*
class AND_Gate : public sc_module{ 
public:
  AND_Gate(sc_module_name name) : sc_module(name){ 
    cout<<"Hello, SystemC!"<<endl; 
  }
};
*/

SC_MODULE(AND_Gate)                // declare AND_Gate sc_module

{

  sc_in  <bool> input1, input2;     // input signal ports
  sc_out <bool> F;                 // output signal ports

  SC_CTOR(AND_Gate){               // constructor for AND_Gate
    SC_METHOD(do_and2);            
    sensitive << input1 << input2; // sensitivity list
  }

  void do_and2(){                  // boolean function
    F.write( (input1.read() && input2.read()) );    
  }

};