# determine os
UNAME			= $(shell uname)
OS				= 
ifeq ($(UNAME), Linux)
OS				= Linux
else ifeq ($(UNAME), Windows 10)
OS				= Windows
else ifeq ($(UNAME), Darwin)
OS				= MacOS
else
@echo "Operating system not supported at this point in time."
exit 0
endif

@echo $(UNAME)

# executable name
TARGET			= output.out

# compiler to use
CC				= gcc

# compiler flags
CFLAGS   		= -std=c99 -Wall -g

LINKER   		= gcc

# linking flags
LFLAGS			= -Isrc/include -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# directories
SRCDIR   = src
INCDIR   = include
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(shell find $(SRCDIR)/ -type f -name *.c)
INCLUDES := $(shell find $(INCDIR)/ -type f -name *.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -rf


$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(OBJDIR)/Entities)
$(shell mkdir -p $(OBJDIR)/Components)
$(shell mkdir -p $(OBJDIR)/Scenes)
$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo $(SOURCES) $(INCLUDES) $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)
	@echo "Cleanup complete!"
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
