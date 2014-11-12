EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:custom
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "12 nov 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L C C4
U 1 1 545804FB
P 1900 4050
F 0 "C4" H 1900 4150 40  0000 L CNN
F 1 "1uF" H 1906 3965 40  0000 L CNN
F 2 "~" H 1938 3900 30  0000 C CNN
F 3 "~" H 1900 4050 60  0000 C CNN
	1    1900 4050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR01
U 1 1 54580501
P 1600 4050
F 0 "#PWR01" H 1600 4050 30  0001 C CNN
F 1 "GND" H 1600 3980 30  0001 C CNN
F 2 "" H 1600 4050 60  0000 C CNN
F 3 "" H 1600 4050 60  0000 C CNN
	1    1600 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	1700 4050 1600 4050
$Comp
L R R3
U 1 1 545805E8
P 1850 3800
F 0 "R3" V 1930 3800 40  0000 C CNN
F 1 "22" V 1857 3801 40  0000 C CNN
F 2 "~" V 1780 3800 30  0000 C CNN
F 3 "~" H 1850 3800 30  0000 C CNN
	1    1850 3800
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 545805FA
P 1850 3600
F 0 "R2" V 1930 3600 40  0000 C CNN
F 1 "22" V 1857 3601 40  0000 C CNN
F 2 "~" V 1780 3600 30  0000 C CNN
F 3 "~" H 1850 3600 30  0000 C CNN
	1    1850 3600
	0    -1   -1   0   
$EndComp
$Comp
L SW_PUSH_SMALL SW1
U 1 1 54580AA8
P 2500 1850
F 0 "SW1" H 2650 1960 30  0000 C CNN
F 1 "SW_PUSH_SMALL" H 2500 1771 30  0000 C CNN
F 2 "~" H 2500 1850 60  0000 C CNN
F 3 "~" H 2500 1850 60  0000 C CNN
	1    2500 1850
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 54580AFB
P 2350 2050
F 0 "R4" V 2430 2050 40  0000 C CNN
F 1 "1k" V 2357 2051 40  0000 C CNN
F 2 "~" V 2280 2050 30  0000 C CNN
F 3 "~" H 2350 2050 30  0000 C CNN
	1    2350 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 2050 2100 2050
$Comp
L GND #PWR02
U 1 1 54580CD0
P 2000 1750
F 0 "#PWR02" H 2000 1750 30  0001 C CNN
F 1 "GND" H 2000 1680 30  0001 C CNN
F 2 "" H 2000 1750 60  0000 C CNN
F 3 "" H 2000 1750 60  0000 C CNN
	1    2000 1750
	0    1    1    0   
$EndComp
Entry Wire Line
	5900 5900 6000 6000
$Comp
L SW_PUSH_SMALL SW2
U 1 1 5458175B
P 6400 6100
F 0 "SW2" H 6550 6210 30  0000 C CNN
F 1 "SW_PUSH_SMALL" H 6400 6021 30  0000 C CNN
F 2 "~" H 6400 6100 60  0000 C CNN
F 3 "~" H 6400 6100 60  0000 C CNN
	1    6400 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 6000 6500 6000
Text Label 6000 6000 0    60   ~ 0
HWB
$Comp
L R R6
U 1 1 5458183C
P 6750 6000
F 0 "R6" V 6830 6000 40  0000 C CNN
F 1 "1k" V 6757 6001 40  0000 C CNN
F 2 "~" V 6680 6000 30  0000 C CNN
F 3 "~" H 6750 6000 30  0000 C CNN
	1    6750 6000
	0    -1   -1   0   
$EndComp
Connection ~ 6300 6000
Wire Wire Line
	6500 6200 6500 6300
$Comp
L GND #PWR03
U 1 1 54581914
P 6500 6300
F 0 "#PWR03" H 6500 6300 30  0001 C CNN
F 1 "GND" H 6500 6230 30  0001 C CNN
F 2 "" H 6500 6300 60  0000 C CNN
F 3 "" H 6500 6300 60  0000 C CNN
	1    6500 6300
	1    0    0    -1  
