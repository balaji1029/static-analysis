RUSTEXECUTABLE := target/debug/ast-build
ASTPARSE := bin/astparse
CXX := g++
CXXFLAGS := -std=c++20 -O3
CODE := codes/forloop.rs

all: $(ASTPARSE) $(RUSTEXECUTABLE)

$(RUSTEXECUTABLE): src/main.rs
	cargo build

$(ASTPARSE): cpp/astparse.cpp include/*.h
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f bin/*
	cargo clean

run: $(RUSTEXECUTABLE) $(ASTPARSE)
	$(RUSTEXECUTABLE) $(CODE) | $(ASTPARSE) $(CODE) > graphs/$(CODE).dot