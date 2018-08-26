#Makefile

#Erick de Oliveira Silva

#Compiler
CXX = gcc

#Flags
COMPILE_FLAG = -std=c11

#Path
SRC_PATH = src/caesar_decoder.c

#Executable
BIN_NAME = ./bin/decipher

#Builded files
UNCIPHER_NAME = build/unciphered

make:
	if [ ! -d bin/ ]; then mkdir bin/; fi
	if [ ! -d build/ ]; then mkdir build/; fi
	$(CXX) -Wall $(COMPILE_FLAG) $(SRC_PATH) -o $(BIN_NAME)

clean:
	rm -rf bin/
	rm -rf build/
