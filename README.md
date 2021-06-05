# Greaseweazle Projects
Greaseweazle Projects

Various PCB projects based on **keirf**'s Greaseweazle project for reading and writing floppy disks:

https://github.com/keirf/Greaseweazle

# Greaseweazle F1 Plus

## Features

These are the features of the GW F1 Plus boards.

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
|Disk Change Detect|Yes|Yes|
|User Outputs|3|3|

Note: **Disk Change Detect** allows WinUAE integration - see https://amiga.robsmithdev.co.uk/winuae

**Other Features:**
|   | F1 Plus Gotek	| F1 Plus 3.5"|
|---|---|---|
|Gotek Case Form Factor|Yes|		-		|
|3.5" Floppy Drive Form Factor|		-		|			Yes|
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
| - Type: SMT| - | Yes|
| - Type: THT| Yes | Yes|
|Write Enable Jumper|				Yes|				Yes|
|Input pullups|					Yes|				Yes|
|Reset Button|					Yes|				Yes|
|Serial Programming Header|		Yes|				Yes|
|SWD Programming Header|			Yes|				Yes|

The features of the official Greaseweazle models can be seen at:

https://github.com/keirf/Greaseweazle/wiki/Greaseweazle-Models

## Greaseweazle F1 Plus Gotek

**Design Files:** https://github.com/solarmon/Greaseweazle/tree/main/Greaseweazle%20F1%20Plus%20Gotek

This Greaseweazle board has been designed to re-purpose and fit into an original Gotek case; and to make use of its LEDC68 display as a track display.

It has been designed to sit on top of the floppy drive that is connected to it.

![](https://github.com/solarmon/Greaseweazle/blob/main/Greaseweazle%20F1%20Plus%20Gotek/Greaseweazle%20F1%20Plus%20Gotek%20-%20PCB%20THT%20Front.png)

![](https://github.com/solarmon/Greaseweazle/blob/main/Greaseweazle%20F1%20Plus%20Gotek/Greaseweazle%20F1%20Plus%20Gotek%20-%20PCB%20THT%20Top.png)

![](https://github.com/solarmon/Greaseweazle/blob/main/Greaseweazle%20F1%20Plus%20Gotek/Greaseweazle%20F1%20Plus%20Gotek%20-%20PCB%20SMD%20Top.png)


## Greaseweazle F1 Plus 3.5"

**Design Files:** https://github.com/solarmon/Greaseweazle/tree/main/Greaseweazle%20F1%20Plus%203.5

This Greaseweazle board has been designed to have a 3.5" floppy drive mounted directly on top of it, using the floppy drive standard mounting holes.

The track display feature can support the LEDC68 Gotek LED display, or a 128x32 0.91" OLED display, or a 128x64 0.96" OLED display.

![](https://github.com/solarmon/Greaseweazle/blob/main/Greaseweazle%20F1%20Plus%203.5/Greaseweazle%20F1%20Plus%203.5%20-%20PCB%20SMT%20Front%20Angle.png)

![](https://github.com/solarmon/Greaseweazle/blob/main/Greaseweazle%20F1%20Plus%203.5/Greaseweazle%20F1%20Plus%203.5%20-%20PCB%20SMT%20Front.png)

![](https://github.com/solarmon/Greaseweazle/blob/main/Greaseweazle%20F1%20Plus%203.5/Greaseweazle%20F1%20Plus%203.5%20-%20PCB%20SMT%20Side.png)

![](https://github.com/solarmon/Greaseweazle/blob/main/Greaseweazle%20F1%20Plus%203.5/Greaseweazle%20F1%20Plus%203.5%20-%20PCB%20SMT%20THT%20Bottom.png)

![](https://github.com/solarmon/Greaseweazle/blob/main/Greaseweazle%20F1%20Plus%203.5/Greaseweazle%20F1%20Plus%203.5%20-%20PCB%20SMT%20Top.png)

![](https://github.com/solarmon/Greaseweazle/blob/main/Greaseweazle%20F1%20Plus%203.5/Greaseweazle%20F1%20Plus%203.5%20-%20PCB%20Bottom.png)

## Track Display

The GW F1 Plus Gotek/3.5" Track Display is provided by an Arduino Nano. The Arduino sketch for this can be found at:

https://github.com/solarmon/Greaseweazle/tree/main/Arduino_Nano_GW_F1_Plus_Floppy_Drive_Track_Display_LED_and_OLED

The LEDC68 and OLED display adapter board, used in the GW F1 3.5" and GW F1 Plus 3.5" boards, can be found at:

https://github.com/solarmon/Greaseweazle/tree/main/LEDC68%20and%200.9%20Inch%20OLED%20Adapter

![Top](https://github.com/solarmon/Greaseweazle/blob/main/LEDC68%20and%200.9%20Inch%20OLED%20Adapter/LEDC68%20and%200.9%20Inch%20OLED%20Adapter%20-%20Top.png)

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
