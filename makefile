CXX = g++
CXXFLAGS = -Wall -O2 -Iinclude
TARGET = mjolnir
SRC = src/main.cpp src/mjolnir_functions.cpp
MANPAGE = man/mjolnir.1

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
	sudo cp $(MANPAGE) /usr/share/man/man1/
	sudo mandb

uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)
	sudo rm -f /usr/share/man/man1/$(MANPAGE)
	sudo mandb

clean:
	rm -f $(TARGET)
