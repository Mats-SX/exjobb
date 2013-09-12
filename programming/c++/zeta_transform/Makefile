
# le debug options
DEBUG = true

# le flags >_<
CXX		= g++
CC		= g++

LDLIBS		+= -lgmpxx -lgmp	# For GMP links

ifeq ($(DEBUG), true)
CPPFLAGS += -ggdb
LDFLAGS += -ggdb
else
CPPFLAGS += -O3
endif

# Paths
HOME		= ./
VPATH		= $(HOME)src/
BIN		= $(HOME)bin/
#TEMP		= $(HOME)/temp/

# Programs
PRGS		= fztlin
OBJS		= *.o
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
	$(RM) $(VPATH)*.d

cleanest: cleaner
	$(RM) $(VPATH)*~ $(HOME)*~

# Linking
fztlin: fztlin.o utils.o types.o

include $(DFILES)

# Dependencies
%.d: %.cc
	@set -e; rm -f $@; \
	$(CC) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
