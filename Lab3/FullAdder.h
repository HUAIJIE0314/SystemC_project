#ifndef FULLADDER_H
#define FULLADDER_H

#include "systemc.h"
#include "HalfAdder.h"

SC_MODULE(FullAdder){

  sc_in  <bool> A;
  sc_in  <bool> B;
  sc_in  <bool> Cin;
  sc_out <bool> Sum;
  sc_out <bool> Cout;     

  void xorFunc(void);
  void trace(sc_trace_file* );

  HalfAdder*  HalfAdder1;
  HalfAdder*  HalfAdder2;

  sc_signal <bool> s1;
  sc_signal <bool> c1;
  sc_signal <bool> c2;

  SC_CTOR(FullAdder){

    SC_METHOD(xorFunc);            
    sensitive << c1 << c2;

    HalfAdder1 = new HalfAdder("HalfAdder1");
    HalfAdder1->A(A);
    HalfAdder1->B(B);
    HalfAdder1->Sum(s1);
    HalfAdder1->Carry(c1);

    HalfAdder2 = new HalfAdder("HalfAdder2");
    HalfAdder2->A(s1);
    HalfAdder2->B(Cin);
    HalfAdder2->Sum(Sum);
    HalfAdder2->Carry(c2);

  }

};

#endif // FULLADDER_H