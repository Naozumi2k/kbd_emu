#include <Keyboard.h>
#include <Mouse.h>
#include <MouseTo.h>

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(1);
}

void loop(){
  if(Serial.available() > 0){
    int kb_code, m_x, m_y;
    String in = Serial.readString();
    String cmd = in.substring(0, 3);
    if(cmd == "SET"){
      sscanf(in.c_str(), "SET %d %d", &m_x, &m_y);
      Keyboard.begin();
      Mouse.begin();
      MouseTo.setScreenResolution(m_x, m_y);
      //Serial.print("SETUP DONE\n");
    }else if(cmd == "END"){
      Keyboard.end();
      Mouse.end();
      //Serial.print("ENDED\n");
    }else if(cmd == "KEY"){
      sscanf(in.c_str(), "KEY %d", &kb_code);
      Keyboard.press(kb_code);
      delay(35);
      Keyboard.releaseAll();
    }else if(cmd == "MOV"){
      sscanf(in.c_str(), "MOV %d %d", &m_x, &m_y);
      MouseTo.home();
      MouseTo.setTarget(m_x, m_y, false);
      while(!MouseTo.move())
        delay(1);
    }else if(cmd == "MLC"){
      Mouse.click(MOUSE_LEFT);
    }else if(cmd == "MRC"){
      Mouse.click(MOUSE_RIGHT);
    }
  }
}
