# kbd_emu

Arduino ATmega32u4 hardware keyboard and mouse input emulator.

![Arduino PRO Micro](https://all-arduino.ru/wp-content/uploads/vyrn_181arduinomicro.png)


There are the Arduino IDE sketch and Dev-C++ project with DLL to communicate with Arduino using COM port.  
DLL can be compiled with Dev-C++ http://orwelldevcpp.blogspot.com/  
Also there is ready to use with 32-bit apps DLL: https://github.com/Naozumi2k/kbd_emu/releases  

# DLL usage example with Kibor:  
Kibor can be downloaded here: http://kibor-bot.com/stat/programmed-autoclicker.php:  
Definitions for modifier keys can be found here: https://www.arduino.cc/en/Reference/KeyboardModifiers  

    external(INT, "Initialize", "Initialize", "kbd_emu.dll");
    external(INT, "MouseMove", "MouseMove", "kbd_emu.dll");
    external(INT, "MouseClick", "MouseClick", "kbd_emu.dll");
    external(INT, "KeyboardKey", "KeyboardKey", "kbd_emu.dll");
    
    //Initialize DLL with COM port name and desktop resolution
    if(!Initialize("COM5", 1920, 1080)){
	    messagebox("Failed to initialize kbd_emu!");
	    close();
    }
    
    //emulate mouse move
    MouseMove(100, 100);
    //emulate left click
    MouseClick(100, 150);
    //emulate 'return' key press
    KeyboardKey(176);
