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

/* button callback */
static lv_res_t btn_click_action(lv_obj_t * btn){
  Button * b = (Button *)lv_obj_get_free_num(btn);
  b->callback(b);
  return LV_RES_OK; /*Return OK if the button is not deleted*/
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
  return Label(lbl);
}
Button GUI::button(void (*callback)(Button *), const char * txt){
  lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);
  lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_obj_t * lbl = lv_label_create(btn, NULL);
  lv_label_set_text(lbl, txt);
  return Button(btn, lbl, callback);
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

Button::Button(lv_obj_t * btn, lv_obj_t * lbl, void (*cb)(Button *)){
  obj = btn;
  lv_cont_set_fit(obj, true, true);
  label = Label(lbl);
  lv_obj_set_free_num(obj, (uint32_t)this);
  callback = cb;
}
void Button::size(uint16_t width, uint16_t height){
  lv_cont_set_fit(obj, false, false);
  lv_obj_set_size(obj, width, height);
}
