TARGET_ARCH = linux64
CC = g++
CPPFLAGS = -Wall
#-DDEBUG

LIBS   =
LIBDIR =
INCDIR = -I../src
TBDIR  = ../tb
TB     = ../tb/f1.pla ../tb/g1.pla


TARGET = ufs
VPATH := ../src
SRCS = main.cpp tc_parser.cpp ufs.cpp tautology.cpp coversim.cpp printplas.cpp
HDRS = tc_parser.h ufs.h tautology.h coversim.h printplas.h
OBJS = $(SRCS:.cpp=.o)

.SUFFIXES: .cpp .cc .o
$(TARGET): $(OBJS)
	@$(CC) $(CPPFLAGS) ${INCDIR} ${LIBDIR} -o $@ $(OBJS) ${LIBS}

$(OBJS): $(HDRS)

.cpp.o:
	@$(CC) $(CPPFLAGS) ${INCDIR} -c $<

clean:
	@ rm -rf *.o $(TARGET) all-PLAs *.txt *log
	@ echo "CLEAN"

run: $(TARGET)
	@./$(TARGET) $(TB)

log: $(TARGET)
	./$(TARGET) $(TB) > run_log

test: $(TARGET)
	@(for i in 1 2 3 4 5 6 7 8; do 							\
		echo test $$i; 								\
		./$(TARGET) ../tb/f$$i.pla ../tb/g$$i.pla;				\
		diff recursionTree.txt ../tb/gold/tree_$$i.txt || echo TEST $$i FAILED; \
		diff print_sim.txt ../tb/gold/sim_$$i.txt || echo TEST $$i FAILED;	\
		echo ;									\
		echo test $$i with disjoint; 								\
		./$(TARGET) --multi_disjoint ../tb/f$$i.pla ../tb/g$$i.pla;		\
		diff recursionTree.txt ../tb/gold/tree_disjoint_$$i.txt || echo TEST $$i WITH --disjoint FAILED; \
		diff print_sim.txt ../tb/gold/sim_$$i.txt || echo TEST $$i FAILED;	\
		echo ;									\
	done > log)
	@ (grep 'FAILED' log && echo See log for details) || echo ALL TEST PASSED

help: $(TARGET)
	./$(TARGET) --help

.PHONY: run clean log test help