$EndComp
Entry Wire Line
	5800 2250 5900 2350
Entry Wire Line
	5800 2350 5900 2450
Entry Wire Line
	5800 2450 5900 2550
Entry Wire Line
	5800 2550 5900 2650
Entry Wire Line
	5800 2750 5900 2850
Entry Wire Line
	5800 2850 5900 2950
Entry Wire Line
	5800 2650 5900 2750
Entry Wire Line
	5800 2950 5900 3050
$Comp
L C C5
U 1 1 5459532C
P 3850 1800
F 0 "C5" H 3850 1900 40  0000 L CNN
F 1 "1uF" H 3856 1715 40  0000 L CNN
F 2 "~" H 3888 1650 30  0000 C CNN
F 3 "~" H 3850 1800 60  0000 C CNN
	1    3850 1800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR04
U 1 1 545953BD
P 3550 1800
F 0 "#PWR04" H 3550 1800 30  0001 C CNN
F 1 "GND" H 3550 1730 30  0001 C CNN
F 2 "" H 3550 1800 60  0000 C CNN
F 3 "" H 3550 1800 60  0000 C CNN
	1    3550 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 1600 10100 1600
Entry Wire Line
	10100 1600 10200 1700
Entry Wire Line
	10100 1700 10200 1800
Entry Wire Line
	10100 1800 10200 1900
Entry Wire Line
	10100 2600 10200 2700
Entry Wire Line
	10100 2700 10200 2800
Entry Wire Line
	10100 2800 10200 2900
Entry Wire Line
	10100 2900 10200 3000
Entry Wire Line
	10100 3000 10200 3100
Entry Wire Line
	10100 3100 10200 3200
$Comp
L AT90S8515-P IC2
U 1 1 545A62EA
P 8600 3300
F 0 "IC2" H 7750 5180 40  0000 L BNN
F 1 "AT90S8515-P" H 9050 1350 40  0000 L BNN
F 2 "DIL40" H 8600 3300 30  0000 C CIN
F 3 "" H 8600 3300 60  0000 C CNN
	1    8600 3300
	1    0    0    -1  
$EndComp
NoConn ~ 9600 2450
Entry Wire Line
	10100 3450 10200 3550
Entry Wire Line
	10100 3550 10200 3650
Entry Wire Line
	10100 3650 10200 3750
Entry Wire Line
	10100 3750 10200 3850
Entry Wire Line
	10100 3850 10200 3950
Entry Wire Line
	10100 3950 10200 4050
Entry Wire Line
	10100 4150 10200 4250
Entry Wire Line
	10100 4050 10200 4150
NoConn ~ 7600 4700
NoConn ~ 7600 4800
NoConn ~ 7600 1600
Wire Wire Line
	9600 1700 10100 1700
Wire Wire Line
	9600 1800 10100 1800
Wire Wire Line
	9600 1900 10100 1900
Wire Wire Line
	9600 2000 10100 2000
Wire Wire Line
	9600 2100 10100 2100
Wire Wire Line
	9600 2200 10100 2200
Wire Wire Line
	9600 2300 10100 2300
Text Label 9700 1600 0    60   ~ 0
A
Text Label 9700 1700 0    60   ~ 0
B
Text Label 9700 1800 0    60   ~ 0
C
Text Label 9700 1900 0    60   ~ 0
G
Wire Wire Line
	9600 2600 10100 2600
Wire Wire Line
	9600 2700 10100 2700
Wire Wire Line
	9600 2800 10100 2800
Wire Wire Line
	9600 2900 10100 2900
Wire Wire Line
	9600 3000 10100 3000
Wire Wire Line
	9600 3100 10100 3100
Wire Wire Line
	9600 3200 10100 3200
Wire Wire Line
	9600 3300 10100 3300
