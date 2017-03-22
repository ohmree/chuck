CC     = gcc# --enable-checking
CFLAGS = -Wall -Wextra -ggdb3 -O0 -std=gnu11# -v -da -Q #-MD
#CURL   := $(shell curl-config --cflags --libs)
LIBS   = -lncurses -lm -lcjson -lneon #$(CURL)
.PHONY = all clean

ifeq ($(GPROF),yes)
CFLAGS += -pg
endif

ifeq ($(GCOV),yes)
CFLAGS += -O0 -DNDEBUG -fno-elide-constructors -fno-inline -fprofile-arcs -ftest-coverage
endif

SRCS = $(wildcard *.c)
#BIN  = $(SRCS:%.c:%.o)
all: foo
	$(CC) $(CFLAGS) $(SRCS) -Iinclude -o chuck $(LIBS)

foo: $(SRCS:%.c:%.o)

clean:
	$(RM) -f foo core gmon.out *.o *.d *.gcno *.gcov *.gcda

#-include *.d