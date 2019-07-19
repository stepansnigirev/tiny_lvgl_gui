#include "gui.h"
#include <mbed.h>
#include <tft.h>
#include <touchpad.h>
#include <lvgl.h>
#include "utility/qrcode.h"

/* timer to count time in a loop and update the lvgl */
static volatile int t = 0;
Ticker ms_tick;
static void onMillisecondTicker(void){
  t++;
}

LV_FONT_DECLARE(square1);
LV_FONT_DECLARE(square2);
LV_FONT_DECLARE(square3);
LV_FONT_DECLARE(square4);
LV_FONT_DECLARE(square5);
LV_FONT_DECLARE(square6);
LV_FONT_DECLARE(square7);
LV_FONT_DECLARE(square8);


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
  lv_obj_align(obj, NULL, mode, 0, lv_obj_get_y(obj));
}

/********* Label class *********/

Label::Label(const char * txt){
  obj = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(obj, txt);
  lv_label_set_long_mode(obj, LV_LABEL_LONG_BREAK);
}
Label::Label(std::string txt){
  obj = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(obj, txt.c_str());
  lv_label_set_long_mode(obj, LV_LABEL_LONG_BREAK);
}
Label::Label(lv_obj_t * lbl){
  obj = lbl;
  lv_label_set_long_mode(obj, LV_LABEL_LONG_BREAK);
}
void Label::text(const char * txt){
  if(obj == NULL){ return; }
  lv_label_set_text(obj, txt);
}
void Label::text(std::string txt){
  text(txt.c_str());
}
void Label::alignText(int mode){
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
Button::Button(lv_res_t (*callback)(lv_obj_t * btn), const char * txt){
  obj = lv_btn_create(lv_scr_act(), NULL);
  lv_btn_set_action(obj, LV_BTN_ACTION_CLICK, callback);
  lv_obj_t * lbl = lv_label_create(obj, NULL);
  lv_label_set_text(lbl, txt);
  label = Label(lv_obj_get_child(obj, NULL));
  label.alignText(ALIGN_TEXT_CENTER);
}
Button::Button(lv_res_t (*callback)(lv_obj_t * btn), std::string txt){
  obj = lv_btn_create(lv_scr_act(), NULL);
  lv_btn_set_action(obj, LV_BTN_ACTION_CLICK, callback);
  lv_obj_t * lbl = lv_label_create(obj, NULL);
  lv_label_set_text(lbl, txt.c_str());
  label = Label(lv_obj_get_child(obj, NULL));
  label.alignText(ALIGN_TEXT_CENTER);
}
void Button::size(uint16_t width, uint16_t height){
  // lv_cont_set_fit(obj, false, false);
  lv_obj_set_size(obj, width, height);
  label.size(width, height);
}
void Button::id(int32_t i){
  lv_obj_set_free_num(obj, i);
  // _id = i;
}
int32_t Button::id(){
  return lv_obj_get_free_num(obj);
}
void Button::disable(){
  lv_btn_set_state(obj, LV_BTN_STATE_INA);
}
void Button::enable(){
  lv_btn_set_state(obj, LV_BTN_STATE_REL);
}

/********* Keyboard class *********/

Keyboard::Keyboard(lv_obj_t * btn){
  obj = btn;
}
Keyboard::Keyboard(lv_res_t (*callback)(lv_obj_t * btn, const char * key), const char * keys[]){
  obj = lv_btnm_create(lv_scr_act(), NULL);
  lv_btnm_set_map(obj, keys);
  lv_btnm_set_action(obj, callback);
}
void Keyboard::size(uint16_t width, uint16_t height){
  // lv_cont_set_fit(obj, false, false);
  lv_obj_set_size(obj, width, height);
}

/********* QR code class *********/
static lv_style_t black_square;

QR::QR(lv_obj_t * qr){
  create(qr);
}
QR::QR(const char * txt){
  create();
  text(txt);
}
QR::QR(std::string txt){
  create();
  text(txt);
}
void QR::text(const char * txt){
  if(obj == NULL){ return; }
  text_to_encode = txt;
  resize();
}
void QR::text(std::string txt){
  text(txt.c_str());
}
void QR::size(uint16_t size){
  lv_obj_set_size(obj, size, size);
  width = size;
  resize();
}
void QR::resize(){
  int qrSize = 10;
  int sizes[] = { 14, 26, 42, 62, 84, 106, 122, 152, 180, 213, 251, 287, 331, 362, 412, 480, 504, 560, 624, 666, 711, 779, 857, 911, 997, 1059, 1125, 1190 };
  int len = text_to_encode.length();
  for(int i=0; i<sizeof(sizes)/sizeof(int); i++){
    if(sizes[i] > len){
      qrSize = i+1;
      break;
    }
  }

  QRCode qrcode;
  uint8_t * qrcodeData = (uint8_t *)calloc(qrcode_getBufferSize(qrSize), sizeof(uint8_t));
  qrcode_initText(&qrcode, qrcodeData, qrSize, 1, text_to_encode.c_str());

  char * qr = (char *)calloc((qrcode.size+2)*(qrcode.size+1)+1, sizeof(char));
  char * c = qr;

  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if(qrcode_getModule(&qrcode, x, y)){
        c[0] = '1';
      }else{
        c[0] = '0';
      }
      c++;
    }
    c[0] = '\n';
    c++;
  }
  free(qrcodeData);
  lv_style_copy(&black_square, &lv_style_plain);
  uint16_t font_size = width / qrcode.size;
  if(font_size > 8){ font_size = 8; }
  if(font_size < 1){ font_size = 1; }
  lv_font_t * fonts[] = { &square1, &square2, &square3, &square4, &square5, &square6, &square7, &square8 };
  black_square.text.font = fonts[font_size-1];
	black_square.text.letter_space = 0;
  black_square.text.line_space = 0;
  black_square.text.color = LV_COLOR_HEX(0x000000);
  lv_label_set_style(obj, &black_square);
	lv_label_set_text(obj, qr);
  free(qr);
  lv_obj_set_size(obj, width, width);
  lv_label_set_align(obj, ALIGN_TEXT_CENTER);
}
void QR::create(lv_obj_t * qr){
  if(qr == NULL){
    obj = lv_label_create(lv_scr_act(), NULL);
  }else{
    obj = qr;
  }
  width = 100;
  lv_obj_set_size(obj, width, width);
  text_to_encode = "QR code";
}
