// testbench.cpp

#include "testbench.h"

void testbench::source(){
  // Reset
  start = 1;
  wait(3);
  start = 0;
  // test pattern
  for(int times=0;times<2;times++){
    wait(4+times);// during counting reset the timer "before" count reaches 0
    start = 1;
    wait(1);
    start = 0;
  }

  for(int times=0;times<3;times++){
    wait(6+times);// during counting reset the timer "after" count reaches 0
    start = 1;
    wait(1);
    start = 0;
  }

}
