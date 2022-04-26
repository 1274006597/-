# user add code include *.mk files
include message/message.mk
include menu/menu.mk

ARCH ?= x86
TARGET = tcp_server

# c sources files(*.c) foldr 
SRC_DIRS += server\
            message
#export SRC_DIRS 
# c include files(*.h) folder 
INC_DIRS += server\
            message
#export INC_DIRS

# build files folder
BUILD_DIR = build_$(ARCH)
CUR_DIR = $(shell pwd)

SRC_DIRS := $(patsubst %,$(CUR_DIR)/%,$(SRC_DIRS))
SRC_DIRS := $(sort $(SRC_DIRS))  # Remove duplicate files

INC_DIRS := $(patsubst %,$(CUR_DIR)/%,$(INC_DIRS))
INC_DIRS := $(sort $(INC_DIRS))  # Remove duplicate files

BUILD_DIR := $(patsubst %,$(CUR_DIR)/%,$(BUILD_DIR))

# c sources files(*.c) 
#SRCS = $(wildcard $(SRC_DIR)/*.c) #实际测试该行只会返回文件夹路径
SRCS := $(foreach c_dirs, $(SRC_DIRS), $(wildcard $(c_dirs)/*.c))
# c include files(*.h)
DEPS := $(foreach h_dirs, $(INC_DIRS), $(wildcard $(h_dirs)/*.h))
# object files(*.o)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))


CFLAGS += $(patsubst %, -I%, $(INC_DIRS))
# libraries
CLIBS  += -lpthread

#ARCH=x86，use gcc
#ARCH=arm，use arm-gcc
ifeq ($(ARCH),x86)
CC = gcc
else
CC = arm-linux-gnueabihf-gcc
endif
# list of objects
vpath %.c $(sort $(dir $(SRCS)))



$(BUILD_DIR)/$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(CLIBS) $(CFLAGS)
$(BUILD_DIR)/%.o:%.c $(DEPS)
	@mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAGS) 

.PHONY:clean
clean:
	rm -rf $(BUILD_DIR)
.PHONY:print
print:
	@echo OBJS is: $(OBJS)
	@echo SRC_DIRS is: $(SRC_DIRS)
	@echo INC_DIRS is: $(INC_DIRS)
	@echo SRCS is: $(SRCS)
	@echo DEPS is: $(DEPS)
	@echo CFLAGS is: $(CFLAGS)
