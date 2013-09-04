
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
PRGS		= poly_test fast_zeta_transform instance_creator
OBJS		= poly_test.o polynomial.o utils.o instance_creator.o fast_zeta_transform.o
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
fast_zeta_transform: fast_zeta_transform.o utils.o polynomial.o
instance_creator: instance_creator.o
poly_test: poly_test.o polynomial.o

include $(DFILES)

# Dependencies
%.d: %.cc
	@set -e; rm -f $@; \
	$(CC) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