Text Label 9700 2600 0    60   ~ 0
DL2
Text Label 9700 2700 0    60   ~ 0
DR1
Text Label 9700 2800 0    60   ~ 0
DR2
Text Label 9700 2900 0    60   ~ 0
DL1
Text Label 9700 3200 0    60   ~ 0
SCL
Text Label 9700 3300 0    60   ~ 0
SDA
Wire Wire Line
	9600 3450 10100 3450
Wire Wire Line
	9600 3550 10100 3550
Wire Wire Line
	9600 3650 10100 3650
Wire Wire Line
	9600 3750 10100 3750
Wire Wire Line
	9600 3850 10100 3850
Wire Wire Line
	9600 3950 10100 3950
Wire Wire Line
	9600 4050 10100 4050
Wire Wire Line
	9600 4150 10100 4150
Text Label 9700 3450 0    60   ~ 0
R1
Text Label 9700 3550 0    60   ~ 0
R2
Text Label 9700 3650 0    60   ~ 0
R3
Text Label 9700 3750 0    60   ~ 0
R4
Text Label 9700 3850 0    60   ~ 0
R5
Text Label 9700 3950 0    60   ~ 0
R6
Text Label 9700 4050 0    60   ~ 0
R7
Text Label 9700 4150 0    60   ~ 0
R8
Wire Wire Line
	9600 4300 10100 4300
Wire Wire Line
	9600 4400 10100 4400
Wire Wire Line
	9600 4500 10100 4500
Wire Wire Line
	9600 4600 10100 4600
Wire Wire Line
	9600 4700 10100 4700
Wire Wire Line
	9600 4800 10100 4800
Wire Wire Line
	9600 4900 10100 4900
Wire Wire Line
	9600 5000 10100 5000
Text Label 9700 4400 0    60   ~ 0
FS1
Text Label 9700 4800 0    60   ~ 0
FS3
Text Label 9700 5000 0    60   ~ 0
FS2
$Comp
L GND #PWR05
U 1 1 545A7377
P 8600 5400
F 0 "#PWR05" H 8600 5400 30  0001 C CNN
F 1 "GND" H 8600 5330 30  0001 C CNN
F 2 "" H 8600 5400 60  0000 C CNN
F 3 "" H 8600 5400 60  0000 C CNN
	1    8600 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 5300 8600 5400
Text Label 9700 4500 0    60   ~ 0
CLOCK
Text Label 9700 4600 0    60   ~ 0
DATA
NoConn ~ 10100 4500
NoConn ~ 10100 4600
Text Label 9700 3000 0    60   ~ 0
KP
Text Label 9700 3100 0    60   ~ 0
PGM
Text Label 9700 2300 0    60   ~ 0
BUZZ
NoConn ~ 7600 2100
NoConn ~ 7600 2500
$Comp
L VCC #PWR06
U 1 1 545A7429
P 8600 1200
F 0 "#PWR06" H 8600 1300 30  0001 C CNN
F 1 "VCC" H 8600 1300 30  0000 C CNN
F 2 "" H 8600 1200 60  0000 C CNN
F 3 "" H 8600 1200 60  0000 C CNN
	1    8600 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 1200 8600 1300
$Comp
L VCC #PWR07
U 1 1 545A74CA
P 4150 1700
F 0 "#PWR07" H 4150 1800 30  0001 C CNN
F 1 "VCC" H 4150 1800 30  0000 C CNN
F 2 "" H 4150 1700 60  0000 C CNN
F 3 "" H 4150 1700 60  0000 C CNN
	1    4150 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 1700 4150 2000
$Comp
L GND #PWR08
U 1 1 545A7565
P 4100 5500
F 0 "#PWR08" H 4100 5500 30  0001 C CNN
F 1 "GND" H 4100 5430 30  0001 C CNN
F 2 "" H 4100 5500 60  0000 C CNN
F 3 "" H 4100 5500 60  0000 C CNN
	1    4100 5500
	1    0    0    -1  
