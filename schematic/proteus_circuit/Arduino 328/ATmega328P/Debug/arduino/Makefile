###############################################################################
# Makefile for Arduino core & libraries
###############################################################################

## General options
MCU = atmega328p
CLOCK = 8000000
COMPILER = "Arduino"
ARDUINO = 187
SHELL = C:\Windows\system32\cmd.exe

## Tools general options
CCFLAGS = -Wall -fsigned-char -MD -MP -DF_CPU=$(CLOCK) -DARDUINO=$(ARDUINO) -mmcu=$(MCU) -Iarduino -Os
ARFLAGS = ruv

## Processing Tools
CC=avr-gcc
AR=ar

## Build tree:

all:	arduino.a

