#
# Sin-Yaw Wang <swang24@scu.edu>
# For CSEN79 Exercice
# 
STD=-std=c++20
OPT=-g
CXXFLAGS=${STD} ${OPT}

%.o: %.cxx
	$(CXX) -c $(CXXFLAGS) $<

%: %.cxx
	$(CXX) -o $@ $(CXXFLAGS) $<

SRCS=bignum.cxx bignummain.cxx bignumops.cxx
OBJS=$(SRCS:.cxx=.o)
ALL=bignum

all: $(ALL)

bignum: $(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $+

clean:
	/bin/rm -f $(OBJS) $(ALL)
	/bin/rm -f test*.py test*.out
	/bin/rm -rf $(ALL:=.dSYM)

depend: $(SRCS)
	TMP=`mktemp -p .`; export TMP; \
	sed -e '/^# DEPENDENTS/,$$d' Makefile > $$TMP; \
	echo '# DEPENDENTS' >> $$TMP; \
	$(CXX) -MM $+ >> $$TMP; \
	/bin/mv -f $$TMP Makefile

# DEPENDENTS
bignum.o: bignum.cxx bignum.h
main.o: main.cxx bignum.h
