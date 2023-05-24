# 1. compiler, flags
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++14
INCLUDES := -I.
LDFLAGS := -L./lib


# 2. DIRS
SRCDIR := .
OBJDIR := ./obj
LIBDIR := ./lib
BINDIR := ./bin


# 3. FILES
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))
LIBS := $(addprefix $(LIBDIR)/, $(patsubst %.o, lib%.so, $(filter-out main.o, $(notdir $(OBJS)))))
BINS := $(addprefix $(BINDIR)/, main)


# 4. BUILD RULES
all: $(BINS)

$(BINS): $(OBJS) $(LIBS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJDIR)/main.o -o $(BINS) $(LDFLAGS) -lfunc

$(LIBDIR)/lib%.so: $(OBJDIR)/%.o | $(LIBDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -shared $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(OBJDIR) $(LIBDIR) $(BINDIR):
	mkdir -p $@


# 5. clean rule
.PHONY: clean

clean:
	rm -r $(OBJDIR) $(LIBDIR) $(BINDIR)