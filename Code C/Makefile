.PHONY: all clean
CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lgmp -lgmpxx
OBJFILES = main.o rsa_file_blocks.o rsa_file_char.o rsa_tools_gmp.o rsa_tools.o bezout.o other_base64.o rsa_print_tools.o crypt_decrypt.o Sha-256/sha256_utils.o Sha-256/sha256.o int2char.o
TARGET = exe

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
