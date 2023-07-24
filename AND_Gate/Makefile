#Makefile
SYSTEMC_HOME=/usr/local/systemc-2.3.3
LIB_DIR=-L $(SYSTEMC_HOME)/lib-macosxarm
INC_DIR=-I $(SYSTEMC_HOME)/include
LIB=-l systemc

export $(SYSTEMC_HOME)


fileName=AND_Gate
Output=$(fileName).o

all:
	echo $(SYSTEMC_HOME)
	g++-13 $(addsuffix .cpp, $(fileName)) -o $(Output) $(LIB_DIR) $(INC_DIR) $(LIB)
	./$(Output)

clean:
	rm -rf $(Output)

run:
	./$(Output)

wave:
	open trace.vcd
