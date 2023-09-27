/*
Open Dials Gamepad - V1.0
USB version
Arduino pro micro pinout.
*/

#include "NewEncoder.h"
#include "HID-Project.h"
#include <EEPROM.h>

NewEncoder firstEncoder;
NewEncoder secondEncoder;

const int button_up_pin = 10;
const int button_down_pin = 16;
const int button_left_pin = 14;
const int button_right_pin = 15;

const int button_a_pin = 2;
const int button_b_pin = 3;

const int button_start_pin = 4;
const int button_select_pin = 5;

const int encoder1_a_pin = 9;
const int encoder1_b_pin = 8;
const int encoder2_a_pin = 6;
const int encoder2_b_pin = 7;

const int led_mode_joypad_pin = A0;
const int led_mode_keyboard_pin = A1;
const int button_mode_pin = A2;

int encoder1_last = 0;
int encoder2_last = 0;
bool button_up_last = false;
bool button_down_last = false;
bool button_left_last = false;
bool button_right_last = false;
bool button_a_last = false;
bool button_b_last = false;
bool button_start_last = false;
bool button_select_last = false;
bool button_mode_last = false;

bool button_l = false;
bool button_r = false;
bool button_x = false;
bool button_y = false;

int mode = 0;
int mode_address = 0;

unsigned long delayTime = 0;

void setup()
{
    pinMode(button_up_pin, INPUT_PULLUP);
    pinMode(button_down_pin, INPUT_PULLUP);
    pinMode(button_left_pin, INPUT_PULLUP);
    pinMode(button_right_pin, INPUT_PULLUP);
    pinMode(button_a_pin, INPUT_PULLUP);
    pinMode(button_b_pin, INPUT_PULLUP);
    pinMode(button_start_pin, INPUT_PULLUP);
    pinMode(button_select_pin, INPUT_PULLUP);

    pinMode(button_mode_pin, INPUT_PULLUP);
    pinMode(led_mode_joypad_pin, OUTPUT);
    pinMode(led_mode_keyboard_pin, OUTPUT);

    firstEncoder.begin(encoder1_a_pin, encoder1_b_pin);
    secondEncoder.begin(encoder2_a_pin, encoder2_b_pin);    
    mode = EEPROM.read(mode_address);
    if(mode != 0 && mode != 1)
    {
      mode = 0;
    } 
    SetMode();
}

void loop()
{      
    firstEncoder.Update();
    secondEncoder.Update();
    
    if (millis() - delayTime < 300)
        return;

    delayTime = millis();      
      
    SetEncoder();
    SelectMode();
      
    if(mode == 0){
      digitalWrite(led_mode_joypad_pin, HIGH);
      digitalWrite(led_mode_keyboard_pin, LOW);
      JoypadMode();
    }
    else
    {
      digitalWrite(led_mode_keyboard_pin, HIGH);
      digitalWrite(led_mode_joypad_pin, LOW);
      KeyboardMode();
    }    
}

void JoypadMode()
{
  bool up = digitalRead(button_up_pin) == LOW;
  bool down = digitalRead(button_down_pin) == LOW;
  bool left = digitalRead(button_left_pin) == LOW;
  bool right = digitalRead(button_right_pin) == LOW;

  bool a = digitalRead(button_a_pin) == LOW;
  bool b = digitalRead(button_b_pin) == LOW;

  bool start = digitalRead(button_start_pin) == LOW;
  bool select = digitalRead(button_select_pin) == LOW;
  

  if(up)
  {
    Gamepad.press(12);
  }
  else
  {
    Gamepad.release(12);
  }

  if(down)
  {
    Gamepad.press(13);
  }
  else
  {
    Gamepad.release(13);
  }

  if(left)
  {
    Gamepad.press(14);
  }
  else
  {
    Gamepad.release(14);
  }

  if(right)
  {
    Gamepad.press(15);
  }
  else
  {
    Gamepad.release(15);
  }

  if(select)
  {
    Gamepad.press(5);
  }
  else
  {
    Gamepad.release(5);
  }

  if(start)
  {
    Gamepad.press(7);
  }
  else
  {
    Gamepad.release(7);
  }

  if(a)
  {
    Gamepad.press(1);
  }
  else
  {
    Gamepad.release(1);
  }

  if(b)
  {
    Gamepad.press(2);
  }
  else
  {
    Gamepad.release(2);
  }

  if(button_x)
  {
    Gamepad.press(3);    
  }
  else
  {
    Gamepad.release(3);
  }

  if(button_y)
  {
    Gamepad.press(4);    
  }
  else
  {
    Gamepad.release(4);
  }

  if(button_l)
  {
    Gamepad.press(10);
  }
  else
  {
    Gamepad.release(10);
  }

  if(button_r)
  {
    Gamepad.press(11);
  }
  else
  {
    Gamepad.release(11);
  }

  Gamepad.write();
}

