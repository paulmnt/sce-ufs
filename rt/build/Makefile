TARGET_ARCH = linux64
CC = g++

LIBS   =
LIBDIR =
INCDIR = ../include
TBDIR  = ../tb
TB     = --f $(TBDIR)/correlator-in.txt --phi 13 --verbose
CPPFLAGS = -I $(INCDIR) -Wall #-DINFO #-DDEBUG


TARGET = retime
VPATH := ../src
SRCS = parser.cpp algo_cp.cpp algo_wd.cpp algo_feas.cpp main.cpp \
	p1out.cpp algo_simplex.cpp p2out.cpp
HDRS = $(INCDIR)/p1out.h $(INCDIR)/sng.h $(INCDIR)/algo_wd.h \
	$(INCDIR)/algo_cp.h $(INCDIR)/algo_feas.h $(INCDIR)/parser.h \
	$(INCDIR)/algo_simplex.h $(INCDIR)/p2out.h
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

help: $(TARGET)
	./$(TARGET) --help

.PHONY: run clean log help
