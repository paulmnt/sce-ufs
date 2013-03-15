TARGET_ARCH = linux64
CC = g++
CFLAGS = -Wall

LIBS   =
LIBDIR =
INCDIR = -I../src
TBDIR  = ../tb
TB ?= t1.txt
TBFLAGS ?= 

TARGET = ufs
VPATH := ../src
SRCS = main.cpp tc_parser.cpp
HDRS = tc_parser.h ufs.h
OBJS = $(SRCS:.cpp=.o)

.SUFFIXES: .cpp .cc .o
$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) ${INCDIR} ${LIBDIR} -o $@ $(OBJS) ${LIBS}

$(OBJS): $(HDRS)

.cpp.o:
	@$(CC) $(CFLAGS) ${INCDIR} -c $<

clean:
	@ rm -rf *.o $(TARGET)
	@ echo "CLEAN"

run: $(TARGET)
	@echo RUNNING TEST $(TB)
	@./$(TARGET) $(TBFLAGS) $(TBDIR)/$(TB)

log: $(TARGET)
	./$(TARGET) > log

.PHONY: run clean log
