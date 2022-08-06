# RetroARDUInput
Use USB Keyboards, Mice and Joysticks on PC/XT, PC/AT, Tandy 1000, Atari, Amiga, C64 and Apple

Requires Circuits@Home USB Host Shield 2.0 Library

Released before getting all components in a 100% working state, as I did not want to wait longer. Due to time limitations, I cannot guarantee to be finished soon with the last details, but by now, you can use all working components already. I will continue development but also encourage the retro computing community to help and contribute in fixing the last PS/2 and ADB issues.

Current status of release:

- Working Input Devices:
  - Most normal USB Keyboards
  - Most normal USB Mice
  - Most USB Composite HIDs (Wireless USB Keyboard/Mouse)
  - USB Joysticks and Gamepads if they match to any of the implemented profiles
  
Non-working or limited input devices (mostly limitations of the USB host shield library):
  - USB Hubs work random
  - No support for X-Box/Playstation USB gamepads
  - Problems with Gaming Keyboard/Mice with light effects etc.

Working computers to connect to:
  - PC/XT via Keyboard port
  - PC/AT via Keyboard port and PS/2 via adapter - includes typematic rate programming and LED set, however LEDs sometimes not properly set (only limitation)
  - Amiga 500 via Keyboard port when using an adapter to the internal keyboard port
  - Serial mouse with 2-button Microsoft and 3-button Logitech mode
  - Amiga/Atari mouse including switching of the X/Y pins between Atari and Amiga standard
  - Digital joystick, reacting to either joystick (normal joystick mode - uses a "dead zone" for analog joysticks to not immediately react on the slightest changes) and mouse (like a Commodore 1350 "Joymouse")
  - Analog joystick with 4 axis and 4 buttons
  
Untested computers to connect to:
  - Tandy 1000 via keyboard port - adaptation of Adrian Black's PS/2 to Tandy, should work, but I cannot test it
  - Amiga 2000 via keyboard port - Should mostly work as mainly identical to Amiga 500, but uses a different routine during keyboard reset (Ctrl+Amiga+Amiga), which I cannot test du to not having an Amiga 2000 - Routine implemented but untested
  - Analog joystick when pulling the potentiometer to ground, which should enable to use it with BBC Micro, Tandy TRS-80, Tandy 1000 and Tano/Dragon with a proper adapter cable (attention, BBC Micro DB15 pinout different from PC!)

Non-working or limited computers to connect to:
  - PS/2 via mouse port - detected by the BIOS and IRQ 12 properly reserved, works with a certain Logitech driver but not with Cutemouse or Windows
  - ADB for keyboard and mouse - Impleentation ongoing, switching on power via ADB works (currently mapped to Print Screen key), no keyboard scancodes implemented yet, mouse reporting started to implement but currently no reaction on my PowerMac to this
