// testbench.cpp

#include "testbench.h"
#include <bitset>
#include <iostream>
#include <iomanip>

using namespace std;
#define patternNum 100

void testbench::source(){
	// random seed
	srand( time(NULL) );
	// Reset
	rst_n = 0;
	enable = 0;
	data_i = 0x00;
	tx_data = 0x00;

	wait(3);
	rst_n = 1;

	for(int patternIdx=0;patternIdx<patternNum;patternIdx++){
		// TX test pattern
		tx_data = rand() % 256;
		enable = 1;
		data_i = tx_data;
		wait();
		enable = 0;
		// wait one baud rate period (HIGH)
		wait(10 * 10416, SC_NS);
		// wait half baud rate period (half period of first bit)
		wait(10 * 10416 / 2, SC_NS);
		//cout << hex << " ======= TX data:" << tx_data << " =======" << endl;
		for(int idx=0;idx<8;idx++){
		  rx_data = (rx_data >> 1) | (uart_txd.read() << 7);
		  //cout << "current bit : " << uart_txd.read() << ", " << (uart_txd.read() << 8) << ", " << bitset<8>(rx_data) << endl;
		  //cout << "current bit : " << uart_txd.read() << endl;
		  for(int baud=0;baud<10416;baud++){
			wait();
		  }
		}
		wait(10 * 10416 / 1.5, SC_NS);
		//cout << hex << " ======= RX data:" << rx_data << " =======" << endl;

		if(tx_data == rx_data){
			correctNum++;
			cout << "No." << setw(3) << patternIdx << " PASS !" << endl;
		}
	}
	//print the test result
	if(correctNum == patternNum){
		cout << endl;
		cout << "        ****************************   " << endl;
		cout << "        **                        **   " << endl;
		cout << "        **  Congratulations !!    **   " << endl;
		cout << "        **                        **   " << endl;
		cout << "        **  Simulation PASS!!     **   " << endl;
		cout << "        **                        **   " << endl;
		cout << "        ****************************   " << endl;
		cout << endl;
	}
	else{
		cout << endl;
		cout << "        ****************************   " << endl;
		cout << "        **                        **   " << endl;
		cout << "        **  OOPS!!                **   " << endl;
		cout << "        **                        **   " << endl;
		cout << "        **  Simulation Failed!!   **   " << endl;
		cout << "        **                        **   " << endl;
		cout << "        ****************************   " << endl;
		cout << "         Correct " << correctNum << " / " << patternNum  << endl;
		cout << endl;
	}
	sc_stop();
}



void testbench::trace(sc_trace_file* tf){
    sc_trace(tf,      rx_data, "   rx_data");
    sc_trace(tf,      tx_data, "   tx_data");
    sc_trace(tf,   correctNum, "correctNum");
}