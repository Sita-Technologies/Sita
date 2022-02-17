HPPS = commandline_args.hpp COutline.hpp decompile.hpp helper.hpp \
       item.hpp outline_decs.hpp SalNumber.hpp system_variables.hpp \
       sal_datatypes.hpp sal_functions.hpp system_variables.cpp
OBJS = commandline_args.o COutline.o decompile.o helper.o item.o \
       main.o SalNumber.o system_variables.o
TARGET = Sita

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ -Wall -O2 -o $@ $^

%.o: %.cpp $(HPPS)
	g++ -Wall -O2 -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
