# Makefile for AG0700 projects.

# Use the ARM C++ toolchain.
CC = arm-eabi-g++
OBJCOPY = arm-eabi-objcopy
INC = -I .\\libs

# Compiler options:
# -g      Enable debugging symbols
# -O3     Full compiler optimisations
# -Wall   Enable all warnings
# -S 	  Generate assembly
#CFLAGS = -g -O3 -Wall
CGLAGS = -g -O3 -Wall

# Architecture options for the GBA.
#MODEL = -mthumb -mthumb-interwork -specs=gba_mb.specs

## USING CART SPEC!
MODEL = -mthumb -mthumb-interwork -specs=gba.specs

# The name of the program to build.
TARGET = main

# The object files to link into the final program.
# The rules below will build foo.o from foo.cpp automatically.

# tonclib stuff is pre-compiled.


OBJECTS = \
	$(TARGET).o \
	gameobjects.o \
	player.o \
	eyebots.o \
	disk.o \
	securitycam.o \
	state_menu.o \
	state_game.o \
	state_pause.o \
	state_win.o \
	title_screen.o \
	prototype_gfx.o \
	pausestuff.o \
	shadowtiles_simple.o \
	status_good.o \
	status_bad.o \
	status_seen.o \
	status_dead.o \
	business.o \
	visioncone.o \
	gfx_eyebots.o \
	level_data.o \
	levels.o \
	tonchelper.o \
	libtonc.a

# The default target to make if none is specified.
all: $(TARGET).gba

# Convert a .elf file into a .gba ROM image.
%.gba: %.elf
	$(OBJCOPY) -O binary $< $@
	gbafix $@

# Link .o files together to produce a .elf file.
$(TARGET).elf: $(OBJECTS)
	$(CC) $(MODEL) -o $@ $^ -lm

# Compile a .cpp file into a .o file.
%.o: %.cpp
	$(CC) $(CFLAGS) $(INC) $(MODEL) -c $<

# Run the ROM image using VBA.
run: $(TARGET).gba
	vba $(TARGET).gba

# Run a program with a different value of TARGET.
# (This lets you have multiple GBA programs in the same directory;
# if you have foo.cpp, you can compile and run it with "make run-foo".)
run-%:
	@$(MAKE) run TARGET=$*

# Remove all the compiled files.	
clean:
	rm -f *.gba *.elf *.o *.s depend.mk

# Automatically extract dependencies from .cpp files.
# Invoking the compiler with -MM below makes it scan the source files and
# write out Makefile-style rules saying which other files they depend upon;
# we then include that file.
-include depend.mk
depend.mk: *.cpp 
	$(CC) -MM *.cpp >depend.mk
