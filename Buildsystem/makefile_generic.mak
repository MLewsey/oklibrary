# Oliver Kullmann, 6.3.2002 (Swansea)

# Generic makefile, to be used in a general environment for C++
# compilation

# Usage:

# make all
# = make unoptimised optimised

# make unoptimised
# creates all dependencies files, object files, and program files;

# make optimised
# creates the same (names of object and program files modified), but using optimisation options;

# make prebuild
# creates all directories, and copies makefiles if necessary

# make check
# = make test testop
# The test program is called with the parameters given by $(test_parameters) (see below);
# the main variable is test_level, which has one of the values "basic", "full", "extensive".

# make test
# recompiles the test program if necessary, and runs the test if necessary.

# make testop
# recompiles the test program with optimisation if necessary, and runs the test if necessary.

# make clean
# = make cleanobj cleandep
# make cleanall
# = make clean cleanprograms

# make cleantest 
# removes test timestamp files from every module.

# make cleantestop 
# removes testop timestamp files from every module.

# make cleanalltest 
# = make cleantest cleantestop

# make new_cleantest 
# removes all new_test_basic timestamp files from aux subdirectories.

# make new_cleantestop 
# removes all new_testop_basic timestamp files from aux subdirectories.

# make new_cleanalltests
# = make new_cleantest new_cleantestop

# Programs are compiled with $(CXX), while objectfiles are compiled with $(CXX) resp. $(CC)
# depending on the suffix (.cpp resp. .c).

# make alternative_gcc=? alternative_boost=% 
# where ? is the locally installed GCC version number (for example 3.4.3) and % is the locally installed boost version number (for example 1_33).
# If one doesn't specify alternative_boost=, then the system boost will be used, while setting alternative_gcc will override $(CXX) and $(CC) respectively, and a locally installed boost will be used (either given by alternative_boost, or, if not defined, then the tail of $(Boost) is used as the generic name for the current boost version).

# The compile-command is prefixed with $(Compile_tool), the link-command with $(Link_tool),
#  and the test execution with $(Test_tool); the default in all 3 cases is "time -p" (measuring
# the wall clock time, the process time and the system time used in total for the execution).
# Setting Test_tool="valgrind --quiet" runs all tests with memory check.
# The default of Warning_options is "-Wall".

# make html
# creates the doxygen-documentation
# make doxygen-parameters="..." html
# will pass these parameter-settings to doxygen; for example by
# make doxygen-parameters="HAVE_DOT=YES" html
# creates all sorts of graphs (dependencies and derivations; takes much longer than without).

# #############################################################

SHELL = /bin/sh
.SUFFIXES :

define last-element
$(word $(words $1),$1)
endef

ifndef srcdir

this-makefile := $(call last-element,$(MAKEFILE_LIST))
other-makefiles := $(filter-out $(this-makefile),$(MAKEFILE_LIST))
parent-makefile := $(call last-element,$(other-makefiles))
srcdir := $(shell cd $(dir $(parent-makefile)); pwd)
module-name := $(notdir $(srcdir))

endif

ifndef OKplatform
  ifdef OKPLATFORM
    OKplatform := $(OKPLATFORM)
  else
    $(error Either OKplatform (a make-variable) or OKPLATFORM (an environment-variable) must be defined when calling this makefile!)
  endif
endif

ifndef OKsystem
  ifdef OKSYSTEM
    OKsystem := $(OKSYSTEM)
  else
    OKsystem := $(OKplatform)/OKsystem
  endif
endif

OKsystem_include := -I$(OKsystem)

OKBuildsystem := $(OKsystem)/Transitional/Buildsystem

ifndef Boost
  ifdef BOOST
    Boost = -I$(BOOST)
  endif
endif

export

include $(OKBuildsystem)/makefile_standardgoals.mak

export

include $(srcdir)/makefile.definitions.mak

# Definitions required from makefile.definitions:
# General_options
# Optimisation_options
# test_program (for the old test-system)
# programs
# source_libraries
# link_libraries

source_libraries += $(OKsystem_include)

prefix := $(OKplatform)

ifndef SystemDirectories
  ifdef SYSTEMDIRECTORIES
    SystemDirectories := $(SYSTEMDIRECTORIES)
  else
    SystemDirectories := $(prefix)/SystemDirectories
  endif
endif

system_directories := $(SystemDirectories)

bindir := $(system_directories)/bin
libdir := $(system_directories)/lib

aux_dir := $(system_directories)/aux
latex_dir := $(aux_dir)/latex
dependencies_dir := $(aux_dir)/dependencies

doc_dir := $(system_directories)/doc
html_dir := $(doc_dir)/html

