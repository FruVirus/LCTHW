# Predefined variables:
# $< : replaced by first prerequisite of the rule
# $^ : replaced by the list of all prerequisites of the rule
# $@ : replaced by the target name
# $? : list of prerequisites that are newer than the target (if target doesn't exist, they are all considered newer)
# $(RM) : replaced with the system removal commands

# CFLAGS are either the name of environment variables or of Makefile variables that can be set to specify additional switches to be passed to a compiler in the process of building computer software.
# -g : Produce debugging information in the operating system's native format. GDB can work with this debugging information.
# -Wall: This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.
# -Wextra: This enables some extra warning flags that are not enabled by -Wall.
# -rdynamic: Pass the flag -export-dynamic to the ELF linker, on targets that support it. This instructs the linker to add all symbols, not only used ones, to the dynamic symbol table. This option is needed for some uses of 'dlopenj' or to allow obtaining backtraces from within a program.
# -O2: Optimize even more. GCC performs nearly all supported optimizations that do not involve a space-speed tradeoff. As compared to -o, this option increases both compilation time and the performance of the generated code.
# fPIC: 'for Position Independent Code', passed to create shared object libraries
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)

# Options used when linking a library.
# 'ldl' is the dynamic linking library.
LIBS=-ldl $(OPTLIBS)

# The optional variable 'PREFIX' will only have its associate value if the person running Makefile didn't already give a 'PREFIX' setting. That's what the '?=' does.
PREFIX?=/usr/local

# Wildcard expansion happens automatically in rules. But wilcard expansion does not normally take place when a variable is set, or inside the arguments of a function. If you want to do wildcard expansion in such places, you need to use the wildcard function 'wildcard'. '**' matches any level of subdirectories.
SOURCES=$(wildcard src/**/*.c src/*.c)
# $(patsubst pattern,replacement,text) finds whitespace-separated words in 'text' that match 'pattern' and replaces them with 'replacement'.
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libfru.a # Archive libraries (statically linked when you compile your program so if there's any change in the library, you need to compile and build your code again)
SO_TARGET=$(patsubst %.a,%.so,$(TARGET)) # Shared object (linked during runtime after creation of .o file so if there's any change in .so files, you don't need to recompile your main program; however, the main program needs to be linked to the new .so file with the 'ln' command)

# The Target Build
# By default, the first target in a makefile is the default goal.
# If we want to explicitly set the default goal, we create a new 
# phony target and list the wanted targets as the phony target's
# prerequisities. This phony target is commonly called 'all' but 
# can be any name. The only requirement is that this target needs
# to be the first one in the makefile.
# Note: '.PHONY' is a special target in GNU make and is ignored
# as a target.
# The rule 'all' depends on the archive library, the shared object library, and the 'tests' rule defined below.
# In addition, 'make' uses an implicit to first run the command 'cc $(CFLAGS) -c -o src/*.o src/*.c' in order for the 'make all' to work.
.PHONY: all
all: $(TARGET) $(SO_TARGET) tests

# The '+=' operation allows you to append text to an existing
# variable. You can also use the ':=' operation to do the same
# thing; in this case, it would be 'CFLAGS := $(CFLAGS) -fPIC'.
# ar: 'archiver' --> Unix utility that maintains groups of files as a single archive file; used to create and update static libraries
# rcs: 'r' --> insert the files member into archive (with replacement), 'c' --> create the archive with an informational message being written to standard error, 's' --> write an object-file index into the archive, or update an existing one, even if no other change is made to the archive
# ranlib: add or update the table of contents of archive libraries
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

# Build the shared object library from object files.
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

# Make the 'build' and 'bin' directories if they don't exist.
build:
	@mkdir -p build
	@mkdir -p bin
	
# The Unit Tests
# The '.PHONY' : 'XX' rule is used in the case that there is a 
# file named 'XX' in the search directory. The target '.PHONY' 
# signals to 'make' that a file called 'XX' should not be 
# considered a result of the phony target.
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh
	
# The Cleaner
.PHONY: clean
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`
	
# The Install
# The prerequisites for the 'install' target is the software 
# application binary (or binaries). The commands will specify 
# which binary file to place under which directory in the 
# system.
# '-d' : create directories (missing parent directories are created as required)
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/
	
# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
