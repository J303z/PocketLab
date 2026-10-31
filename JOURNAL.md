--- 
title: PocketLab
author: Jayden 
description: A modular handheld electronics multitool built around a ESP32/arduino uno
created_at: 2026-08-27
--- 

# October 27: coded a timer function in Arduino uno

spent the day coding and debugging a timer function on an Arduino uno on tinkercad circuits
components used: LCD 16x2 (I2C) (MCP23008-based)
arduino uno
LED, 220 resistor 

learnt how to do coding on an arduino uno using C++ and how to use the 16x2 LCD screen, i would definitely prefer a bigger screen like a 128x64 OLED 1.3 inch. the code came out alright and working as expected, even though i spent 1 hours trying to debug a “invalid header file” error which was a single missing semicolon.

<img width="2359" height="1372" alt="image" src="https://github.com/user-attachments/assets/9aa5410b-60f0-4c54-9b36-f59f79cdd304" />

<img width="2359" height="1369" alt="image" src="https://github.com/user-attachments/assets/5d3a4677-4226-4aad-b507-4b0c806bd9b2" />

<img width="2359" height="1370" alt="image" src="https://github.com/user-attachments/assets/43c5193a-80b1-441c-bc39-09fd5e7bc2cc" />

**total time spent: 5 hours**

# October 29: moved work from tinkercad to cirkit designer

i moved my work from Thinkercad circuits to cirkit designer as cirkit designer had more components that i would need for this project like the 128x64 monochrome oled and rotatory encoder.

Needed to reprogram the timer function to match with the OLED and also add the rotatory encoder’s function (and calibrate the rotatory encoder) but once this is finished, i think things should go smoothly after since coding the menus and displays and wiring the components together would be easier once i move to a physical device :D

Spent about 1 hourish debugging the rotatory encoder problem that doesn’t made the LEB light up after 1 full rotation cause it si my first time using a rotatory encoder.

Started on coding the menu for item selection, spent like 15 minutes trying to find out why one of my menu item where not displaying, the bug was because i forgotten the “display.display();” text to display my text on the screen. 

finally made the menu appear properly without any bugs, have not integrated other components into the system yet, just a menu with the basic functions that PocketLab will have.

<img width="2360" height="1373" alt="image" src="https://github.com/user-attachments/assets/e04ca1c1-dc71-4954-be54-8a9705d318d1" />

<img width="2360" height="1370" alt="image" src="https://github.com/user-attachments/assets/d4ce4a47-9946-427c-aea7-3af7c2ed0cd4" />

forgot to save my project and needed to restart the coding and wiring ;-;

<img width="2359" height="1376" alt="image" src="https://github.com/user-attachments/assets/4fa1224f-a6b8-44e1-ab89-69273576c327" />

**total time spent: 3.75 hours**

# October 30: started coding the menu for PocketLabOS

today started coding PocketLab’s OS which i call PocketLabOS, planning to implement the rotatory encoder for menu item selection.

updated some wiring to make the wiring less messy and coded and updated the OS to have 
- item selection by rotating the rotatory encoder,
- new and improved menu
- lED and button and rotatory encoder push functions now also works

currently you can’t select items but I’ll do it tomorrow starting with the timer function. Also i keep forgetting to add the display.display thing after each display refresh so I’ll need to remember that to spend less time debugging the code cause of this problem ;—; (happened like 2 times today)

<img width="3000" height="1678" alt="image" src="https://github.com/user-attachments/assets/780a8a6d-dc39-4dc7-9bbc-cbb3e0fe4728" />

**total time spent: 3.15 hours**

# October 31: did light coding for item selection

i just did simple code to print in the console the item that is selected when you press the rotatory encoder button, there is still a bug that causes it to also open stopwatch when you click the button to exit the start up screen but I’ll fix that tmr i feel sleep deprived today ;-;

**total time spent: 0.5 hours**
