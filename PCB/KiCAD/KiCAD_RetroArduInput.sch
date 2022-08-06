EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A2 23386 16535
encoding utf-8
Sheet 1 1
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
L Interface_UART:MAX232 IC1
U 1 1 6072C05B
P 5300 7200
F 0 "IC1" H 5300 8581 50  0000 C CNN
F 1 "MAX232" H 5300 8490 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 5350 6150 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/max232.pdf" H 5300 7300 50  0001 C CNN
	1    5300 7200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 607317E7
P 4150 6450
F 0 "C1" H 4268 6496 50  0000 L CNN
F 1 "10μF 50V" H 4268 6405 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 4188 6300 50  0001 C CNN
F 3 "~" H 4150 6450 50  0001 C CNN
	1    4150 6450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 60733C2B
P 6300 6450
F 0 "C2" H 6418 6496 50  0000 L CNN
F 1 "10μF 50V" H 6418 6405 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 6338 6300 50  0001 C CNN
F 3 "~" H 6300 6450 50  0001 C CNN
	1    6300 6450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C3
U 1 1 60734974
P 5900 5550
F 0 "C3" V 5645 5550 50  0000 C CNN
F 1 "10μF 50V" V 5736 5550 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 5938 5400 50  0001 C CNN
F 3 "~" H 5900 5550 50  0001 C CNN
	1    5900 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	4150 6300 4500 6300
Wire Wire Line
	4500 6600 4150 6600
Wire Wire Line
	6100 6300 6300 6300
Wire Wire Line
	6300 6600 6100 6600
$Comp
L Device:CP C4
U 1 1 60736E1D
P 6250 7100
F 0 "C4" V 5995 7100 50  0000 C CNN
F 1 "10μF 50V" V 6086 7100 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 6288 6950 50  0001 C CNN
F 3 "~" H 6250 7100 50  0001 C CNN
	1    6250 7100
	0    1    1    0   
$EndComp
$Comp
L Device:CP C5
U 1 1 607392A9
P 5700 6000
F 0 "C5" V 5955 6000 50  0000 C CNN
F 1 "10μF 50V" V 5864 6000 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 5738 5850 50  0001 C CNN
F 3 "~" H 5700 6000 50  0001 C CNN
	1    5700 6000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5300 6000 5400 6000
Wire Wire Line
	5300 8400 6400 8400
Wire Wire Line
	6400 8400 6400 8000
Wire Wire Line
	6400 7100 6650 7100
Wire Wire Line
	6650 7100 6650 6000
Wire Wire Line
	6650 6000 5850 6000
Connection ~ 6400 7100
$Comp
L Connector:DB9_Female CN2
U 1 1 6073B64A
P 7500 7600
F 0 "CN2" H 7680 7646 50  0000 L CNN
F 1 "DB9_Female" H 7680 7555 50  0000 L CNN
F 2 "Connector_Dsub:DSUB-9_Female_Horizontal_P2.77x2.84mm_EdgePinOffset9.90mm_Housed_MountingHolesOffset11.32mm" H 7500 7600 50  0001 C CNN
F 3 " ~" H 7500 7600 50  0001 C CNN
	1    7500 7600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 7900 6650 7900
Wire Wire Line
	6650 7900 6650 7500
Wire Wire Line
	6650 7500 7200 7500
Wire Wire Line
	6100 7300 7000 7300
Wire Wire Line
	7200 8000 6400 8000
Connection ~ 6400 8000
Wire Wire Line
	6400 8000 6400 7100
$Comp
L power:GND #PWR0101
U 1 1 60745471
P 6400 8400
F 0 "#PWR0101" H 6400 8150 50  0001 C CNN
F 1 "GND" H 6405 8227 50  0000 C CNN
F 2 "" H 6400 8400 50  0001 C CNN
F 3 "" H 6400 8400 50  0001 C CNN
	1    6400 8400
	1    0    0    -1  
$EndComp
Connection ~ 6400 8400
$Comp
L Connector:Conn_01x03_Female SW1
U 1 1 6075E1F0
P 16000 10950
F 0 "SW1" V 15846 11098 50  0000 L CNN
F 1 "Switch 1xOn-On" V 15937 11098 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 16000 10950 50  0001 C CNN
F 3 "~" H 16000 10950 50  0001 C CNN
	1    16000 10950
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW2
U 1 1 6076443B
P 16000 11250
F 0 "SW2" V 15846 11398 50  0000 L CNN
F 1 "Switch 1xOn-On" V 15937 11398 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 16000 11250 50  0001 C CNN
F 3 "~" H 16000 11250 50  0001 C CNN
	1    16000 11250
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW3
U 1 1 60765229
P 16000 11550
F 0 "SW3" V 15846 11698 50  0000 L CNN
F 1 "Switch 1xOn-On" V 15937 11698 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 16000 11550 50  0001 C CNN
F 3 "~" H 16000 11550 50  0001 C CNN
	1    16000 11550
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW4
U 1 1 60765D8F
P 16000 11850
F 0 "SW4" V 15846 11998 50  0000 L CNN
F 1 "Switch 1xOn-On" V 15937 11998 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 16000 11850 50  0001 C CNN
F 3 "~" H 16000 11850 50  0001 C CNN
	1    16000 11850
	0    1    1    0   
$EndComp
Wire Wire Line
	16000 10750 16000 10700
Wire Wire Line
	16000 10700 17100 10700
Wire Wire Line
	17100 10700 17100 10850
Wire Wire Line
	16000 11050 16000 11000
Wire Wire Line
	16000 11000 17100 11000
Wire Wire Line
	17100 11000 17100 10950
Wire Wire Line
	16000 11350 16000 11300
Wire Wire Line
	16000 11300 16800 11300
Wire Wire Line
	16800 11300 16800 11050
Wire Wire Line
	16800 11050 17100 11050
Wire Wire Line
	16000 11650 16000 11600
