#!/bin/bash

gcc -Wall -g helper.h modules.c sniffer.c fileio.c -o sniffer 
