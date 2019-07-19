/** @file gui.h
 *  A header file defining classes of the tiny C++ lvgl wrapper.
 *  Only simple Label, QR and Button classes are implemented.
 *
 *  Example:
 *  @code
 *  #include <mbed.h>
 *  #include <gui.h>
 *
 *  GUI gui;     // our GUI instance
 *  Label lbl;   // label in the global scope, we will change text from the button callback
 *  int cnt = 0; // click counter
 *
 *  // button callback, default lvgl type
 *  static lv_res_t callback(lv_obj_t * btn){
 *    // Button button(btn); // can be converted to C++ class
 *    cnt++;
 *    char msg[40];
 *    sprintf(msg, "Button clicked %d times!", cnt);
 *    lbl.text(msg);
 *    return LV_RES_OK;
 *  }
 *
 *  int main() {
 *
 *    gui.init();
 *
 *    // Create a label to log clicks
 *    lbl = Label("Hello display!");
 *    lbl.size(gui.width(), 100); // full width
 *    lbl.position(0, 200);
 *    lbl.alignText(ALIGN_TEXT_CENTER);
 *
 *    // Create a button
 *    Button btn(callback, "Click me!");
 *    btn.size(300, 100);
 *    btn.position(0, 300);
 *    btn.align(ALIGN_CENTER);
 *
 *    while(1) {
 *      gui.update();
 *    }
 *  }
 *  @endcode
 */

#ifndef LVGL_MIN_GUI_H
#define LVGL_MIN_GUI_H

#include <lvgl.h>
#include <string>

#define ALIGN_CENTER LV_ALIGN_IN_TOP_MID
#define ALIGN_LEFT   LV_ALIGN_IN_TOP_LEFT
#define ALIGN_RIGHT  LV_ALIGN_IN_TOP_RIGHT

#define ALIGN_TEXT_CENTER LV_LABEL_ALIGN_CENTER
#define ALIGN_TEXT_RIGHT  LV_LABEL_ALIGN_RIGHT
#define ALIGN_TEXT_LEFT   LV_LABEL_ALIGN_LEFT

class Label;
class Button;

/** GUI class.
 *  Used to initialize the littlevgl library, the display and the touchscreen.
 */
class GUI{
public:
  /** Initialize and register the drivers. Should be called first in the very beginning */
  void init();
  /** Update the GUI. Call this function in a loop to get button callbacks and UI updates. */
  void update();
  /** Get the width of the screen. */
  uint16_t width();
  /** Get the height of the screen. */
  uint16_t height();
  /** Clear the screen and delete all elements */
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

/** Label class. Creates a simple label on the screen.
 */
class Label : public GUIObject{
public:
  /** Create an empty label */
  Label(){};
  /** Create a label from lvgl object */
  Label(lv_obj_t * lbl);
  /** Create a label with text `txt` */
  Label(const char * txt);
  /** Create a label with text `txt` */
  Label(std::string txt);
  /** Set text of the label to `txt` */
  void text(const char * txt);
  /** Set text of the label to `txt` */
  void text(std::string txt);
  /** Align text of the label to one of the options:
   *  - ALIGN_TEXT_LEFT
   *  - ALIGN_TEXT_CENTER
   *  - ALIGN_TEXT_RIGHT
   */
  void alignText(int mode);
};

/** Button class. Creates a simple button on the screen.
 */
class Button : public GUIObject{
public:
  Label label;
  /** Create an empty button */
  Button(){};
  /** Create a button based on lvgl object */
  Button(lv_obj_t * btn);
  /** Create a button, define on-click callback and label */
  Button(lv_res_t (*callback)(lv_obj_t * btn), const char * txt);
  /** Create a button, define on-click callback and label */
  Button(lv_res_t (*callback)(lv_obj_t * btn), std::string txt);
  /** Set size of the button */
  void size(uint16_t width, uint16_t height);
  /** Set unique identifier of the button, can be used in the callback */
  void text(const char * txt){ label.text(txt); };
  void text(std::string txt){ label.text(txt); };
  void id(int32_t);
  /** Get unique identifier of the button.
   *  Use this function in the callback to find out which button was pressed.
   */
  int32_t id();
  /** Disables the button and makes it inactive */
  void disable();
  /** Enables the button and makes it active again */
  void enable();
};

/** Keyboard class. Creates a simple keyboard on the screen.
 */
class Keyboard : public GUIObject{
public:
  Label label;
  /** Create an empty button */
  Keyboard(){};
  /** Create a button based on lvgl object */
  Keyboard(lv_obj_t * btn);
  /** Create a button, define on-click callback and label */
  Keyboard(lv_res_t (*callback)(lv_obj_t * btn, const char * key), const char * keys[]);
  /** Set size of the button */
  void size(uint16_t width, uint16_t height);
};

class QR : public GUIObject{
  std::string text_to_encode;
  void create(lv_obj_t * qr = NULL);
  void resize();
  uint16_t width;
public:
  /** Create an empty QR code */
  QR(){};
  /** Create a QR code based on lvgl object */
  QR(lv_obj_t * qr);
  /** Create a QR code and encode text there */
  QR(const char * txt);
  /** Create a QR code and encode a string there */
  QR(std::string txt);
  /** Set size of the QR code. Will be a square. */
  void size(uint16_t size);
  /** Set text to encode in the QR code */
  void text(const char * txt);
  /** Set string to encode in the QR code */
  void text(std::string txt);
};

#endif // LVGL_MIN_GUI_H
