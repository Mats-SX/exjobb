
# le debug options
DEBUG = true

# le flags >_<
CXX		= g++
CC		= g++

ifeq ($(DEBUG), true)
CPPFLAGS += -ggdb
LDFLAGS += -ggdb
else
CPPFLAGS += -O2
endif

# Paths
HOME		= .
VPATH		= $(HOME)/src/
BIN		= $(HOME)/bin/
#TEMP		= $(HOME)/temp/

# Programs
<<<<<<< HEAD
PRGS		= poly_test fast_zeta_transform instance_creator
OBJS		= poly_test.o polynomial.o utils.o instance_creator.o fast_zeta_transform.o
=======
PRGS		= k_packing poly_test k_partition k_cover instance_creator
OBJS		= poly_test.o k_packing.o k_partition.o polynomial.o utils.o k_cover.o instance_creator.o
>>>>>>> Changed implementation in k-cover from vectors to int arrays in
DFILES		= $(addprefix $(VPATH), $(addsuffix .d, $(PRGS)))

# default targets
.PHONY: all install clean

firsttarget: install clean

all: $(PRGS)

install: all
	mv $(PRGS) bin

clean:
	$(RM) $(OBJS)

cleaner: clean
	$(RM) $(DFILES)

cleanest: cleaner
	$(RM) $(BIN)*

# Linking
<<<<<<< HEAD
fast_zeta_transform: fast_zeta_transform.o utils.o polynomial.o
=======
>>>>>>> Changed implementation in k-cover from vectors to int arrays in
instance_creator: instance_creator.o
poly_test: poly_test.o polynomial.o

include $(DFILES)

# Dependencies
%.d: %.cc
	@set -e; rm -f $@; \
	$(CC) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
