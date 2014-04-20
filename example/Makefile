OBJS=test.o 
#add pop_config library
LIBPATH=$(shell pwd)/../lib/
INCPATH=-I$(LIBPATH)
LIB=$(LIBPATH)pop_config.o
OBJS+=$(LIB)

CC=gcc
CFLAGS=$(INCPATH)  
TARGET=test
$(TARGET):$(OBJS)
	$(CC) -o $@  $(OBJS) $(CFLAGS)
clean:
	rm -f $(OBJS) 
	rm -f $(TARGET)
