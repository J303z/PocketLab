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

<img width="2360" height="1377" alt="image" src="https://github.com/user-attachments/assets/80690011-65a0-4812-b117-df6f24a1893a" />
pressing the encoder button makes the arduino output the current selected item into the console

**total time spent: 0.5 hours**

# November 4: added a stop watch function

i added a stopwatch function to let the user measure time, i still haven’t added proper denouncing yet and i also will want to separate my files for each function and it’s code but for now it is good enough for now.

<img width="2360" height="1369" alt="image" src="https://github.com/user-attachments/assets/cc8cb0d5-7e78-4886-ae38-518f8ebb7e7e" />

<img width="2359" height="1367" alt="image" src="https://github.com/user-attachments/assets/1bfed3f1-4715-409d-86ad-9d5228315ee1" />

<img width="2360" height="1366" alt="image" src="https://github.com/user-attachments/assets/c388ee44-f231-4884-96c1-9ed787b920cb" />

**total time spent: 1.5 hours**

# November 5: revised the code for the OS

i added function pointers/structs (i think that is what they are called) for each item menu and removed the old itemmenu array. also removed distance sensor cause i think ill attach it onto the device from the rails separately.

also added .h and .cpp for all menu items and the menu so I’ll move and arrange the code accordingly to the files so it is easier to find and edit code because now it is so hard to find the code that i want to edit.

<img width="2360" height="1534" alt="image" src="https://github.com/user-attachments/assets/3253ce3b-bd69-4946-9fb1-90f4be7288f5" />
(uploaded the image cause idk what image suits here)

**total time spent: 2 hours**

# Novemeber 5: moved stopwatch code to .h and .cpp files

i managed to move the files to their own .h and .cpp files, but when i tried debugging a bug that cause the stopwatch to immediately start measuring time after you re-enter it, the OLED initialisation keeps failing and after A LOT of debugging help from ChatGPT, i concluded it could be memory issues and therefore i might need to upgrade to an ESP32-S3 soon.

at least i would have wifi, Bluetooth and other new capabilities that the arduino uno doesn’t have (and need to re-wire everything ;-;).

also weird text keeps appearing on my OLED i think also smth to do with the memory issues? i think.

<img width="2360" height="1387" alt="image" src="https://github.com/user-attachments/assets/c0efec0b-e0c7-4e47-ae5f-e7c0f454daae" />

**total time spent: 3 hours**
