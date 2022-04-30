HPPS = commandline_args.hpp COutline.hpp decompile.hpp helper.hpp \
       item.hpp outline_decs.hpp SalNumber.hpp system_variables.hpp \
       sal_datatypes.hpp sal_functions.hpp process_outline.hpp \
       def4.inc undef64.inc
OBJS = commandline_args.o COutline.o decompile.o helper.o item.o \
       main.o SalNumber.o system_variables.o COutline64.o item64.o \
       process_outline.o process_outline64.o decompile64.o sal_functions.o
TARGET = Sita

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ -Wall -O2 -o $@ $^

%.o: %.cpp $(HPPS)
	g++ -Wall -O2 -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
