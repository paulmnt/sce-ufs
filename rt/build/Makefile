TARGET_ARCH = linux64
CC = g++

LIBS   =
LIBDIR =
INCDIR = ../include
TBDIR  = ../tb
TB     = --f $(TBDIR)/correlator-in.txt
CPPFLAGS = -I $(INCDIR) -Wall #-DDEBUG #-DINFO


TARGET = retime
VPATH := ../src
SRCS = parser.cpp algo_cp.cpp algo_wd.cpp algo_feas.cpp main.cpp \
	p1out.cpp
HDRS = $(INCDIR)/p1out.h $(INCDIR)/sng.h $(INCDIR)/algo_wd.h \
	$(INCDIR)/algo_cp.h $(INCDIR)/algo_feas.h $(INCDIR)/parser.h
OBJS = $(SRCS:.cpp=.o)

.SUFFIXES: .cpp .cc .o
$(TARGET): $(OBJS)
	@$(CC) $(CPPFLAGS) ${LIBDIR} -o $@ $(OBJS) ${LIBS}
	@rm -rf *.o

$(OBJS): $(HDRS)

.cpp.o:
	@$(CC) $(CPPFLAGS) -c $<

clean:
	@ rm -rf *.o $(TARGET) *.txt *log
	@ echo "CLEAN"

run: $(TARGET)
	@./$(TARGET) $(TB)

log: $(TARGET)
	./$(TARGET) $(TB) > run_log

test: $(TARGET)
#	@(for i in 1 2 3 4 5 6 7 8; do 							\
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
#	@ (grep 'FAILED' log && echo See log for details) || echo ALL TEST PASSED

help: $(TARGET)
	./$(TARGET) --help

.PHONY: run clean log test help
