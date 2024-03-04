// testbench.cpp

#include "testbench.h"

void testbench::source(){
  // Reset
  start.write(1);
  wait(3);
  start.write(0);
  // test pattern
  for(int times=0;times<2;times++){
    wait(4+times);// wait for counter coutning to "1"
    start.write(1);
    wait(1);
    start.write(0);
  }

  for(int times=0;times<3;times++){
    wait(6+times);// wait for counter coutning to "1"
    start.write(1);
    wait(1);
    start.write(0);
  }

}


// void testbench::checkAns(){
//   cout << endl << endl;
//   while( true ){
//     cycle ++;
//     cout << "cycle = " << cycle << ", start = " << start << ", timeout = " << timeout << endl;
//     wait(1);
//   }
// }




