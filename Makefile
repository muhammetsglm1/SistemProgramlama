INC="include"
LIB="include"
TARGET=kripto

all: $(TARGET)


$(TARGET): include/libfdr.a $(TARGET).c
	gcc -I$(INC) $(TARGET).c -o $@ -L$(LIB) -lfdr

clean:
	rm -rf $(TARGET)

