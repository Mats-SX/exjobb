
# le debug options
DEBUG = false

# le flags >_<
CXX		= gcc
CPPFLAGS	= -std=gnu99
#CXXFLAGS	= -std=gnu99
#CC		= gcc

#ifeq ($(DEBUG), true)
#CXXFLAGS += -ggdb
#LDFLAGS += -ggdb
#else
#CXXFLAGS += -O2
#endif

# Paths
HOME		= .
VPATH		= $(HOME)/src/
BIN		= $(HOME)/bin/
#TEMP		= $(HOME)/temp/

# Programs
PRGS		= zeta_transform
OBJS		= $(addsuffix .o, $(PRGS))
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
zeta_transform: zeta_transform.o

include $(DFILES)

# Dependencies
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
