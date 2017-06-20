CC      := gcc
CXX     := g++

BINDIR = bin
OUTDIR = output
SRCDIR = src

LFLAGS	:=
CXXFLAGS := -std=c++11

#main: $(SRCDIR)/main.c $(SRCDIR)/wave.c $(SRCDIR)/wav/wav.c
main:
	mkdir -p $(BINDIR)
	mkdir -p $(OUTDIR)
	$(CXX) $(SRCDIR)/main.cpp $(SRCDIR)/cmdline.cpp $(SRCDIR)/evolution.cpp $(SRCDIR)/fitness.cpp $(SRCDIR)/population.cpp $(LFLAGS) -o $(BINDIR)/genalg -Wall $(CXXFLAGS)

clean:
	rm -rf $(BINDIR)/genalg $(OUTDIR)/
