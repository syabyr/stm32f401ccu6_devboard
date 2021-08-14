EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x20 J3
U 1 1 5FD6D63F
P 6050 2600
F 0 "J3" H 5968 1375 50  0000 C CNN
F 1 "Conn_01x20" H 5968 1466 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Vertical" H 6050 2600 50  0001 C CNN
F 3 "~" H 6050 2600 50  0001 C CNN
	1    6050 2600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x20 J4
U 1 1 5FD6E1AF
P 4600 2550
F 0 "J4" H 4518 1325 50  0000 C CNN
F 1 "Conn_01x20" H 4518 1416 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Vertical" H 4600 2550 50  0001 C CNN
F 3 "~" H 4600 2550 50  0001 C CNN
	1    4600 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3600 5850 3600
Wire Wire Line
	5800 3500 5850 3500
Wire Wire Line
	5800 3400 5850 3400
Wire Wire Line
	5800 3300 5850 3300
Wire Wire Line
	5800 3200 5850 3200
Wire Wire Line
	5800 3100 5850 3100
Wire Wire Line
	5800 3000 5850 3000
Wire Wire Line
	5800 2900 5850 2900
Wire Wire Line
	5800 2800 5850 2800
Wire Wire Line
	5800 2700 5850 2700
Wire Wire Line
	5800 2600 5850 2600
Wire Wire Line
	5800 2500 5850 2500
Wire Wire Line
	5800 2400 5850 2400
Wire Wire Line
	5800 2300 5850 2300
Wire Wire Line
	5800 2200 5850 2200
Wire Wire Line
	5800 2100 5850 2100
Wire Wire Line
	5800 2000 5850 2000
Wire Wire Line
	5800 1900 5850 1900
Wire Wire Line
	4350 1650 4400 1650
Wire Wire Line
	4350 1750 4400 1750
Wire Wire Line
	4350 1850 4400 1850
Wire Wire Line
	4350 1950 4400 1950
Wire Wire Line
	4350 2050 4400 2050
Wire Wire Line
	4350 2150 4400 2150
Wire Wire Line
	4350 2250 4400 2250
Wire Wire Line
	4350 2350 4400 2350
Wire Wire Line
	4350 2450 4400 2450
Wire Wire Line
	4350 2550 4400 2550
Wire Wire Line
	4350 2650 4400 2650
Wire Wire Line
	4350 2750 4400 2750
Wire Wire Line
	4350 2850 4400 2850
Wire Wire Line
	4350 2950 4400 2950
Wire Wire Line
	4350 3050 4400 3050
Wire Wire Line
	4350 3150 4400 3150
Wire Wire Line
	4350 3250 4400 3250
Wire Wire Line
	4350 3350 4400 3350
Wire Wire Line
	4350 3450 4400 3450
Wire Wire Line
	4350 3550 4400 3550
Text GLabel 4350 1650 0    50   Input ~ 0
PB12
Text GLabel 4350 1750 0    50   Input ~ 0
PB13
Text GLabel 4350 1850 0    50   Input ~ 0
PB14
Text GLabel 4350 1950 0    50   Input ~ 0
PB15
Text GLabel 4350 2050 0    50   Input ~ 0
PA8
Text GLabel 4350 2150 0    50   Input ~ 0
PA9
Text GLabel 4350 2250 0    50   Input ~ 0
PA10
Text GLabel 4350 2350 0    50   Input ~ 0
PA11
Text GLabel 4350 2450 0    50   Input ~ 0
PA12
Text GLabel 4350 2550 0    50   Input ~ 0
PA15
Text GLabel 4350 2650 0    50   Input ~ 0
PB3
Text GLabel 4350 2750 0    50   Input ~ 0
PB4
Text GLabel 4350 2850 0    50   Input ~ 0
PB5
Text GLabel 4350 2950 0    50   Input ~ 0
PB6
Text GLabel 4350 3050 0    50   Input ~ 0
PB7
Text GLabel 4350 3150 0    50   Input ~ 0
PB8
Text GLabel 4350 3250 0    50   Input ~ 0
PB9
$Comp
L power:+5V #PWR0123
U 1 1 5FD7D5F6
P 4350 3350
F 0 "#PWR0123" H 4350 3200 50  0001 C CNN
F 1 "+5V" V 4365 3478 50  0000 L CNN
F 2 "" H 4350 3350 50  0001 C CNN
F 3 "" H 4350 3350 50  0001 C CNN
	1    4350 3350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 5FD7E0B4
