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
findc			:= find $(SRCDIR)/ -type f -name *.c
findh			:= find $(INCDIR)/ -type f -name *.h

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
findc			:= Get-ChildItem -Path src/ -Filter *.c -Recurse -ErrorAction SilentlyContinue -Force | % { $_.name } | foreach-object ` {"$(SRCDIR)/" + $_}
findh			:= Get-ChildItem -Path src/ -Filter *.h -Recurse -ErrorAction SilentlyContinue -Force | % { $_.name } | foreach-object ` {"$(INCDIR)/" + $_}
LFLAGS			:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -Isrc/include
$(info Building for windows)
else
$(info Building for unix)
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
$(shell $(mkdir) $(OBJDIR)/Entities)
$(shell $(mkdir) $(OBJDIR)/Components)
$(shell $(mkdir) $(OBJDIR)/Scenes)

# build objects
$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	$(info Linking complete!)

# compile executable
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	$(info Compiled $< successfully!)

# clean all building materials.
.PHONY:	clean

# are we making a debug build?
debug:
	CFLAGS += -DDEBUG -g


clean:
	@$(rm) $(OBJDIR)
	@echo "Cleanup complete!"
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"