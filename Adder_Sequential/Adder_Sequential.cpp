#include "Adder_Sequential.h"


void Adder_Sequential::adder_main(){
  // reset
  F = 0;
  wait();//wait for one cycle.
  // ========= Sequential logic =========
  while( true ){
    F = input1.read() + input2.read();
    wait();//wait for one cycle.
  }
}

