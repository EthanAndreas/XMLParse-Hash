TARGET = tests

CFLAGS = -O0 -Wall -Werror -g

INCLUDE_PATH = ../include

SRCDIR   = ../src
OBJDIR   = ../obj

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS0  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS = $(filter-out $(OBJDIR)/main.o,$(OBJECTS0))


tests: $(OBJECTS) obj/tests.o
	$(CC) -o $@ $^ $(CFLAGS)

cov: clean tests
	valgrind --leak-check=full -q ./$(TARGET)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

obj/tests.o: tests.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)


.PHONY: clean cov
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f obj/*.o
	rm -f tests
	rm -f $(BINDIR)/$(TARGET)