void KeyboardMode()
{
  bool up = digitalRead(button_up_pin) == LOW;
  bool down = digitalRead(button_down_pin) == LOW;
  bool left = digitalRead(button_left_pin) == LOW;
  bool right = digitalRead(button_right_pin) == LOW;

  bool a = digitalRead(button_a_pin) == LOW;
  bool b = digitalRead(button_b_pin) == LOW;

  bool start = digitalRead(button_start_pin) == LOW;
  bool select = digitalRead(button_select_pin) == LOW;

  if(up)
  {
    Keyboard.press(KEY_W);
  }
  else
  {
    Keyboard.release(KEY_W);
  }

  if(down)
  {
    Keyboard.press(KEY_S);
  }
  else
  {
    Keyboard.release(KEY_S);
  }

  if(left)
  {
    Keyboard.press(KEY_A);
  }
  else
  {
    Keyboard.release(KEY_A);
  }

  if(right)
  {
    Keyboard.press(KEY_D);
  }
  else
  {
    Keyboard.release(KEY_D);
  }

  if(select)
  {
    Keyboard.press(KEY_ESC);
  }
  else
  {
    Keyboard.release(KEY_ESC );
  }

  if(start)
  {
    Keyboard.press(KEY_ENTER);
  }
  else
  {
    Keyboard.release(KEY_ENTER);
  }

  if(a)
  {
    Keyboard.press(KEY_SPACE);
  }
  else
  {
    Keyboard.release(KEY_SPACE);
  }

  if(b)
  {
    Keyboard.press(KEY_RIGHT_SHIFT);
  }
  else
  {
    Keyboard.release(KEY_RIGHT_SHIFT);
  }

  if(button_x)
  {
    Keyboard.press(KEY_DOWN);    
  }
  else
  {
    Keyboard.release(KEY_DOWN);
  }

  if(button_y)
  {
    Keyboard.press(KEY_UP);    
  }
  else
  {
    Keyboard.release(KEY_UP);
  }

  if(button_l)
  {
    Keyboard.press(KEY_LEFT);
  }
  else
  {
    Keyboard.release(KEY_LEFT);
  }

  if(button_r)
  {
    Keyboard.press(KEY_RIGHT);
  }
  else
  {
    Keyboard.release(KEY_RIGHT);
  }

  Keyboard.send();
}

void SetEncoder()
{  
  int encoder1_value = firstEncoder.GetSteps();
  int encoder2_value = secondEncoder.GetSteps();
  if(encoder1_value != encoder1_last) 
    {
      if(encoder1_value > encoder1_last)
      {
        button_r = true;
      }else 
      {
        button_l = true;
      }
      encoder1_last = encoder1_value;
    }
    else
    {
      button_r = false;
      button_l = false;
    }

    if(encoder2_value != encoder2_last) 
    {
      if(encoder2_value > encoder2_last)
      {
        button_x = true;
      }else 
      {
        button_y = true;
      }
      encoder2_last = encoder2_value;
    }
    else
    {
      button_x = false;
      button_y = false;
    }  
}

void SelectMode()
{
  if(GetButtonState(button_mode_pin) != button_mode_last)
  {
    if(GetButtonState(button_mode_pin))
    {      
      if(mode == 0)
      {
        mode = 1;        
      }else
      {
        mode = 0;        
      }    
      EEPROM.write(mode_address, mode);
      SetMode();
    }
    button_mode_last = GetButtonState(button_mode_pin);
  }
}

void SetMode()
{
  if(mode == 0)
  {
    Keyboard.end();
    Gamepad.begin();
  }else
  {
    Gamepad.end();
    Keyboard.begin();
  }      
}

bool GetButtonState(int button){
  if(digitalRead(button) == HIGH) 
  {
    return false;
  }else
  {
    return true;
  }
}