Wire Wire Line
	16000 11600 16850 11600
Wire Wire Line
	16850 11600 16850 11150
Wire Wire Line
	16850 11150 17100 11150
Wire Wire Line
	17100 11350 16400 11350
Wire Wire Line
	16400 11350 16400 11450
Wire Wire Line
	16400 11450 15950 11450
Wire Wire Line
	15950 11450 15950 11350
Wire Wire Line
	15950 11350 15900 11350
$Comp
L power:GND #PWR0102
U 1 1 6076A396
P 15800 11800
F 0 "#PWR0102" H 15800 11550 50  0001 C CNN
F 1 "GND" H 15805 11627 50  0000 C CNN
F 2 "" H 15800 11800 50  0001 C CNN
F 3 "" H 15800 11800 50  0001 C CNN
	1    15800 11800
	1    0    0    -1  
$EndComp
Wire Wire Line
	15800 11800 15800 11650
Wire Wire Line
	15800 11650 15900 11650
Wire Wire Line
	15900 11650 15900 11550
Wire Wire Line
	15900 11550 16150 11550
Wire Wire Line
	16150 11550 16150 11350
Wire Wire Line
	16150 11350 16100 11350
Connection ~ 15900 11650
$Comp
L power:VCC #PWR0103
U 1 1 6077647A
P 5500 5850
F 0 "#PWR0103" H 5500 5700 50  0001 C CNN
F 1 "VCC" H 5515 6023 50  0000 C CNN
F 2 "" H 5500 5850 50  0001 C CNN
F 3 "" H 5500 5850 50  0001 C CNN
	1    5500 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5850 5500 6000
Connection ~ 5500 6000
Wire Wire Line
	5500 6000 5550 6000
$Comp
L arduino:Arduino_Mega2560_Shield CN0
U 1 1 6077A1C8
P 10950 10050
F 0 "CN0" H 10950 7669 60  0000 C CNN
F 1 "Arduino Mega2560+USB Host Shield" H 10950 7563 60  0000 C CNN
F 2 "Arduino:Arduino_Mega2560_Shield_Reduced" H 11650 12800 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-mega-2560-rev3" H 11650 12800 60  0001 C CNN
	1    10950 10050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 8400 7850 8700
Wire Wire Line
	7850 8700 4150 8700
Wire Wire Line
	4150 8700 4150 7300
Wire Wire Line
	4150 7300 4500 7300
Wire Wire Line
	7750 8300 7750 8650
Wire Wire Line
	7750 8650 4200 8650
Wire Wire Line
	4200 8650 4200 7700
Wire Wire Line
	4200 7700 4500 7700
Wire Wire Line
	4100 8800 4100 7900
Wire Wire Line
	4100 7900 4500 7900
Wire Wire Line
	15900 10750 15800 10750
Wire Wire Line
	14650 10750 14650 11200
Wire Wire Line
	14650 11200 12250 11200
Wire Wire Line
	15800 10750 15800 10600
Wire Wire Line
	15800 10600 16500 10600
Wire Wire Line
	16500 10600 16500 11650
Wire Wire Line
	16500 11650 16100 11650
Connection ~ 15800 10750
Wire Wire Line
	15800 10750 14650 10750
Wire Wire Line
	12250 11400 14700 11400
Wire Wire Line
	14700 11400 14700 11050
Wire Wire Line
	14700 11050 15700 11050
Wire Wire Line
	15700 11050 15700 10500
Wire Wire Line
	15700 10500 16100 10500
Wire Wire Line
	16100 10500 16100 10750
Connection ~ 15700 11050
Wire Wire Line
	15700 11050 15900 11050
Wire Wire Line
	12250 11800 14800 11800
Wire Wire Line
	14800 11800 14800 11350
Wire Wire Line
	14800 11350 15900 11350
Connection ~ 15900 11350
Wire Wire Line
	15600 11600 15600 11150
Wire Wire Line
	15600 11150 16150 11150
Wire Wire Line
	16150 11150 16150 11050
Wire Wire Line
	16150 11050 16100 11050
Wire Wire Line
	12250 11600 15600 11600
Wire Wire Line
	9650 12100 9550 12100
Wire Wire Line
	9550 12100 9550 12000
Wire Wire Line
	9550 12000 9650 12000
Wire Wire Line
	9550 12000 9550 11900
Wire Wire Line
	9550 11900 9650 11900
Connection ~ 9550 12000
Wire Wire Line
	9650 11700 9550 11700
Wire Wire Line
	9550 11700 9550 11600
Wire Wire Line
	9550 11600 9650 11600
Wire Wire Line
	9650 11500 9550 11500
Wire Wire Line
	9550 11500 9550 11600
Connection ~ 9550 11600
Wire Wire Line
	9650 11400 9550 11400
Wire Wire Line
	9550 11400 9550 11500
Connection ~ 9550 11500
Wire Wire Line
	9650 11300 9550 11300
Wire Wire Line
	9550 11300 9550 11400
Connection ~ 9550 11400
$Comp
L power:VCC #PWR0104
U 1 1 6080952E
P 9450 12000
F 0 "#PWR0104" H 9450 11850 50  0001 C CNN
F 1 "VCC" H 9465 12173 50  0000 C CNN
F 2 "" H 9450 12000 50  0001 C CNN
F 3 "" H 9450 12000 50  0001 C CNN
	1    9450 12000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 6080A572
P 9450 11500
F 0 "#PWR0105" H 9450 11250 50  0001 C CNN
F 1 "GND" H 9455 11327 50  0000 C CNN
F 2 "" H 9450 11500 50  0001 C CNN
F 3 "" H 9450 11500 50  0001 C CNN
	1    9450 11500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 11500 9450 11500
Wire Wire Line
	9450 12000 9550 12000