$EndComp
Entry Wire Line
	5800 3450 5900 3550
Entry Wire Line
	5800 3550 5900 3650
Entry Wire Line
	5800 3650 5900 3750
Entry Wire Line
	5800 3750 5900 3850
Entry Wire Line
	5800 3950 5900 4050
Entry Wire Line
	5800 4050 5900 4150
Entry Wire Line
	5800 3850 5900 3950
Entry Wire Line
	5800 4150 5900 4250
NoConn ~ 3100 2650
Wire Wire Line
	3650 1800 3550 1800
Wire Wire Line
	4150 1800 4050 1800
Wire Wire Line
	2100 4050 2200 4050
NoConn ~ 3100 2850
Connection ~ 2600 2050
Wire Wire Line
	2000 1750 2400 1750
Wire Wire Line
	2100 3600 3100 3600
Wire Wire Line
	2100 3700 3100 3700
Wire Wire Line
	2100 3700 2100 3800
Wire Bus Line
	5900 5900 5900 850 
Wire Bus Line
	5900 850  10200 850 
Wire Bus Line
	10200 850  10200 5100
Text Label 5400 4150 0    60   ~ 0
G
Text Label 5400 4050 0    60   ~ 0
C
Text Label 5400 3950 0    60   ~ 0
B
Text Label 5400 3850 0    60   ~ 0
A
Text Label 5400 2250 0    60   ~ 0
R1
Text Label 5400 2350 0    60   ~ 0
R2
Text Label 5400 2450 0    60   ~ 0
R3
Text Label 5400 2550 0    60   ~ 0
R4
Text Label 5400 2650 0    60   ~ 0
R5
Text Label 5400 2750 0    60   ~ 0
R6
Text Label 5400 2850 0    60   ~ 0
R7
Text Label 5400 2950 0    60   ~ 0
R8
Wire Wire Line
	1300 3600 1600 3600
Text Label 5400 4650 0    60   ~ 0
DL2
Text Label 5400 4750 0    60   ~ 0
DR1
Text Label 5400 4850 0    60   ~ 0
DR2
Text Label 5400 4950 0    60   ~ 0
DL1
$Comp
L VCC #PWR09
U 1 1 545A7C1C
P 2000 2050
F 0 "#PWR09" H 2000 2150 30  0001 C CNN
F 1 "VCC" H 2000 2150 30  0000 C CNN
F 2 "" H 2000 2050 60  0000 C CNN
F 3 "" H 2000 2050 60  0000 C CNN
	1    2000 2050
	0    -1   -1   0   
$EndComp
Text Label 2300 3600 0    60   ~ 0
D+
Text Label 2300 3650 0    60   ~ 0
D-
Wire Wire Line
	7000 6000 7100 6000
$Comp
L VCC #PWR010
U 1 1 545A957B
P 7100 6000
F 0 "#PWR010" H 7100 6100 30  0001 C CNN
F 1 "VCC" H 7100 6100 30  0000 C CNN
F 2 "" H 7100 6000 60  0000 C CNN
F 3 "" H 7100 6000 60  0000 C CNN
	1    7100 6000
	0    1    1    0   
$EndComp
NoConn ~ 10100 1900
NoConn ~ 10100 2000
NoConn ~ 10100 2100
NoConn ~ 10100 2200
NoConn ~ 10100 2300
Text Label 9700 4300 0    60   ~ 0
GND
NoConn ~ 10100 4700
NoConn ~ 10100 4900
Text Label 5400 3250 0    60   ~ 0
KP
Text Label 5400 3150 0    60   ~ 0
PGM
$Comp
L ATMEGA32U4-A U1
U 1 1 5462E0B1
P 4250 3800
F 0 "U1" H 3300 5500 40  0000 C CNN
F 1 "ATMEGA32U4-A" H 4950 2300 40  0000 C CNN
F 2 "TQFP44" H 4250 3800 35  0000 C CIN
F 3 "" H 5350 4900 60  0000 C CNN
	1    4250 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4650 3100 5400
