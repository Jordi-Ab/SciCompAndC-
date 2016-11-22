CC = gcc
CXX = g++
RM = rm -f
CPPFLAGS = -g 
LDFLAGS = -g 
LDLIBS = 

SRCS = Driver.cpp ComplexNumber.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

all: Driver

Driver: $(OBJS)
	$(CXX) $(LDFLAGS) -o Driver $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
