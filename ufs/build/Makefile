TARGET_ARCH = linux64
CC = g++
CPPFLAGS = -Wall -DDEBUG

LIBS   =
LIBDIR =
INCDIR = -I../src
TBDIR  = ../tb
TBFLAGS ?= 

TARGET = ufs
VPATH := ../src
SRCS = main.cpp tc_parser.cpp ufs.cpp tautology.cpp coversim.cpp
HDRS = tc_parser.h ufs.h tautology.h coversim.h
OBJS = $(SRCS:.cpp=.o)

.SUFFIXES: .cpp .cc .o
$(TARGET): $(OBJS)
	@$(CC) $(CPPFLAGS) ${INCDIR} ${LIBDIR} -o $@ $(OBJS) ${LIBS}

$(OBJS): $(HDRS)

.cpp.o:
	@$(CC) $(CPPFLAGS) ${INCDIR} -c $<

clean:
	@ rm -rf *.o $(TARGET)
	@ echo "CLEAN"

run: $(TARGET)
	@./$(TARGET) $(TBFLAGS)

log: $(TARGET)
	./$(TARGET) > log

.PHONY: run clean log
