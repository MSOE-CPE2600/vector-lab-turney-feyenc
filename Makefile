CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= main.c repl.c storage.c vector_math.c
OBJECTS= $(SOURCES:.c=.o)
EXECUTABLE= Lab5

all: $(SOURCES) $(EXECUTABLE)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d