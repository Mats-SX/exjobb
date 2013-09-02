
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
PRGS		= k_packing poly_test k_partition k_cover instance_creator
OBJS		= poly_test.o k_packing.o k_partition.o polynomial.o utils.o k_cover.o instance_creator.o
DFILES		= $(addprefix $(VPATH), $(addsuffix .d, $(PRGS)))

# default targets
.PHONY: all install clean

firsttarget: install

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
instance_creator: instance_creator.o
k_cover: k_cover.o utils.o polynomial.o
k_partition: k_partition.o utils.o polynomial.o
k_packing: k_packing.o utils.o polynomial.o
poly_test: poly_test.o polynomial.o

include $(DFILES)

# Dependencies
%.d: %.cc
	@set -e; rm -f $@; \
	$(CC) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
