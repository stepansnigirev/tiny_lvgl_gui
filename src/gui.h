#ifndef LVGL_MIN_GUI_H
#define LVGL_MIN_GUI_H

#include <lvgl.h>

#define ALIGN_CENTER LV_ALIGN_IN_TOP_MID
#define ALIGN_LEFT   LV_ALIGN_IN_TOP_LEFT
#define ALIGN_RIGHT  LV_ALIGN_IN_TOP_RIGHT

#define ALIGN_TEXT_CENTER LV_LABEL_ALIGN_CENTER
#define ALIGN_TEXT_RIGHT  LV_LABEL_ALIGN_RIGHT
#define ALIGN_TEXT_LEFT   LV_LABEL_ALIGN_LEFT

class Label;
class Button;

class GUI{
public:
  void init();
  void update();
  Label label(const char * txt = "Label");
  Button button(void (*callback)(Button *), const char * txt = "Button");
  uint16_t width();
  uint16_t height();
  void clear(); // Clear the display. All components will be deleted.
};

class GUIObject{
public:
  lv_obj_t * obj;
  void lv_object(lv_obj_t * o);
  lv_obj_t * lv_object();
  void size(uint16_t width, uint16_t height);
  void position(uint16_t width, uint16_t height);
  void align(int mode = ALIGN_CENTER);
};

class Label : public GUIObject{
public:
  Label(){};
  Label(lv_obj_t * lbl);
  void text(const char * txt);
  void align_text(int mode);
};

class Button : public GUIObject{
public:
  uint32_t id;
  void (*callback)(Button *btn);
  Label label;
  Button(){};
  Button(lv_obj_t * btn, lv_obj_t * lbl, void (*callback)(Button *));
  void size(uint16_t width, uint16_t height);
};

#endif // LVGL_MIN_GUI_H