$Comp
L Connector:Conn_01x03_Female SW6
U 1 1 608294C1
P 13050 13150
F 0 "SW6" V 12896 13298 50  0000 L CNN
F 1 "Switch 1xOn-On" V 12987 13298 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 13050 13150 50  0001 C CNN
F 3 "~" H 13050 13150 50  0001 C CNN
	1    13050 13150
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW7
U 1 1 6082D3BF
P 13950 13150
F 0 "SW7" V 13796 13298 50  0000 L CNN
F 1 "Switch 1xOn-On" V 13887 13298 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 13950 13150 50  0001 C CNN
F 3 "~" H 13950 13150 50  0001 C CNN
	1    13950 13150
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW8
U 1 1 60831088
P 14850 13150
F 0 "SW8" V 14696 13298 50  0000 L CNN
F 1 "Switch 1xOn-On" V 14787 13298 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 14850 13150 50  0001 C CNN
F 3 "~" H 14850 13150 50  0001 C CNN
	1    14850 13150
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW9
U 1 1 60838959
P 15750 13150
F 0 "SW9" V 15596 13298 50  0000 L CNN
F 1 "Switch 1xOn-On" V 15687 13298 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 15750 13150 50  0001 C CNN
F 3 "~" H 15750 13150 50  0001 C CNN
	1    15750 13150
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW10
U 1 1 6083C422
P 16650 13150
F 0 "SW10" V 16496 13298 50  0000 L CNN
F 1 "Switch 1xOn-On" V 16587 13298 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 16650 13150 50  0001 C CNN
F 3 "~" H 16650 13150 50  0001 C CNN
	1    16650 13150
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW11
U 1 1 6083FE93
P 17550 13150
F 0 "SW11" V 17396 13298 50  0000 L CNN
F 1 "Switch 1xOn-On" V 17487 13298 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 17550 13150 50  0001 C CNN
F 3 "~" H 17550 13150 50  0001 C CNN
	1    17550 13150
	0    1    1    0   
$EndComp
Wire Wire Line
	12950 12850 12950 12950
Wire Wire Line
	12950 12850 13850 12850
Wire Wire Line
	13850 12850 13850 12950
Wire Wire Line
	13850 12850 14750 12850
Wire Wire Line
	14750 12850 14750 12950
Connection ~ 13850 12850
Wire Wire Line
	14750 12850 15650 12850
Wire Wire Line
	15650 12850 15650 12950
Connection ~ 14750 12850
Wire Wire Line
	15650 12850 16550 12850
Wire Wire Line
	16550 12850 16550 12950
Connection ~ 15650 12850
Wire Wire Line
	16550 12850 17450 12850
Wire Wire Line
	17450 12850 17450 12950
Connection ~ 16550 12850
Wire Wire Line
	13150 12750 13150 12950
Wire Wire Line
	13150 12750 14050 12750
Wire Wire Line
	14050 12750 14050 12950
Wire Wire Line
	14050 12750 14950 12750
Wire Wire Line
	14950 12750 14950 12950
Connection ~ 14050 12750
Wire Wire Line
	14950 12750 15850 12750
Wire Wire Line
	15850 12750 15850 12950
Connection ~ 14950 12750
Wire Wire Line
	15850 12750 16750 12750
Wire Wire Line
	16750 12750 16750 12950
Connection ~ 15850 12750
Wire Wire Line
	16750 12750 17650 12750
Wire Wire Line
	17650 12750 17650 12950
Connection ~ 16750 12750
Wire Wire Line
	14850 12950 14850 10700
Wire Wire Line
	14850 10700 12250 10700
Wire Wire Line
	15750 12950 15750 12100
Wire Wire Line
	14400 12100 14400 10900
Wire Wire Line
	14400 10900 12250 10900
Wire Wire Line
	16650 12950 16650 12200
Wire Wire Line
	16650 12200 14350 12200
Wire Wire Line
	14350 12200 14350 11100
Wire Wire Line
	14350 11100 12250 11100
Wire Wire Line
	15750 12100 14400 12100
Wire Wire Line
	17550 12950 17550 12500
Wire Wire Line
	17550 12500 13950 12500
Wire Wire Line
	13950 12500 13950 9900
Wire Wire Line
	13950 9900 12250 9900
$Comp
L power:VCC #PWR0108
U 1 1 608F9145
P 8300 13050
F 0 "#PWR0108" H 8300 12900 50  0001 C CNN
F 1 "VCC" H 8315 13223 50  0000 C CNN
F 2 "" H 8300 13050 50  0001 C CNN
F 3 "" H 8300 13050 50  0001 C CNN
	1    8300 13050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 608F9E23
P 8300 13150
F 0 "#PWR0109" H 8300 12900 50  0001 C CNN
F 1 "GND" H 8305 12977 50  0000 C CNN
F 2 "" H 8300 13150 50  0001 C CNN
F 3 "" H 8300 13150 50  0001 C CNN
	1    8300 13150
	1    0    0    -1  
$EndComp
$Comp
L Connector:DB15_Male CN1
U 1 1 6091AE19
P 11250 3050
F 0 "CN1" V 11542 3050 50  0000 C CNN
F 1 "DB15_Male" V 11451 3050 50  0000 C CNN
F 2 "Connector_Dsub:DSUB-15_Male_Horizontal_P2.77x2.84mm_EdgePinOffset7.70mm_Housed_MountingHolesOffset9.12mm" H 11250 3050 50  0001 C CNN
F 3 " ~" H 11250 3050 50  0001 C CNN
	1    11250 3050
	0    -1   -1   0   
$EndComp
$Comp
L Connector:DB9_Female CN3
U 1 1 60923AC5
P 16000 7350
F 0 "CN3" H 16180 7396 50  0000 L CNN
F 1 "DB9_Female" H 16180 7305 50  0000 L CNN
F 2 "Connector_Dsub:DSUB-9_Female_Horizontal_P2.77x2.84mm_EdgePinOffset9.90mm_Housed_MountingHolesOffset11.32mm" H 16000 7350 50  0001 C CNN
F 3 " ~" H 16000 7350 50  0001 C CNN
	1    16000 7350
	1    0    0    -1  
