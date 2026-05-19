# Sita — Gupta Team Developer decompiler
#
# Build artifacts (objects, dependency files, final binary) go into build/.
# Sources live in src/. Run `make` from the repository root.

CXX      ?= g++
CXXFLAGS ?= -Wall -O2
LDFLAGS  ?=
LDLIBS   ?=

PREFIX  ?= /usr/local
BINDIR  ?= $(PREFIX)/bin

SRCDIR   := src
BUILDDIR := build

TARGET := $(BUILDDIR)/Sita

SRCS := \
    commandline_args.cpp \
    COutline.cpp \
    COutline64.cpp \
    decompile.cpp \
    decompile64.cpp \
    helper.cpp \
    item.cpp \
    item64.cpp \
    main.cpp \
    process_outline.cpp \
    process_outline64.cpp \
    sal_functions.cpp \
    SalNumber.cpp \
    system_variables.cpp

OBJS := $(SRCS:%.cpp=$(BUILDDIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(@:.o=.d) -c -o $@ $<

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

install: $(TARGET)
	install -d $(DESTDIR)$(BINDIR)
	install -m 0755 $(TARGET) $(DESTDIR)$(BINDIR)/Sita

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/Sita

clean:
	rm -rf $(BUILDDIR)

-include $(DEPS)