P 4350 3450
F 0 "#PWR0124" H 4350 3200 50  0001 C CNN
F 1 "GND" V 4355 3322 50  0000 R CNN
F 2 "" H 4350 3450 50  0001 C CNN
F 3 "" H 4350 3450 50  0001 C CNN
	1    4350 3450
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR0125
U 1 1 5FD7E67B
P 4350 3550
F 0 "#PWR0125" H 4350 3400 50  0001 C CNN
F 1 "+3V3" V 4365 3678 50  0000 L CNN
F 2 "" H 4350 3550 50  0001 C CNN
F 3 "" H 4350 3550 50  0001 C CNN
	1    4350 3550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0126
U 1 1 5FD7F6E5
P 5800 1800
F 0 "#PWR0126" H 5800 1550 50  0001 C CNN
F 1 "GND" V 5805 1672 50  0000 R CNN
F 2 "" H 5800 1800 50  0001 C CNN
F 3 "" H 5800 1800 50  0001 C CNN
	1    5800 1800
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR0127
U 1 1 5FD81483
P 5800 1900
F 0 "#PWR0127" H 5800 1750 50  0001 C CNN
F 1 "+3V3" V 5815 2028 50  0000 L CNN
F 2 "" H 5800 1900 50  0001 C CNN
F 3 "" H 5800 1900 50  0001 C CNN
	1    5800 1900
	0    -1   -1   0   
$EndComp
Text GLabel 5800 3200 0    50   Input ~ 0
NRST
Text GLabel 5800 2000 0    50   Input ~ 0
PB10
Text GLabel 5800 2100 0    50   Input ~ 0
PB2
Text GLabel 5800 2200 0    50   Input ~ 0
PB1
Text GLabel 5800 2300 0    50   Input ~ 0
PB0
Text GLabel 5800 2400 0    50   Input ~ 0
PA7
Text GLabel 5800 2500 0    50   Input ~ 0
PA6
Text GLabel 5800 2600 0    50   Input ~ 0
PA5
Text GLabel 5800 2700 0    50   Input ~ 0
PA4
Text GLabel 5800 2800 0    50   Input ~ 0
PA3
Text GLabel 5800 2900 0    50   Input ~ 0
PA2
Text GLabel 5800 3000 0    50   Input ~ 0
PA1
Text GLabel 5800 3100 0    50   Input ~ 0
PA0
Text GLabel 5800 3300 0    50   Input ~ 0
PC15
Text GLabel 5800 3400 0    50   Input ~ 0
PC14
Text GLabel 5800 3500 0    50   Input ~ 0
PC13
$Comp
L power:+BATT #PWR0128
U 1 1 5FD8401C
P 5800 3600
F 0 "#PWR0128" H 5800 3450 50  0001 C CNN
F 1 "+BATT" V 5815 3728 50  0000 L CNN
F 2 "" H 5800 3600 50  0001 C CNN
F 3 "" H 5800 3600 50  0001 C CNN
	1    5800 3600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5850 1800 5800 1800
Wire Wire Line
	5850 1700 5800 1700
$Comp
L power:+5V #PWR0129
U 1 1 5FDB1132
P 5800 1700
F 0 "#PWR0129" H 5800 1550 50  0001 C CNN
F 1 "+5V" V 5815 1828 50  0000 L CNN
F 2 "" H 5800 1700 50  0001 C CNN
F 3 "" H 5800 1700 50  0001 C CNN
	1    5800 1700
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