$EndComp
$Comp
L Connector:DB9_Female CN4
U 1 1 60927E99
P 16000 6150
F 0 "CN4" H 16180 6196 50  0000 L CNN
F 1 "DB9_Female" H 16180 6105 50  0000 L CNN
F 2 "Connector_Dsub:DSUB-9_Female_Horizontal_P2.77x2.84mm_EdgePinOffset9.90mm_Housed_MountingHolesOffset11.32mm" H 16000 6150 50  0001 C CNN
F 3 " ~" H 16000 6150 50  0001 C CNN
	1    16000 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 8800 8150 8800
Wire Wire Line
	7850 8400 9650 8400
Wire Wire Line
	7750 8300 9650 8300
Wire Wire Line
	8150 8100 9650 8100
Wire Wire Line
	8150 8100 8150 8800
$Comp
L DS18030-010+:DS18030-010+ IC3
U 1 1 609A781B
P 10600 5500
F 0 "IC3" H 11150 5765 50  0000 C CNN
F 1 "DS18030-100+" H 11150 5674 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 11550 5600 50  0001 L CNN
F 3 "http://docs-emea.rs-online.com/webdocs/0a29/0900766b80a29b9d.pdf" H 11550 5500 50  0001 L CNN
F 4 "DS18030-010+, Digital Potentiometer 10k 256-Position Linear 2-channel Serial-2 Wire 16-Pin PDIP N" H 11550 5400 50  0001 L CNN "Description"
F 5 "4.572" H 11550 5300 50  0001 L CNN "Height"
F 6 "Maxim Integrated" H 11550 5200 50  0001 L CNN "Manufacturer_Name"
F 7 "DS18030-010+" H 11550 5100 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "700-DS18030-010" H 11550 5000 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Maxim-Integrated/DS18030-010%2b?qs=0Y9aZN%252BMVCU7WgUs0Blajw%3D%3D" H 11550 4900 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 11550 4800 50  0001 L CNN "Arrow Part Number"
F 11 "" H 11550 4700 50  0001 L CNN "Arrow Price/Stock"
	1    10600 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 8700 9250 8700
Wire Wire Line
	9250 8700 9250 6700
Wire Wire Line
	9250 6700 12100 6700
Wire Wire Line
	12100 6700 12100 6100
Wire Wire Line
	12100 6100 11950 6100
Wire Wire Line
	9650 8800 9350 8800
Wire Wire Line
	9350 8800 9350 6850
Wire Wire Line
	9350 6850 12200 6850
Wire Wire Line
	12200 6200 12150 6200
Wire Wire Line
	12200 6200 12200 6850
$Comp
L DS18030-010+:DS18030-010+ IC2
U 1 1 609B89EA
P 10600 4350
F 0 "IC2" H 11150 4615 50  0000 C CNN
F 1 "DS18030-100+" H 11150 4524 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket" H 11550 4450 50  0001 L CNN
F 3 "http://docs-emea.rs-online.com/webdocs/0a29/0900766b80a29b9d.pdf" H 11550 4350 50  0001 L CNN
F 4 "DS18030-010+, Digital Potentiometer 10k 256-Position Linear 2-channel Serial-2 Wire 16-Pin PDIP N" H 11550 4250 50  0001 L CNN "Description"
F 5 "4.572" H 11550 4150 50  0001 L CNN "Height"
F 6 "Maxim Integrated" H 11550 4050 50  0001 L CNN "Manufacturer_Name"
F 7 "DS18030-010+" H 11550 3950 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "700-DS18030-010" H 11550 3850 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Maxim-Integrated/DS18030-010%2b?qs=0Y9aZN%252BMVCU7WgUs0Blajw%3D%3D" H 11550 3750 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 11550 3650 50  0001 L CNN "Arrow Part Number"
F 11 "" H 11550 3550 50  0001 L CNN "Arrow Price/Stock"
	1    10600 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	11950 6100 11950 4950
Wire Wire Line
	11950 4950 11700 4950
Connection ~ 11950 6100
Wire Wire Line
	11950 6100 11700 6100
Wire Wire Line
	12150 6200 12150 5050
Wire Wire Line
	12150 5050 11700 5050
Connection ~ 12150 6200
Wire Wire Line
	12150 6200 11700 6200
$Comp
L power:GND #PWR0110
U 1 1 609D21B1
P 10600 5050
F 0 "#PWR0110" H 10600 4800 50  0001 C CNN
F 1 "GND" H 10605 4877 50  0000 C CNN
F 2 "" H 10600 5050 50  0001 C CNN
F 3 "" H 10600 5050 50  0001 C CNN
	1    10600 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 609D2DFB
P 10600 6200
F 0 "#PWR0111" H 10600 5950 50  0001 C CNN
F 1 "GND" H 10605 6027 50  0000 C CNN
F 2 "" H 10600 6200 50  0001 C CNN
F 3 "" H 10600 6200 50  0001 C CNN
	1    10600 6200
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0112
U 1 1 609D4009
P 11700 4350
F 0 "#PWR0112" H 11700 4200 50  0001 C CNN
F 1 "VCC" H 11715 4523 50  0000 C CNN
F 2 "" H 11700 4350 50  0001 C CNN
F 3 "" H 11700 4350 50  0001 C CNN
	1    11700 4350
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0113
U 1 1 609D517B
P 11700 5500
F 0 "#PWR0113" H 11700 5350 50  0001 C CNN
F 1 "VCC" H 11715 5673 50  0000 C CNN
F 2 "" H 11700 5500 50  0001 C CNN
F 3 "" H 11700 5500 50  0001 C CNN
	1    11700 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10600 5050 10600 4950
Connection ~ 10600 5050
Wire Wire Line
	10600 4950 10600 4850
