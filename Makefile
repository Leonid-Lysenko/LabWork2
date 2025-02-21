G = g++
F = -Werror -Wpedantic -Wall
RUN = Lab2
T_RUN = test

SRC = $(wildcard source/*.cpp)
T_SRC = $(wildcard tests/*.cpp)

OBJDIR = source/obj
T_OBJDIR = tests/obj

OBJ = $(SRC:source/%.cpp=$(OBJDIR)/%.o)
T_OBJ = $(T_SRC:tests/%.cpp=$(T_OBJDIR)/%.o)

all: $(RUN)

$(RUN): $(OBJ)
	$(G) $(OBJ) -o $@
$(T_RUN): $(T_OBJ)
	$(G) $(T_OBJ) -o $@ -lgtest -lgtest_main -pthread

$(OBJDIR)/%.o: source/%.cpp | $(OBJDIR)
	$(G) -c $< $(F) -o $@
$(T_OBJDIR)/%.o: tests/%.cpp | $(T_OBJDIR)
	$(G) -c $< $(F) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(T_OBJDIR):
	mkdir -p $(T_OBJDIR)

clean:
	rm -rf $(OBJDIR) $(T_OBJDIR) $(RUN) $(T_RUN)

cleanall: clean

.PHONY: all clean cleanall test
