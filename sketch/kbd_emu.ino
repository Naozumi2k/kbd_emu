#include <Keyboard.h>
#include <AbsMouse.h>

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(1);
}

void loop(){
  if(Serial.available() > 0){
    int kb_code, m_x, m_y;
    String in = Serial.readString();
    String cmd = in.substring(0, 2);
    if(cmd == "ST"){
      sscanf(in.c_str(), "ST %d %d", &m_x, &m_y);
      AbsMouse.init(m_x, m_y);
    }else if(cmd == "KB"){
      sscanf(in.c_str(), "KB %d", &kb_code);
      Keyboard.press(kb_code);
      delay(25);
      Keyboard.releaseAll();
    }else if(cmd == "MV"){
      sscanf(in.c_str(), "MV %d %d", &m_x, &m_y);
      AbsMouse.move(m_x, m_y);
    }else if(cmd == "MC"){
      sscanf(in.c_str(), "MC %d %d", &m_x, &m_y);
      AbsMouse.move(m_x, m_y);
      delay(10);
      AbsMouse.press(MOUSE_LEFT);
      delay(25);
      AbsMouse.release(MOUSE_LEFT);
    }
  }
}