Connection ~ 10600 4950
Wire Wire Line
	10600 4850 10600 4750
Connection ~ 10600 4850
Wire Wire Line
	10600 6200 10500 6200
Wire Wire Line
	10500 6200 10500 6000
Wire Wire Line
	10500 6000 10600 6000
Connection ~ 10600 6200
Wire Wire Line
	10600 6000 10600 5900
Connection ~ 10600 6000
$Comp
L power:VCC #PWR0114
U 1 1 609FCE13
P 10450 6100
F 0 "#PWR0114" H 10450 5950 50  0001 C CNN
F 1 "VCC" H 10465 6273 50  0000 C CNN
F 2 "" H 10450 6100 50  0001 C CNN
F 3 "" H 10450 6100 50  0001 C CNN
	1    10450 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10600 6100 10450 6100
Wire Wire Line
	13050 12950 13050 10300
Wire Wire Line
	13050 10300 12250 10300
Wire Wire Line
	13950 12950 13950 12700
Wire Wire Line
	13950 12700 13100 12700
Wire Wire Line
	13100 12700 13100 10100
Wire Wire Line
	13100 10100 12250 10100
Wire Wire Line
	12250 9100 15250 9100
Wire Wire Line
	15250 9100 15250 7050
Wire Wire Line
	15250 7050 15700 7050
Wire Wire Line
	12250 9200 15300 9200
Wire Wire Line
	15300 9200 15300 7650
Wire Wire Line
	15300 7650 15700 7650
Wire Wire Line
	12250 9300 15350 9300
Wire Wire Line
	15350 9300 15350 7150
Wire Wire Line
	15350 7150 15700 7150
Wire Wire Line
	12250 9400 15450 9400
Wire Wire Line
	15450 9400 15450 6950
Wire Wire Line
	15450 6950 15700 6950
Wire Wire Line
	12250 9500 15500 9500
Wire Wire Line
	15500 9500 15500 7550
Wire Wire Line
	15500 7550 15700 7550
Wire Wire Line
	12250 9600 15600 9600
Wire Wire Line
	15600 9600 15600 7350
Wire Wire Line
	15600 7350 15700 7350
Wire Wire Line
	12250 11000 15400 11000
Wire Wire Line
	15400 11000 15400 9750
Wire Wire Line
	15400 9750 14800 9750
Wire Wire Line
	14800 9750 14800 5850
Wire Wire Line
	14800 5850 15700 5850
Wire Wire Line
	12250 10800 14550 10800
Wire Wire Line
	14550 10800 14550 6450
Wire Wire Line
	14550 6450 15700 6450
Wire Wire Line
	12250 10600 14450 10600
Wire Wire Line
	14450 10600 14450 6550
Wire Wire Line
	14450 6550 15700 6550
Wire Wire Line
	12250 10400 14350 10400
Wire Wire Line
	14350 10400 14350 5750
Wire Wire Line
	14350 5750 15700 5750
Wire Wire Line
	12250 10200 14250 10200
Wire Wire Line
	14250 10200 14250 6150
Wire Wire Line
	14250 6150 15700 6150
Wire Wire Line
	12250 10000 14150 10000
Wire Wire Line
	14150 10000 14150 5950
Wire Wire Line
	14150 5950 15700 5950
Wire Wire Line
	12250 9800 14100 9800
Wire Wire Line
	14100 9800 14100 6350
Wire Wire Line
	14100 6350 15700 6350
$Comp
L power:GND #PWR0107
U 1 1 60845192
P 11900 12850
F 0 "#PWR0107" H 11900 12600 50  0001 C CNN
F 1 "GND" H 11905 12677 50  0000 C CNN
F 2 "" H 11900 12850 50  0001 C CNN
F 3 "" H 11900 12850 50  0001 C CNN
	1    11900 12850
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0106
U 1 1 60843B24
P 11900 12750
F 0 "#PWR0106" H 11900 12600 50  0001 C CNN
F 1 "VCC" H 11915 12923 50  0000 C CNN
F 2 "" H 11900 12750 50  0001 C CNN
F 3 "" H 11900 12750 50  0001 C CNN
	1    11900 12750
	1    0    0    -1  
$EndComp
Wire Wire Line
	12150 12950 12150 12500
Wire Wire Line
	12150 12500 12950 12500
Wire Wire Line
	12950 12500 12950 10500
Wire Wire Line
	12950 10500 12250 10500
Wire Wire Line
	11700 4550 11950 4550
Wire Wire Line
	11950 4550 11950 3350
Wire Wire Line
	10600 4350 10550 4350
Wire Wire Line
	10550 4350 10550 3350
Wire Wire Line
	11700 5700 12300 5700
Wire Wire Line
	12300 5700 12300 3450
Wire Wire Line
	12300 3450 11850 3450
Wire Wire Line
	11850 3450 11850 3350
Wire Wire Line
	10600 5500 10300 5500
Wire Wire Line
	10300 5500 10300 3400
Wire Wire Line
	10300 3400 10650 3400
Wire Wire Line
	10650 3400 10650 3350
Wire Wire Line
	11700 4750 12250 4750
Wire Wire Line
	12250 4750 12250 3500
Wire Wire Line
	12250 3500 11550 3500
Wire Wire Line
	11550 3500 11550 3350
Wire Wire Line
	10950 3350 10950 3450
Wire Wire Line
	10950 3450 10350 3450
Wire Wire Line
	10350 3450 10350 4650
Wire Wire Line
	10350 4650 10600 4650
Wire Wire Line
	11450 3350 11450 3550
Wire Wire Line
	11450 3550 12200 3550
Wire Wire Line
	12200 3550 12200 5900
Wire Wire Line
	12200 5900 11700 5900
Wire Wire Line
	11050 3350 11050 3500
Wire Wire Line
	11050 3500 10400 3500
Wire Wire Line
	10400 3500 10400 5800
