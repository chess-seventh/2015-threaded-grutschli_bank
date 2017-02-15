HEADERS := $(wildcard *.h)
SOURCES := $(wildcard *.c)
OBJECTS := $(foreach file, $(addsuffix .o, $(basename $(SOURCES))), bin/$(file))


CFLAGS += -Wall -O3 -std=c99


all: bin/grutschli

clean:
	@echo "cleaning..."
	@rm -rf bin/ doc/ report/{resources,tmp}/

doc: doc/index.html

bin/grutschli: $(OBJECTS)
	@echo "linking $@..."
	@mkdir -p bin/
	@$(LINK.o) -o bin/grutschli $(OBJECTS) -lm -lrt -lpthread

bin/%.o: %.c $(HEADERS)
	@echo "compiling $<..."
	@mkdir -p bin/
	@$(COMPILE.c) -o $@ $<

doc/index.html: Doxyfile $(HEADERS) $(SOURCES)
	@echo "generating doc with doxygen..."
	@doxygen


.PHONY: all clean doc
