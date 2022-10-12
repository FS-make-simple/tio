TARGET=tio
VERSION=2.1
BAUDRATES=0 50 75 110 134 150 200 300 600 1200 1800 2400 4800 9600 19200 38400 57600 115200 230400 460800 500000 576000 921600 1000000 1152000 1500000 2000000 2500000 3000000 3500000 4000000 # not found: 7200 14400 28800 76800

CC=cc
CFLAGS=-Wall -std=gnu99 -Isrc
LDFLAGS= -linih -s
RM = rm -f
SRCS = \
      src/alert.c \
      src/configfile.c \
      src/error.c \
      src/log.c \
      src/misc.c \
      src/options.c \
      src/print.c \
      src/rs485.c \
      src/setspeed.c \
      src/signals.c \
      src/socket.c \
      src/timestamp.c \
      src/tty.c \
      src/main.c

all: $(TARGET)

$(TARGET): $(SRCS) src/config.h
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

src/config.h:
	printf "#define VERSION \"$(VERSION)\" \n" > $@
	if test -f "`find /usr/include | grep -m 1 asm-generic/ioctls.h`"; then printf "#define HAVE_TERMIOS2\n" >> $@; fi
	if test -f "`find /usr/include | grep -m 1 IOKit/serial/ioss.h`"; then printf "#define HAVE_IOSSIOSPEED\n" >> $@; fi
	printf "#define BAUDRATE_CASES" >> $@
	for baud in $(BAUDRATES); do printf " case $${baud}: baudrate = B$${baud}; break;"; done >> $@
	printf "\n" >> $@

clean:
	$(RM) $(TARGET) src/config.h

