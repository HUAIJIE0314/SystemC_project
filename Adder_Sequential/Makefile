# Makefile
SYSTEMC_DIR = /usr/local/systemc-2.3.4
PROJECT     = Adder_Sequential
BUILDFLAGS  = -g3
CXX         = g++

INCFLAGS    = -I. -I${SYSTEMC_DIR}/include
LDFLAGS     = -L${SYSTEMC_DIR}/lib-linux64 -lsystemc -lm

SRC_CPPHEAD = Adder_Sequential
SRC_CPP     =
HEADERS     =
MAIN        = main.cpp
OBJECTS     = $(SRC_CPPHEAD:=.o) $(SRC_CPP:cpp=o)

EXE = $(PROJECT)

all: $(EXE)

$(EXE): $(MAIN) $(OBJECTS) $(HEADERS)
	@echo "$@ building..."
	$(CXX) $(INCFLAGS) $(MAIN) $(OBJECTS) $(LDFLAGS) -o $@
	@echo ""
	@echo "$@ build done successfully..."
	@echo ""
	./$(PROJECT)

%.o:%.cpp %.h
	@echo "Compiling $< ..."
	$(CXX) -c $< $(INCFLAGS)

wave:
	gtkwave waveform.vcd

clean:
	rm -f $(EXE)
	rm -f *.o












# $(CXX) $(INCFLAGS) $(MAIN) $(OBJECTS) $(LDFLAGS) -o $@
# $(CXX) $(INCFLAGS) $(MAIN) $(LDFLAGS) -o $@
# $(CXX) $(MAIN) -o $(Output) $(LDFLAGS) $(INCFLAGS) $(LIB)
# $(CXX) $(MAIN) -o $@ $(LDFLAGS) $(INCFLAGS) $(LIB)
# ==================================== OLD version =======================================



#INC_DIR     = -I $(SYSTEMC_DIR)/include
#LIB_DIR     = -L $(SYSTEMC_DIR)/lib-macosxarm



# EXE = $(PROJECT)
# 
# export $(SYSTEMC_DIR)
# 
# 
# fileName=main
# Output=$(fileName).o
# 
# all:
# 	echo $(SYSTEMC_DIR)
# 	g++-13 $(addsuffix .cpp, $(fileName)) -o $(Output) $(LIB_DIR) $(INC_DIR) $(LIB)
# 	./$(Output)
# 
# clean:
# 	rm -rf $(Output)
# 
# run:
# 	./$(Output)
# 
# wave:
# 	open trace.vcd




