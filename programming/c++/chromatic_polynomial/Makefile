
# le debug options
DEBUG = true

# le flags >_<
CXX		= g++
CC		= g++
CXXFLAGS 	+= -Wall -Wextra -pedantic-errors -Wold-style-cast
CPPFLAGS	+= -m64

ifeq ($(DEBUG), true)
CPPFLAGS += -ggdb
LDFLAGS += -ggdb
else
CPPFLAGS += -O3
endif

# Paths
HOME		= .
VPATH		= $(HOME)/src/
BIN		= $(HOME)/bin/
#TEMP		= $(HOME)/temp/

LDLIBS		+= -lntl		# For NTL links
LDLIBS		+= -lgmpxx -lgmp	# For GMP links

# Programs
PRGS		= chromatic_polynomial ntltest 
OBJS		= *.o
DFILES		= $(addprefix $(VPATH), $(addsuffix .d, $(PRGS)))

# default targets
.PHONY: all install clean

firsttarget: install

all: $(PRGS)

install: all
	mv $(PRGS) bin

clean:
	$(RM) $(OBJS)

cleanest: 
	$(RM) $(DFILES) 

# Linking
chromatic_polynomial: chromatic_polynomial.o utils.o polynomial.o

polynomial.o: ../polynomial/polynomial.cc ../polynomial/polynomial.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

include $(DFILES)

# Dependencies
%.d: %.cc
	@set -e; rm -f $@; \
	$(CC) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