Wire Wire Line
	10400 5800 10600 5800
$Comp
L Connector:Conn_01x03_Female SW13
U 1 1 60C44A31
P 9100 4450
F 0 "SW13" V 8946 4598 50  0000 L CNN
F 1 "Switch 1xOn-On" V 9037 4598 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 9100 4450 50  0001 C CNN
F 3 "~" H 9100 4450 50  0001 C CNN
	1    9100 4450
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW15
U 1 1 60C46F22
P 9100 4800
F 0 "SW15" V 8946 4948 50  0000 L CNN
F 1 "Switch 1xOn-On" V 9037 4948 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 9100 4800 50  0001 C CNN
F 3 "~" H 9100 4800 50  0001 C CNN
	1    9100 4800
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW12
U 1 1 60C48AEC
P 12900 4500
F 0 "SW12" V 12746 4648 50  0000 L CNN
F 1 "Switch 1xOn-On" V 12837 4648 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 12900 4500 50  0001 C CNN
F 3 "~" H 12900 4500 50  0001 C CNN
	1    12900 4500
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female SW14
U 1 1 60C490B0
P 12900 4850
F 0 "SW14" V 12746 4998 50  0000 L CNN
F 1 "Switch 1xOn-On" V 12837 4998 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 12900 4850 50  0001 C CNN
F 3 "~" H 12900 4850 50  0001 C CNN
	1    12900 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	10600 4550 10150 4550
Wire Wire Line
	10150 4550 10150 3950
Wire Wire Line
	10150 3950 9100 3950
Wire Wire Line
	9100 3950 9100 4250
Wire Wire Line
	10600 5700 10100 5700
Wire Wire Line
	10100 5700 10100 4500
Wire Wire Line
	10100 4500 9100 4500
Wire Wire Line
	9100 4500 9100 4600
Wire Wire Line
	11700 4650 12450 4650
Wire Wire Line
	12450 4650 12450 3900
Wire Wire Line
	12450 3900 12900 3900
Wire Wire Line
	12900 3900 12900 4300
Wire Wire Line
	12900 4650 12900 4550
Wire Wire Line
	12900 4550 12500 4550
Wire Wire Line
	12500 4550 12500 5800
Wire Wire Line
	12500 5800 11700 5800
$Comp
L Connector:Conn_01x03_Female SW5
U 1 1 60B02B5D
P 12150 13150
F 0 "SW5" V 11996 13298 50  0000 L CNN
F 1 "Switch 1xOn-On" V 12087 13298 50  0000 L CNN
F 2 "SamacSys:CS12ANW03" H 12150 13150 50  0001 C CNN
F 3 "~" H 12150 13150 50  0001 C CNN
	1    12150 13150
	0    1    1    0   
$EndComp
Wire Wire Line
	12950 12850 12050 12850
Wire Wire Line
	12050 12850 12050 12950
Connection ~ 12950 12850
Wire Wire Line
	13150 12750 12250 12750
Wire Wire Line
	12250 12750 12250 12950
Connection ~ 13150 12750
Wire Wire Line
	12250 12750 11900 12750
Connection ~ 12250 12750
Wire Wire Line
	11900 12850 12050 12850
Connection ~ 12050 12850
$Comp
L power:GND #PWR0115
U 1 1 60DCABA7
P 11250 2500
F 0 "#PWR0115" H 11250 2250 50  0001 C CNN
F 1 "GND" H 11255 2327 50  0000 C CNN
F 2 "" H 11250 2500 50  0001 C CNN
F 3 "" H 11250 2500 50  0001 C CNN
	1    11250 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	11250 2500 9150 2500
Wire Wire Line
	9150 2500 9150 4250
Wire Wire Line
	9150 4250 9200 4250
Wire Wire Line
	9200 4600 9150 4600
Wire Wire Line
	9150 4600 9150 4250
Connection ~ 9150 4250
Wire Wire Line
	11250 2500 12950 2500
Wire Wire Line
	12950 2500 12950 4300
Wire Wire Line
	12950 4300 13000 4300
Connection ~ 11250 2500
Wire Wire Line
	12950 4300 12950 4650
Wire Wire Line
	12950 4650 13000 4650
Connection ~ 12950 4300
Wire Wire Line
	11750 3350 11750 3400
Wire Wire Line
	11750 3400 13900 3400
Wire Wire Line
	10750 3350 10750 3600
Wire Wire Line
	10750 3600 13800 3600
Wire Wire Line
	11650 3350 11650 3650
Wire Wire Line
	11650 3650 13750 3650
Wire Wire Line
	10850 3350 10850 3700
Wire Wire Line
	10850 3700 13700 3700
$Comp
L power:GND #PWR0116
U 1 1 60EC69D6
P 11250 3350
F 0 "#PWR0116" H 11250 3100 50  0001 C CNN
F 1 "GND" H 11255 3177 50  0000 C CNN
F 2 "" H 11250 3350 50  0001 C CNN
F 3 "" H 11250 3350 50  0001 C CNN
	1    11250 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	11150 3350 11250 3350
Connection ~ 11250 3350
Wire Wire Line
	11250 3350 11350 3350
$Comp
L Connector:Conn_01x05_Female CN7
U 1 1 6074E009
P 18650 9550
F 0 "CN7" H 18678 9576 50  0000 L CNN
F 1 "Conn_01x05_Female" H 18678 9485 50  0000 L CNN
F 2 "Custom:Connector_Mini-DIN_Female_4Pin_2rows" H 18650 9550 50  0001 C CNN
F 3 "~" H 18650 9550 50  0001 C CNN
	1    18650 9550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x07_Female CN6
U 1 1 6075251A
P 18650 8700
F 0 "CN6" H 18678 8726 50  0000 L CNN
F 1 "Conn_01x07_Female" H 18678 8635 50  0000 L CNN
F 2 "Custom:Connector_Mini-DIN_Female_6Pin_2rows" H 18650 8700 50  0001 C CNN
F 3 "~" H 18650 8700 50  0001 C CNN
	1    18650 8700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 607944DB
