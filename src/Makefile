# This is the top-level Makefile for Kaldi.
# Also see kaldi.mk which supplies options and some rules
# used by the Makefiles in the subdirectories.

SHELL := /bin/bash


SUBDIRS = nnettf nnettfbin

MEMTESTDIRS = nnettf nnettfbin 

SUBDIRS_LIB = $(filter-out %bin, $(SUBDIRS))

include nnettf.mk

# Reset the default goal, so that the all target will become default
.DEFAULT_GOAL :=
all: checkversion nnettf.mk $(SUBDIRS)
	-echo Done

.PHONY: checkversion
checkversion:
ifeq ($(shell ./configure --version),$(CONFIGURE_VERSION))
	@echo "The version of configure script matches nnettf.mk version. Good."
else
	$(error The nnettf.mk file was generated using a different version of configure script. Run the configure script again.)
endif

nnettf.mk:
	@[ -f nnettf.mk ] || { echo "nnettf.mk does not exist; you have to run ./configure"; exit 1; }

# Compile optional stuff
ext: test_dependencies ext_depend $(SUBDIRS) $(EXT_SUBDIRS)
	-echo Done

clean:
	-for x in $(SUBDIRS); do $(MAKE) -C $$x clean; done

test: $(addsuffix /test, $(SUBDIRS))

ext_test: $(addsuffix /test, $(EXT_SUBDIRS))

# Define an implicit rule, expands to e.g.:
#  base/test: base
#     $(MAKE) -C base test 
%/test: %
	$(MAKE) -C $< test

valgrind:
	-for x in $(MEMTESTDIRS); do $(MAKE) -C $$x valgrind || { echo "valgrind on $$x failed"; exit 1; }; done


depend: $(addsuffix /depend, $(SUBDIRS))

%/depend:
	$(MAKE) -C $(dir $@) depend


.PHONY: $(SUBDIRS)
$(SUBDIRS) :
	$(MAKE) -C $@ 

nnettfbin: nnettf
