PROJECT_ROOT := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
PROJECT_NAME = main_3

CROSS_COMPILER = 
INCLUDE_PATH = $(PROJECT_ROOT)
BUILD_DIR = $(PROJECT_ROOT)/build

CC = $(CROSS_COMPILER)g++

all: main_3.o adc.o gpio.o pwm.o uart.o
	$(CC) $(BUILD_DIR)/*.o -o $(PROJECT_NAME)

main_3.o: | $(BUILD_DIR)
		$(CC) -c $(PROJECT_ROOT)/main_3.cpp -o $(BUILD_DIR)/main_3.o

adc.o:  | $(BUILD_DIR)
	$(CC) -I $(INCLUDE_PATH)/adc -c $(PROJECT_ROOT)/adc/adc.cpp -o $(BUILD_DIR)/adc.o

gpio.o:  | $(BUILD_DIR)
	$(CC) -I $(INCLUDE_PATH)/gpio -c $(PROJECT_ROOT)/gpio/SimpleGPIO.cpp -o $(BUILD_DIR)/gpio.o

pwm.o:  | $(BUILD_DIR)
	$(CC) -I $(INCLUDE_PATH)/pwm -c $(PROJECT_ROOT)/pwm/pwm.cpp -o $(BUILD_DIR)/pwm.o

uart.o: | $(BUILD_DIR)
	$(CC) -I $(INCLUDE_PATH)/uart -c $(PROJECT_ROOT)/uart/uart.cpp -o $(BUILD_DIR)/uart.o

$(BUILD_DIR):
	mkdir $(BUILD_DIR)