P 18650 9100
F 0 "#PWR0117" H 18650 8850 50  0001 C CNN
F 1 "GND" H 18655 8927 50  0000 C CNN
F 2 "" H 18650 9100 50  0001 C CNN
F 3 "" H 18650 9100 50  0001 C CNN
	1    18650 9100
	1    0    0    -1  
$EndComp
Wire Wire Line
	18650 9100 18450 9100
Wire Wire Line
	18450 8600 17950 8600
Wire Wire Line
	17950 8600 17950 9100
Wire Wire Line
	18450 8400 13400 8400
Wire Wire Line
	13400 8400 13400 8100
Wire Wire Line
	13400 8100 12250 8100
Wire Wire Line
	17600 9350 17600 8500
Wire Wire Line
	17600 8500 13300 8500
Wire Wire Line
	13300 8500 13300 8300
Wire Wire Line
	13300 8300 12250 8300
Wire Wire Line
	17550 9450 17550 8550
Wire Wire Line
	17550 8550 13250 8550
Wire Wire Line
	13250 8550 13250 8400
Wire Wire Line
	13250 8400 12250 8400
Wire Wire Line
	18450 9100 18450 9000
Connection ~ 18450 9100
Wire Wire Line
	6050 5550 6900 5550
Wire Wire Line
	6900 5550 6900 6800
Wire Wire Line
	6900 6800 6100 6800
Wire Wire Line
	5400 6000 5400 5550
Wire Wire Line
	5400 5550 5750 5550
Connection ~ 5400 6000
Wire Wire Line
	5400 6000 5500 6000
$Comp
L power:GND #PWR0118
U 1 1 6090AD4F
P 15050 6750
F 0 "#PWR0118" H 15050 6500 50  0001 C CNN
F 1 "GND" H 15055 6577 50  0000 C CNN
F 2 "" H 15050 6750 50  0001 C CNN
F 3 "" H 15050 6750 50  0001 C CNN
	1    15050 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	15050 6750 15500 6750
Wire Wire Line
	15500 6750 15500 6250
Wire Wire Line
	15500 6250 15700 6250
Wire Wire Line
	15700 7450 15500 7450
Wire Wire Line
	15500 7450 15500 6750
Connection ~ 15500 6750
Wire Wire Line
	7050 7700 7050 7600
Wire Wire Line
	7050 7600 7200 7600
Wire Wire Line
	6100 7700 7050 7700
Wire Wire Line
	7000 7300 7000 7400
Wire Wire Line
	7000 7400 7200 7400
Wire Wire Line
	13700 3700 13700 8800
Wire Wire Line
	13700 8800 12250 8800
Wire Wire Line
	13750 3650 13750 8700
Wire Wire Line
	13750 8700 12250 8700
Wire Wire Line
	13800 3600 13800 8650
Wire Wire Line
	13800 8650 12250 8650
Wire Wire Line
	12250 8650 12250 8600
Wire Wire Line
	13900 3400 13900 8600
Wire Wire Line
	13900 8600 12350 8600
Wire Wire Line
	12350 8600 12350 8500
Wire Wire Line
	12350 8500 12250 8500
$Comp
L Connector:Conn_01x08+GND_Female CN5
U 1 1 6075B59D
P 17300 11250
F 0 "CN5" H 17328 11226 50  0000 L CNN
F 1 "8-Pin DIN" H 17328 11135 50  0000 L CNN
F 2 "RetroArduInput:DIN8-270Print" H 17300 11250 50  0001 C CNN
F 3 "~" H 17300 11250 50  0001 C CNN
	1    17300 11250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 61A03AF5
P 17100 11650
F 0 "#PWR0119" H 17100 11400 50  0001 C CNN
F 1 "GND" H 17105 11477 50  0000 C CNN
F 2 "" H 17100 11650 50  0001 C CNN
F 3 "" H 17100 11650 50  0001 C CNN
	1    17100 11650
	1    0    0    -1  
$EndComp
Wire Wire Line
	13350 8200 12250 8200
Wire Wire Line
	13350 8450 13350 8200
Wire Wire Line
	17650 8800 17650 8450
Wire Wire Line
	17650 8450 13350 8450
Wire Wire Line
	18450 8800 17650 8800
Wire Wire Line
	17100 11250 17000 11250
Wire Wire Line
	17000 11250 17000 10200
Wire Wire Line
	15000 11300 12250 11300
Wire Wire Line
	15000 10200 15000 11300
Wire Wire Line
	12250 11500 15500 11500
Wire Wire Line
	15500 11500 15500 9800
Wire Wire Line
	15500 9800 17100 9800
Wire Wire Line
	17250 9800 17250 8700
Wire Wire Line
	17250 8700 18450 8700
Wire Wire Line
	12250 9700 17700 9700
Wire Wire Line
	18250 9750 18450 9750
Wire Wire Line
	18250 9100 17950 9100
Wire Wire Line
	18450 9100 18250 9100
Connection ~ 18250 9100
Wire Wire Line
	18450 9450 17550 9450
Wire Wire Line
	18450 9350 17600 9350
$Comp
L Device:R_Small R4
U 1 1 62714AA2
P 8600 13050
F 0 "R4" V 8796 13050 50  0000 C CNN
F 1 ">=10 OHM" V 8705 13050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" H 8600 13050 50  0001 C CNN
F 3 "~" H 8600 13050 50  0001 C CNN
	1    8600 13050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8300 13050 8500 13050
$Comp
L Device:LED LED1
U 1 1 6277BA27
P 9350 12900
F 0 "LED1" V 9389 12782 50  0000 R CNN
F 1 "LED" V 9298 12782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 9350 12900 50  0001 C CNN
F 3 "~" H 9350 12900 50  0001 C CNN
	1    9350 12900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED LED2
