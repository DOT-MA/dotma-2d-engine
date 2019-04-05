UNAME			= $(shell uname)
OS				=

# executable name
TARGET			:= output.out

# compiler to use
CC				:= gcc

# compiler flags
CFLAGS   		:= -std=c99 -Wall -pedantic -g

LINKER   		:= gcc

# linking flags
LFLAGS			:= -Isrc/include -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# directories
SRCDIR   		:= src
INCDIR			:= include
OBJDIR			:= obj
BINDIR			:= bin

# helpers
rm				:= rm -rf
mkdir			:= mkdir -p
find			:= find
findc			= $(find) $(SRCDIR)/ -type f -name *.c
findh			= $(find) $(INCDIR)/ -type f -name *.h

# determine os
ifeq ($(UNAME), Linux)
OS				= UNIX
else ifeq ($(UNAME), MINGW32_NT-6.2)
OS				= WIN
else ifeq ($(UNAME), Darwin)
OS				= UNIX
else
$(info "Operating system not supported at this point in time.")
exit 0
endif

# override if on windows
ifeq ($(OS), WIN)
SHELL 			:= powershell
TARGET			:= output.exe
# where is the find command located on your windows machine?
find			:= C:\MinGW\msys\1.0\bin\find.exe
LFLAGS			:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -Isrc/include
$(info Enviroment: windows)
else
$(info Enviroment: unix)
endif

# source listings
SOURCES  		:= $(shell $(findc))
INCLUDES 		:= $(shell $(findh))

# reset shell
SHELL 			:= sh

# What are my objects?
OBJECTS  		:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# make subfolders if they do not already exist.
$(shell $(mkdir) $(OBJDIR))
$(shell $(mkdir) $(OBJDIR)/Components)
$(shell $(mkdir) $(OBJDIR)/Entities)
$(shell $(mkdir) $(OBJDIR)/Managers)
$(shell $(mkdir) $(OBJDIR)/Rendering)
$(shell $(mkdir) $(OBJDIR)/Scenes)
$(shell $(mkdir) $(OBJDIR)/Utilities)

all: $(OBJECTS) $(BINDIR)/$(TARGET)

# are we making a debug build?
debug: CFLAGS += -DDEBUG -g 
debug: TARGET = debug.out
debug: $(OBJECTS) $(BINDIR)/$(TARGET)

# compile objects
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	$(info Compiled $< successfully!)


# link objects
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	$(info Linking complete!)


.PHONY:	clean

# clean all building materials.
clean:
	@$(rm) $(OBJDIR)
	@echo "Cleanup complete!"
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
	