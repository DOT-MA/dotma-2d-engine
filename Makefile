# copied from stack overflow lol cant
# remember where but not original makefile

# executable name
TARGET   = output

# compiler to use
CC       = gcc

# compiler flags here
CFLAGS   = -std=c99 -Wall

LINKER   = gcc

# linking flags here
LFLAGS   = -Isrc/include -lSDL2 -lSDL2_image

# directories
SRCDIR   = src
INCDIR   = include
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo $(SOURCES) $(INCLUDES) $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"