U 1 1 6279FC92
P 9750 12900
F 0 "LED2" V 9789 12782 50  0000 R CNN
F 1 "LED" V 9698 12782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 9750 12900 50  0001 C CNN
F 3 "~" H 9750 12900 50  0001 C CNN
	1    9750 12900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED LED3
U 1 1 627A1127
P 10150 12900
F 0 "LED3" V 10189 12782 50  0000 R CNN
F 1 "LED" V 10098 12782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 10150 12900 50  0001 C CNN
F 3 "~" H 10150 12900 50  0001 C CNN
	1    10150 12900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8700 13050 8850 13050
Wire Wire Line
	8850 13050 8850 12750
Wire Wire Line
	8850 12750 9350 12750
Wire Wire Line
	18250 9100 18250 9650
Wire Wire Line
	17700 9550 18150 9550
Wire Wire Line
	17700 9550 17700 9700
Wire Wire Line
	18450 9650 18250 9650
Connection ~ 18250 9650
Wire Wire Line
	18250 9650 18250 9750
$Comp
L Device:R_Small R1
U 1 1 624EE446
P 16600 10200
F 0 "R1" V 16796 10200 50  0000 C CNN
F 1 "10kOHM" V 16705 10200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" H 16600 10200 50  0001 C CNN
F 3 "~" H 16600 10200 50  0001 C CNN
	1    16600 10200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	16500 10200 16450 10200
$Comp
L power:GND #PWR?
U 1 1 625EB3E0
P 16450 10250
F 0 "#PWR?" H 16450 10000 50  0001 C CNN
F 1 "GND" H 16455 10077 50  0000 C CNN
F 2 "" H 16450 10250 50  0001 C CNN
F 3 "" H 16450 10250 50  0001 C CNN
	1    16450 10250
	1    0    0    -1  
$EndComp
Wire Wire Line
	16450 10200 16450 10250
Wire Wire Line
	17000 10200 16900 10200
Wire Wire Line
	16900 10200 16900 9850
Wire Wire Line
	16900 9850 15750 9850
Wire Wire Line
	15750 9850 15750 10200
Wire Wire Line
	15750 10200 15000 10200
Connection ~ 16900 10200
Wire Wire Line
	16900 10200 16700 10200
$Comp
L power:GND #PWR?
U 1 1 626EFB2A
P 17750 10250
F 0 "#PWR?" H 17750 10000 50  0001 C CNN
F 1 "GND" H 17755 10077 50  0000 C CNN
F 2 "" H 17750 10250 50  0001 C CNN
F 3 "" H 17750 10250 50  0001 C CNN
	1    17750 10250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 62715467
P 17450 10250
F 0 "R2" V 17646 10250 50  0000 C CNN
F 1 "10kOHM" V 17555 10250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" H 17450 10250 50  0001 C CNN
F 3 "~" H 17450 10250 50  0001 C CNN
	1    17450 10250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	17750 10250 17550 10250
Wire Wire Line
	17350 10250 17100 10250
Wire Wire Line
	17100 10250 17100 9800
Connection ~ 17100 9800
Wire Wire Line
	17100 9800 17250 9800
$Comp
L Device:R_Small R3
U 1 1 6275FEC1
P 18050 10250
F 0 "R3" V 18246 10250 50  0000 C CNN
F 1 "10kOHM" V 18155 10250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" H 18050 10250 50  0001 C CNN
F 3 "~" H 18050 10250 50  0001 C CNN
	1    18050 10250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	18150 9550 18150 9900
Wire Wire Line
	18150 9900 18400 9900
Wire Wire Line
	18400 9900 18400 10250
Wire Wire Line
	18400 10250 18150 10250
Connection ~ 18150 9550
Wire Wire Line
	18150 9550 18450 9550
Wire Wire Line
	17950 10250 17750 10250
Connection ~ 17750 10250
$Comp
L Device:LED LED4
U 1 1 6264F365
P 10550 12900
F 0 "LED4" V 10589 12782 50  0000 R CNN
F 1 "LED" V 10498 12782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 10550 12900 50  0001 C CNN
F 3 "~" H 10550 12900 50  0001 C CNN
	1    10550 12900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED LED5
U 1 1 626759C3
P 10950 12900
F 0 "LED5" V 10989 12782 50  0000 R CNN
F 1 "LED" V 10898 12782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 10950 12900 50  0001 C CNN
F 3 "~" H 10950 12900 50  0001 C CNN
	1    10950 12900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED LED6
U 1 1 6269BDFE
P 11350 12900
F 0 "LED6" V 11389 12782 50  0000 R CNN
F 1 "LED" V 11298 12782 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 11350 12900 50  0001 C CNN
F 3 "~" H 11350 12900 50  0001 C CNN
	1    11350 12900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9350 12750 9750 12750
Connection ~ 9350 12750
Wire Wire Line
	9750 12750 10150 12750
Connection ~ 9750 12750
Wire Wire Line
	10150 12750 10550 12750
Connection ~ 10150 12750
Wire Wire Line
	10550 12750 10950 12750
Connection ~ 10550 12750
Wire Wire Line
	10950 12750 11350 12750
Connection ~ 10950 12750
Wire Wire Line
	11350 13050 10950 13050
Wire Wire Line
	10950 13050 10550 13050
Connection ~ 10950 13050
Wire Wire Line
	10550 13050 10150 13050
Connection ~ 10550 13050
Wire Wire Line
	10150 13050 9750 13050
Connection ~ 10150 13050
Wire Wire Line
	9750 13050 9350 13050
Connection ~ 9750 13050
Wire Wire Line
	9350 13050 8900 13050
Wire Wire Line
	8900 13050 8900 13150
Wire Wire Line
	8300 13150 8900 13150
Connection ~ 9350 13050
$EndSCHEMATC
