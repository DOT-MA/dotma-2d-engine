# determine os
UNAME			= $(shell uname)
OS				= 
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

# executable name
TARGET			:= output.out

# compiler to use
CC				:= gcc

# compiler flags
CFLAGS   		:= -std=c99 -Wall -g

LINKER   		:= gcc

# linking flags
LFLAGS			:= -Isrc/include -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# helpers
rm				:= rm -rf
mkdir			:= mkdir -p 
findc			:= shell find $(SRCDIR)/ -type f -name *.c
findh			:= shell find $(SRCDIR)/ -type f -name *.h

# directories
SRCDIR   		:= src
INCDIR			:= include
OBJDIR			:= obj
BINDIR			:= bin

# make subfolders if they do not already exist.
$(shell $(mkdir) $(OBJDIR))
$(shell $(mkdir) $(OBJDIR)/Entities)
$(shell $(mkdir) $(OBJDIR)/Components)
$(shell $(mkdir) $(OBJDIR)/Scenes)

# override if on windows
ifeq ($(OS), WIN)
SHELL 			:= powershell
findc			= Get-ChildItem -Path src/ -Filter *.c -Recurse -ErrorAction SilentlyContinue -Force | % { $_.name } | foreach-object ` {"$(SRCDIR)/" + $_}
findh			= Get-ChildItem -Path src/ -Filter *.h -Recurse -ErrorAction SilentlyContinue -Force | % { $_.name } | foreach-object ` {"$(INCDIR)/" + $_}
LFLAGS			:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -Isrc/include
$(info Building for windows)
else
$(info Building for unix)
endif

# source listings
SOURCES  		:= $($(findc))
INCLUDES 		:= $($(findh))
SHELL 			:= sh
OBJECTS  		:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


# build
$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo $(SOURCES) $(INCLUDES) $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

# clean all building materials.
clean:
	@$(rm) $(OBJDIR)
	@echo "Cleanup complete!"
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
