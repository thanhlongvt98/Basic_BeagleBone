PROJECT_ROOT := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
PROJECT_NAME = main

CROSS_COMPILER = 
INCLUDE_PATH = $(PROJECT_ROOT)/../lib
BUILD_DIR = $(PROJECT_ROOT)/build

CC = $(CROSS_COMPILER)g++

all: main.o adc.o gpio.o pwm.o uart.o
	$(CC) $(BUILD_DIR)/*.o -o $(PROJECT_NAME) -std=c++11

main.o: | $(BUILD_DIR)
		$(CC) -c $(PROJECT_ROOT)/main.cpp -o $(BUILD_DIR)/main.o -std=c++11

adc.o:  | $(BUILD_DIR)
	$(CC) -I $(INCLUDE_PATH)/adc -c $(INCLUDE_PATH)/adc/adc.cpp -o $(BUILD_DIR)/adc.o -std=c++11

gpio.o:  | $(BUILD_DIR)
	$(CC) -I $(INCLUDE_PATH)/gpio -c $(INCLUDE_PATH)/gpio/SimpleGPIO.cpp -o $(BUILD_DIR)/gpio.o -std=c++11

pwm.o:  | $(BUILD_DIR)
	$(CC) -I $(INCLUDE_PATH)/pwm -c $(INCLUDE_PATH)/pwm/pwm.cpp -o $(BUILD_DIR)/pwm.o -std=c++11

uart.o: | $(BUILD_DIR)
	$(CC) -I $(INCLUDE_PATH)/uart -c $(INCLUDE_PATH)/uart/uart.cpp -o $(BUILD_DIR)/uart.o -std=c++11

$(BUILD_DIR):
	mkdir $(BUILD_DIR)