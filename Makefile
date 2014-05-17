#
# Makefile for busy-wait IO tests
#
XCC     = gcc
AS	= as
LD      = ld
OUT_DIR	= bin
SRC_DIR	= src

CFLAGS  = -c -fPIC -Wall -I./include -mcpu=arm920t -msoft-float
# -g: include hooks for gdb
# -c: only compile
# -mcpu=arm920t: generate code for the 920t architecture
# -fpic: emit position-independent code
# -Wall: report all warnings

ASFLAGS	= -mcpu=arm920t -mapcs-32
# -mapcs: always generate a complete stack frame

LDFLAGS = -init main -Map $(OUT_DIR)/main.map -N  -T orex.ld -L/u/wbcowan/gnuarm-4.0.2/lib/gcc/arm-elf/4.0.2

OBJS = 	$(OUT_DIR)/kernel.o	\
	$(OUT_DIR)/scheduler.o	\
	$(OUT_DIR)/task.o	\
	$(OUT_DIR)/bwio.o	

all: kernel.elf

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) -lgcc		

$(OUT_DIR)/kernel.o: $(OUT_DIR)/kernel.s
	$(AS) 	-o $(OUT_DIR)/kernel.o 	$(ASFLAGS) $(OUT_DIR)/kernel.s

$(OUT_DIR)/kernel.s:
	$(XCC) 	-o $(OUT_DIR)/kernel.s 	-S $(CFLAGS) $(SRC_DIR)/kernel/kernel.c

$(OUT_DIR)/scheduler.o: $(OUT_DIR)/scheduler.s
	$(AS) 	-o $(OUT_DIR)/scheduler.o 	$(ASFLAGS) $(OUT_DIR)/scheduler.s

$(OUT_DIR)/scheduler.s:
	$(XCC) 	-o $(OUT_DIR)/scheduler.s 	-S $(CFLAGS) $(SRC_DIR)/kernel/scheduler.c

$(OUT_DIR)/task.o: $(OUT_DIR)/task.s
	$(AS) 	-o $(OUT_DIR)/task.o 	$(ASFLAGS) $(OUT_DIR)/task.s

$(OUT_DIR)/task.s:
	$(XCC) 	-o $(OUT_DIR)/task.s 	-S $(CFLAGS) $(SRC_DIR)/kernel/task.c

$(OUT_DIR)/bwio.o: $(OUT_DIR)/bwio.s
	$(AS)	-o $(OUT_DIR)/bwio.o 	$(ASFLAGS) $(OUT_DIR)/bwio.s

$(OUT_DIR)/bwio.s: 
	$(XCC) 	-o $(OUT_DIR)/bwio.s 	-S $(CFLAGS) $(SRC_DIR)/bwio.c

clean:
	-rm -f $(OUT_DIR)/main.elf $(OUT_DIR)/*.s $(OUT_DIR)/*.o $(OUT_DIR)/main.map