Wire Wire Line
	2100 2050 2100 3450
Wire Wire Line
	2100 3450 3100 3450
Wire Wire Line
	2600 2250 3100 2250
Connection ~ 2600 2250
Wire Wire Line
	2600 1950 2600 2250
Wire Wire Line
	3800 2000 4500 2000
Connection ~ 4050 2000
Connection ~ 4150 2000
Connection ~ 4400 2000
Connection ~ 4150 1800
Wire Wire Line
	5350 2250 5800 2250
Wire Wire Line
	5350 2350 5800 2350
Wire Wire Line
	5350 2450 5800 2450
Wire Wire Line
	5350 2550 5800 2550
Wire Wire Line
	5350 2650 5800 2650
Wire Wire Line
	5350 2750 5800 2750
Wire Wire Line
	5350 2850 5800 2850
Wire Wire Line
	5350 2950 5800 2950
Wire Wire Line
	5350 4650 5800 4650
Wire Wire Line
	5350 4750 5800 4750
Wire Wire Line
	5350 4850 5800 4850
Wire Wire Line
	5350 3850 5800 3850
Wire Wire Line
	5350 3950 5800 3950
Wire Wire Line
	5350 4050 5800 4050
Wire Wire Line
	5350 4150 5800 4150
Wire Wire Line
	5350 4350 5800 4350
Entry Wire Line
	5800 4350 5900 4450
Entry Wire Line
	5800 3150 5900 3250
Entry Wire Line
	5800 3250 5900 3350
Entry Wire Line
	5800 4650 5900 4750
Entry Wire Line
	5800 4750 5900 4850
Entry Wire Line
	5800 4850 5900 4950
Entry Wire Line
	5800 4950 5900 5050
Entry Wire Line
	5800 5050 5900 5150
Entry Wire Line
	5800 5150 5900 5250
Entry Wire Line
	5800 4450 5900 4550
Wire Wire Line
	5350 3150 5800 3150
Wire Wire Line
	5350 3250 5800 3250
Wire Wire Line
	3100 5400 4400 5400
Connection ~ 4300 5400
Connection ~ 4200 5400
Wire Wire Line
	4100 5400 4100 5500
Connection ~ 4100 5400
Connection ~ 3850 5400
Text Label 5400 4350 0    60   ~ 0
HWB
Wire Wire Line
	5350 4950 5800 4950
Wire Wire Line
	5350 3450 5800 3450
Wire Wire Line
	5350 3550 5800 3550
Text Label 5400 3450 0    60   ~ 0
SCL
Text Label 5400 3550 0    60   ~ 0
SDA
Wire Wire Line
	5350 3650 5800 3650
Wire Wire Line
	5350 3750 5800 3750
Wire Wire Line
	5350 4450 5800 4450
Text Label 5400 4450 0    60   ~ 0
BUZZ
NoConn ~ 10100 4400
NoConn ~ 10100 4800
NoConn ~ 10100 5000
Entry Wire Line
	10100 3200 10200 3300
Entry Wire Line
	10100 3300 10200 3400
Entry Wire Line
	10100 4300 10200 4400
Text Label 2700 2250 0    60   ~ 0
RESET
Wire Wire Line
	2200 4050 2200 3850
Wire Wire Line
	2200 3850 3100 3850
Text Label 2300 3850 0    60   ~ 0
UCAP
$Comp
L CONN_2 P1
U 1 1 5462FB05
P 950 3700
F 0 "P1" V 900 3700 40  0000 C CNN
F 1 "CONN_2" V 1000 3700 40  0000 C CNN
F 2 "" H 950 3700 60  0000 C CNN
F 3 "" H 950 3700 60  0000 C CNN
	1    950  3700
	-1   0    0    1   
$EndComp
Wire Wire Line
	1600 3800 1300 3800
$EndSCHEMATC