test-bindir := $(bindir)/tests
test-libdir := $(libdir)/tests/$(module-name)
test-auxdir := $(aux_dir)/tests/$(module-name)

Directories := $(bindir) $(libdir) $(aux_dir) $(doc_dir) $(html_dir) $(test-bindir) $(test-libdir) $(test-auxdir) $(latex_dir) $(dependencies_dir)

doxygen-parameters := 
Doxygen_modifier := 2> $(aux_dir)/DoxygenErrorMessages

# -----------------------------------------------------------------------------------


ifneq ($(programs),)
  programs := $(addprefix $(bindir)/, $(programs))
endif

ifneq ($(test_program),) # old test-system needed
  test_program := $(addprefix $(bindir)/, $(test_program))
  programs += $(test_program)
endif

new_test_program := $(test-bindir)/$(module-name)
standard_test_program_object_file := $(libdir)/TestProgram_DesignStudy.o

testobjects-dir := $(srcdir)/testobjects

# ---------------------------------------------------

name_addition := $(shell echo $(Optimisation_options) | tr --delete " ")
All_options := $(General_options) $(Optimisation_options)

programs_optimised := $(programs:=$(name_addition))

new_test_program_optimised := $(new_test_program)$(name_addition)
standard_test_program_object_file_optimised := $(libdir)/TestProgram_DesignStudy$(name_addition).o

