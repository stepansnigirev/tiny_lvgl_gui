#include "gui.h"
#include <mbed.h>
#include <tft.h>
#include <touchpad.h>
#include <lvgl.h>

/* timer to count time in a loop and update the lvgl */
static volatile int t = 0;
Ticker ms_tick;
static void onMillisecondTicker(void){
  t++;
}

/********* GUI class *********/

void GUI::init(){
  /* init hardware */
  lv_init();
  tft_init();
  touchpad_init();

  // timer to update the gui
  ms_tick.attach_us(onMillisecondTicker, 1000);

  /* define theme */
  lv_theme_t * th = lv_theme_material_init(210, NULL);
  lv_theme_set_current(th);

  /* create and load screen */
  lv_obj_t * scr = lv_cont_create(NULL, NULL);
  lv_scr_load(scr);
}
void GUI::update(){
  HAL_Delay(1);
  lv_tick_inc(t);
  lv_task_handler();
  t = 0;
}
uint16_t GUI::width(){ return TFT_HOR_RES; }
uint16_t GUI::height(){ return TFT_VER_RES; }
Label GUI::label(const char * txt){
  lv_obj_t * lbl = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(lbl, txt);
  Label l(lbl);
  return l;
}
Button GUI::button(lv_res_t (*callback)(lv_obj_t * btn), const char * txt){
  lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);
  lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, callback);
  lv_obj_t * lbl = lv_label_create(btn, NULL);
  lv_label_set_text(lbl, txt);
  Button b(btn);
  return b;
}
void GUI::clear(){
  lv_obj_clean(lv_scr_act());
}

/********* GUIObject *********/

void GUIObject::size(uint16_t width, uint16_t height){
  if(obj == NULL){ return; }
  lv_obj_set_size(obj, width, height);
}
void GUIObject::position(uint16_t x, uint16_t y){
  if(obj == NULL){ return; }
  lv_obj_set_pos(obj, x, y);
}
void GUIObject::lv_object(lv_obj_t * o){
  obj = o;
}
lv_obj_t * GUIObject::lv_object(){
  return obj;
}
void GUIObject::align(int mode){
  lv_obj_align(obj, NULL, mode, lv_obj_get_x(obj), lv_obj_get_y(obj));
}

/********* Label class *********/

Label::Label(lv_obj_t * lbl){
  obj = lbl;
  lv_label_set_long_mode(obj, LV_LABEL_LONG_BREAK);
}
void Label::text(const char * txt){
  if(obj == NULL){ return; }
  lv_label_set_text(obj, txt);
}
void Label::align_text(int mode){
  if(obj == NULL){ return; }
  lv_label_set_align(obj, mode);
}

/********* Button class *********/

Button::Button(lv_obj_t * btn){
  obj = btn;
  // lv_cont_set_fit(obj, true, true);
  label = Label(lv_obj_get_child(btn, NULL));
  // lv_obj_set_free_num(obj, (uint32_t)this);
}
void Button::size(uint16_t width, uint16_t height){
  // lv_cont_set_fit(obj, false, false);
  lv_obj_set_size(obj, width, height);
}
void Button::id(uint32_t i){
  lv_obj_set_free_num(obj, i);
  // _id = i;
}
uint32_t Button::id(){
  return lv_obj_get_free_num(obj);
}
