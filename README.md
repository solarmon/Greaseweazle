# Greaseweazle Projects
Greaseweazle Projects

Various PCB projects based on **keirf**'s Greaseweazle project for reading and writing floppy disks:

https://github.com/keirf/Greaseweazle

# Greaseweazle F1 Plus

## Design Files

GW F1 Plus Gotek: **COMING SOON**
GW F1 Plus 3.5": **COMING SOON**

## Features

**Standard Features:**
|   | F1 Plus Gotek	| F1 Plus 3.5"|
|---|---|---|
|Jumperless Update|Yes|Yes|
|Multiple Drives|Yes|Yes|
|Write-Protect Jumper|Yes|Yes|
|Buffered Outputs|Yes|Yes|
|High-Speed USB| - | - |			
|12v Power|Yes|Yes|
|Flippy Drive|Yes|Yes|
|User Outputs|2|2|

**Other Features:**
|   | F1 Plus Gotek	| F1 Plus 3.5"|
|---|---|---|
|Gotek Case Form Factor|Yes|		-		|
|3.5" Drive Form Factor|		-		|			Yes|
|STM32 Blue Pill MCU|				Yes|				Yes|
|**Arduino Nano Track Display:**|		Yes|				Yes|
|	- LEDC68 Display|			Yes|				Yes|
|	- 0.91" OLED Display|		(Yes)|			Yes|
|	- 0.96" OLED Display|		(Yes)|			Yes|
|	- SD Card Reader|			Yes|				Yes|
|USB ESD Protection|				Yes|				Yes|
|12V Reverse Polarity Protection|	Yes|				Yes|
|Poly Fuse|						Yes|				Yes|
|**LED Status:**|						Yes|				Yes|
|	- Activity|					Yes|				Yes|
|	- 3.3V|						Yes|				Yes|
|	- 5V|							Yes|				Yes|
|	- 12V|							Yes|				Yes|
|Write Enable Jumper|				Yes|				Yes|
|Input pullups|					Yes|				Yes|
|Reset Button|					Yes|				Yes|
|Serial Programming Header|		Yes|				Yes|
|SWD Programming Header|			Yes|				Yes|

## Track Display

The GW F1 Plus Gotek/3.5" Track Display is provided by an Arduino Nano. The Arduino sketch for this can be found at:

https://github.com/solarmon/Greaseweazle/tree/main/Arduino_Nano_GW_F1_Plus_Floppy_Drive_Track_Display_LED_and_OLED

The LEDC68 and OLED display adapter board can be found at:

https://github.com/solarmon/Greaseweazle/tree/main/LEDC68%20and%200.9%20Inch%20OLED%20Adapter

# Older Revisions

Design files for older revisions of the GW F1 boards can be found at:

## GW F1 Gotek

* Rev 1 (USB-B): https://github.com/solarmon/Greaseweazle/tree/main/Greaseweazle%20F1%20in%20a%20Gotek%20Case%20(%2B%20USB%20B)
* Rev 1 (USB-A): https://github.com/solarmon/Greaseweazle/tree/main/Greaseweazle%20F1%20in%20a%20Gotek%20Case%20(USB-A)
* Rev 2: https://github.com/solarmon/Greaseweazle/tree/main/Greaseweazle%20F1%20Gotek%20Rev%202
* Rev 2B: https://github.com/solarmon/Greaseweazle/tree/main/Greaseweazle%20F1%20Gotek%20Rev%202B

## GW F1 3.5"

* Rev 1: https://github.com/solarmon/Greaseweazle/tree/main/Greaseweazle%20F1%203.5%20Inch
* Rev 2: https://github.com/solarmon/Greaseweazle/tree/main/Greaseweazle%20F1%203.5%20Inch%20Rev%202
* Rev 2B: https://github.com/solarmon/Greaseweazle/tree/main/Greaseweazle%20F1%203.5%20Inch%20Rev%202B

## Track Display

These older revision GW F1 Plus Track Display is provided by an Arduino Nano. The Arduino sketch for this can be found at:

https://github.com/solarmon/Greaseweazle/tree/main/Arduino_Nano_GW_F1_Floppy_Drive_Track_Display_LED_and_OLED_v1

The LEDC68 and OLED display adapter board can be found at:

https://github.com/solarmon/Greaseweazle/tree/main/LEDC68%20and%200.9%20Inch%20OLED%20Adapter