compilation_units_cpp := $(wildcard $(srcdir)/*.cpp)
compilation_units_cpp := $(notdir $(compilation_units_cpp))
compilation_units_c := $(wildcard $(srcdir)/*.c)
compilation_units_c := $(notdir $(compilation_units_c))

test_compilation_units := $(wildcard $(testobjects-dir)/*.cpp)

dependency_files_cpp := $(compilation_units_cpp:.cpp=.d)
dependency_files_cpp := $(addprefix $(dependencies_dir)/, $(dependency_files_cpp))
dependency_files_c := $(compilation_units_c:.c=.d) 
dependency_files_c := $(addprefix $(dependencies_dir)/, $(dependency_files_c))
dependency_files := $(dependency_files_cpp) $(dependency_files_c)

test_dependency_files := $(notdir $(test_compilation_units))
test_dependency_files := $(test_dependency_files:.cpp=.d)
test_dependency_files := $(addprefix $(test-auxdir)/, $(test_dependency_files))
dependency_files := $(dependency_files) $(test_dependency_files)

object_files_cpp := $(compilation_units_cpp:.cpp=.o) 
object_files_cpp := $(addprefix $(libdir)/, $(object_files_cpp))
object_files_c := $(compilation_units_c:.c=.o)
object_files_c := $(addprefix $(libdir)/, $(object_files_c))
object_files := $(object_files_cpp) $(object_files_c)
object_files_cpp_optimised := $(compilation_units_cpp:.cpp=$(name_addition).o)
object_files_cpp_optimised := $(addprefix $(libdir)/, $(object_files_cpp_optimised))
object_files_c_optimised := $(compilation_units_c:.c=$(name_addition).o)
object_files_c_optimised := $(addprefix $(libdir)/, $(object_files_c_optimised))
object_files_optimised := $(object_files_cpp_optimised) $(object_files_c_optimised)

test_object_files := $(notdir $(test_compilation_units))
test_object_files := $(test_object_files:.cpp=.o)
test_object_files := $(addprefix $(test-libdir)/, $(test_object_files))

test_object_files_optimised := $(notdir $(test_compilation_units))
test_object_files_optimised := $(test_object_files_optimised:.cpp=$(name_addition).o)
test_object_files_optimised := $(addprefix $(test-libdir)/, $(test_object_files_optimised))


test_file := $(srcdir)/test
testop_file := $(srcdir)/testop

# -----------------------------------------------------------------------------------

doxy_file := $(OKBuildsystem)/Doxyfile

# -----------------------------------------------------------------------------------

CXX := g++
CC := gcc
Standard_options := -ansi -pedantic
Warning_options := -Wall
Compile_tool := time -p
Link_tool := time -p
Test_tool := time -p

# -----------------------------------------------------------------------------------

test_level := basic

error_file := $(test-auxdir)/Error
message_file := $(test-auxdir)/Message
log_file := $(test-auxdir)/Log

error_stream := "cerr|ofstream-w=$(error_file)|ofstream-w=$(log_file)"
message_stream := "cout|ofstream-w=$(message_file)|ofstream-w=$(log_file)"
log_stream := "ofstream-w=$(log_file)"

error_level := 0
message_level := 0
log_level := 0

error_lang := en_GB
message_lang := en_GB
log_lang := en_GB

test_parameters := $(test_level) $(error_stream) $(message_stream) $(log_stream) $(error_level) $(message_level) $(log_level) $(error_lang) $(message_lang) $(log_lang)

# -----------------------------------------------------------------------------------

test_timestamp := $(test-auxdir)/new_test_$(test_level)
testop_timestamp := $(test-auxdir)/new_testop_$(test_level)

# -----------------------------------------------------------------------------------

alternative_gcc:=
alternative_boost:=
alternative_library_path:=

ifneq ($(alternative_gcc),) # alternative gcc specified
  CXX := $(prefix)/ExternalSources/Gcc/$(alternative_gcc)/bin/g++
  CC := $(prefix)/ExternalSources/Gcc/$(alternative_gcc)/bin/gcc
  alternative_library_path:= -L$(prefix)/ExternalSources/Gcc/$(alternative_gcc)/lib64 -Wl,-rpath,$(prefix)/ExternalSources/Gcc/$(alternative_gcc)/lib64 -L$(prefix)/ExternalSources/Gcc/$(alternative_gcc)/lib -Wl,-rpath,$(prefix)/ExternalSources/Gcc/$(alternative_gcc)/lib
  ifeq ($(alternative_boost),)
    ifndef Boost
      $(error Variable Boost must be defined!)
    endif
    alternative_boost := $(patsubst -I%,%,$(Boost))
    alternative_boost := $(patsubst %/,%,$(alternative_boost))
    alternative_boost := $(notdir $(alternative_boost))
    alternative_boost := $(patsubst boost-%,%,$(alternative_boost))
  endif
  alternative_library_path := $(alternative_library_path) -L$(prefix)/ExternalSources/Boost/$(alternative_boost)+$(alternative_gcc)/lib -Wl,-rpath,$(prefix)/ExternalSources/Boost/$(alternative_boost)+$(alternative_gcc)/lib
  Boost = -I$(prefix)/ExternalSources/Boost/$(alternative_boost)+$(alternative_gcc)/include/boost-$(alternative_boost)
else # no alternative gcc specified
  ifneq ($(alternative_boost),) # alternative boost specified
  alternative_library_path := $(alternative_library_path) -L$(prefix)/ExternalSources/Boost/$(alternative_boost)/lib -Wl,-rpath,$(prefix)/ExternalSources/Boost/$(alternative_boost)/lib
  Boost = -I$(prefix)/ExternalSources/Boost/$(alternative_boost)/include/boost-$(alternative_boost)
  endif
endif

# Explanation: With "-Wl,-rpath,Path" we tell the compiler to pass the option "-rpath Path" to the linker, which will add Path to the places searched for this program for run-time-libraries.

# ----------------------------------------------------------------

all : unoptimised optimised

prebuild : createdirs

createdirs : $(Directories)

html :
	echo "Doxygen version: $$(doxygen --version)"; rm -r $(html_dir)/*; cd $(OKplatform); ( cat $(doxy_file); echo $(doxygen-parameters) "OUTPUT_DIRECTORY=$(doc_dir)" ) | doxygen - $(Doxygen_modifier)

unoptimised : $(object_files) $(programs)

optimised : $(object_files_optimised) $(programs_optimised)

check : test testop

new_check : new_test new_testop

ifneq ($(test_program),) # old test-system needed
test : $(test_file)
testop : $(testop_file)
else
test :
testop :
endif

new_test : $(test_timestamp)
new_testop : $(testop_timestamp)

$(test_file) : $(test_program)
	$(Test_tool) $(test_program)
	touch $(test_file)
$(testop_file) : $(test_program)$(name_addition)
	$(Test_tool) $(test_program)$(name_addition)
	touch $(testop_file)

$(test_timestamp) : $(new_test_program)
	$(Test_tool) $(new_test_program) $(test_parameters)
	touch $(test_timestamp)
$(testop_timestamp) : $(new_test_program_optimised)
	$(Test_tool) $(new_test_program_optimised) $(test_parameters)
	touch $(testop_timestamp)

force :

# ---------------------------------------------------------------

ifeq ($(firstword $(filter $(special_goals) $(cleaning_goals) $(forced_goals), $(MAKECMDGOALS))),)
include $(dependency_files)
endif

$(Directories) : % :
	mkdir --parents --verbose $@

$(dependency_files_cpp) : $(dependencies_dir)/%.d : $(srcdir)/%.cpp
	$(CXX) -MM -MF $@ -MT $(libdir)/$*.o -MT $(libdir)/$*$(name_addition).o -MT $@ $(source_libraries) $<
$(dependency_files_c) : $(dependencies_dir)/%.d : $(srcdir)/%.c
	$(CC) -MM -MF $@ -MT $(libdir)/$*.o -MT $(libdir)/$*$(name_addition).o -MT $@ $(source_libraries) $<

$(test_dependency_files) : $(test-auxdir)/%.d : $(testobjects-dir)/%.cpp
	$(CXX) -MM -MF $@ -MT $(test-libdir)/$*.o -MT $(test-libdir)/$*$(name_addition).o -MT $@ $(source_libraries) $<

$(object_files_cpp_optimised) : $(libdir)/%$(name_addition).o : $(srcdir)/%.cpp
	$(Compile_tool) $(CXX) -c -o $@ $(Standard_options) $(Warning_options) $(CPPFLAGS) $(CXXFLAGS) $(Optimisation_options) $(source_libraries) $<
$(object_files_cpp) : $(libdir)/%.o : $(srcdir)/%.cpp
	$(Compile_tool) $(CXX) -c -o $@ $(Standard_options) $(Warning_options) $(CPPFLAGS) $(CXXFLAGS) $(General_options) $(source_libraries) $<

$(object_files_c_optimised) : $(libdir)/%$(name_addition).o : $(srcdir)/%.c
	$(Compile_tool) $(CC) -c -o $@ $(Standard_options) $(Warning_options) $(CPPFLAGS) $(CFLAGS) $(Optimisation_options) $(source_libraries) $<
$(object_files_c) : $(libdir)/%.o : $(srcdir)/%.c
	$(Compile_tool) $(CC) -c -o $@ $(Standard_options) $(Warning_options) $(CPPFLAGS) $(CFLAGS) $(General_options) $(source_libraries) $<

$(test_object_files) : $(test-libdir)/%.o : $(testobjects-dir)/%.cpp
	$(Compile_tool) $(CXX) -c -o $@ $(Standard_options) $(Warning_options) $(CPPFLAGS) $(CXXFLAGS) $(General_options) $(source_libraries) $<
$(test_object_files_optimised) : $(test-libdir)/%$(name_addition).o : $(testobjects-dir)/%.cpp
	$(Compile_tool) $(CXX) -c -o $@ $(Standard_options) $(Warning_options) $(CPPFLAGS) $(CXXFLAGS) $(Optimisation_options) $(source_libraries) $<


define get-link_libraries
$$(if [[ -e $(srcdir)/$*.link_libraries ]]; then $(srcdir)/$*.link_libraries; else echo $(link_libraries); fi)
endef
define get-link_libraries_optimised
$$(if [[ -e $(srcdir)/$*.link_libraries_optimised ]]; then $(srcdir)/$*.link_libraries_optimised; else if [[ -e $(srcdir)/$*.link_libraries ]]; then $(srcdir)/$*.link_libraries; else echo $(link_libraries); fi; fi)
endef

export

$(programs) : $(bindir)/% : $(libdir)/%.o
	$(Link_tool) $(CXX) -o $@ $(Standard_options) $(Warning_options) $(General_options) $< $(alternative_library_path) $(get-link_libraries)
$(programs_optimised) : $(bindir)/%$(name_addition) : $(libdir)/%$(name_addition).o
	$(Link_tool) $(CXX) -o $@ $(Standard_options) $(Warning_options) $(Optimisation_options) $< $(alternative_library_path) $(get-link_libraries_optimised)

$(new_test_program) : $(test-bindir)/% : $(test_object_files) $(standard_test_program_object_file)
	$(Link_tool) $(CXX) -o $@ $(Standard_options) $(Warning_options) $(General_options) $^ $(alternative_library_path) $(get-link_libraries)
$(new_test_program_optimised) : $(test-bindir)/%$(name_addition) : $(test_object_files_optimised) $(standard_test_program_object_file_optimised)
	$(Link_tool) $(CXX) -o $@ $(Standard_options) $(Warning_options) $(Optimisation_options) $^ $(alternative_library_path) $(get-link_libraries_optimised)

# --------------------------------

cleantest :
	- rm $(test_file)

cleantestop :
	- rm $(testop_file)

cleanalltest : cleantest cleantestop

new_cleantest :
	- rm $(test_timestamp)

new_cleantestop :
	- rm $(testop_timestamp)

new_cleanalltests : new_cleantest new_cleantestop

cleanobj :
	- rm $(object_files) $(object_files_optimised)

cleantestobj :
	- rm $(test_object_files) $(test_object_files_optimised)

cleandep :
	- rm $(dependency_files)

clean : cleanobj cleantestobj cleandep
	- rm $(test_file) $(testop_file) $(test_timestamp) $(testop_timestamp) 

cleanprograms :
	- rm $(programs) $(programs_optimised) $(new_test_program) $(new_test_program_optimised) 

cleanall : clean cleanprograms
	- rm $(error_file) $(message_file) $(log_file)
