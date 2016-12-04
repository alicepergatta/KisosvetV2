# KisosvetV2
Smart LED-light for shoting photo, video, and comfort illumination in home)

Read [About](https://github.com/alicepergatta/KisosvetV2/wiki/About)

More documentation:[Kisosvet wiki](https://github.com/alicepergatta/KisosvetV2/wiki)

## Main functionality:

- 16-bit PWM brightness regulation, without any flickering
- Color temperature regulation, and white color calibration
- Different LED types for full spectre(WW + NW or WW + CW for example)
- Flickering-free power modules and control circuitry schemati
- Step-down based power modules, wich can work at voltage up to 35V - in car, at home, everywhere with 3S(or more) lithium battery pack.
- STM32 microcontroller as a "brain"
- ESP8266 for networking functionality
- DS18B20 as a temperature sensor for fan control logic
- Temperature & fan control with overheat protection
- Energy efficiency:each PM can be switched on\off, fan on\off + fan PWM, sleep\standby modes for main chips.
- Network control by web-interface or android application
- Wake-up from internal li-ion battery, and power on external PSU - perfect for use wih ATX PSU by pulling down PS_ON pin.
- Measuring power supply\main battery voltage - you exactly know when battery low.


## What should i do?

- [x] Power Modules schematic 
- [x] Reverse voltage protection
- [x] Power rails schematic
- [x] STM32 board pin assigments
- [x] PWM regulation and calibration(for each PM\LED) functionality
- [x] PM on\off
- [x] Main STM32 project code

- [ ] Make normal CLI over UART for STM32+ESP8266 interconnect
- [ ] Add DS18B20 functionality 
- [ ] Add fan PWM level-shifter
- [ ] Write fan control logic
- [ ] Replace linear VREG's for step-down modules, to achieve bettter energy efficiency
- [ ] Write whole networking part
- [ ] Write code for ADC(voltage measuring)
- [ ] Write wake-up and sleep functionality code
- [ ] Make a few variants for device case
- [ ] Implement CLI syntax
- [ ] Develop android application
- [ ] add external antenna for ESP8266
- [ ] Write logic for manual control by encoders and buttons

## Folders & files description

- stm32 - Keil & STM32CubeMX projects
  I'm using C and C++ in this project.
- schematic - Splan schematic project
  Splan is pretty easy tool for drawing schematic
  * [ ] learn a better software
- schematic-png - Schematic in PNG images
- esp8266 - code for esp8266
- Photos - photos of project realization, currently there are prototype photos

## FAQ

[Full FAQ](https://github.com/alicepergatta/KisosvetV2/wiki/FAQ)

**Q**: Can i build own Kisosvet but with different LED's and PM's?

**A**: Yes! You just need to add variables for new LED's\PM's, and if your LED's are less or more powerful - you need to change PM's circuitry(replace DC-DC converter for diffrent type or power)

**Q**: Which DC-DC type converters can be used for PM's?

**A**:  You can use step-up, step-down, and even SEPIC.
Almost all DC-DC converters have same negative feedback voltage control.
Control circuitry, which i made in Kisosvet suitable for any DC-DC converters with negative feedback voltage control)
(maybe you will need rewrite PWM values calculation, it can be inverted)

**Q**: Which LED types can i use?

**A**: Any) It depends on power modules circuitry(DC-DC converter type), and cooling possibilities(heatsink, fan, and thermal grease).

**Q**: How can you describe a typical Kisosvet build configuration?

**A**: I prefear 10W 12V LED's, 4 pieces placed in chess order(like subpixels). This allows me to use lithium battery pack and typical ATX PSU. Also, i made a 10W PM circuit(see schematic) based on cheap step-down converter.
Despite it's cheapness - it's enough powerfull for 10W LED)



