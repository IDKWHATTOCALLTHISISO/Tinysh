CC=gcc
CFLAGS=-Os
LDFLAGS=-static
TARGET=tinysh

all: $(TARGET)

$(TARGET)
    $(CC) $(CFLAGS) -o $(TARGET) $(LDFLAGS)
clean:
    rm -f $(TARGET)
