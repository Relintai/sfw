
//--STRIP
#ifndef GUI_H
#define GUI_H
//--STRIP

// -----------------------------------------------------------------------------
// immediate ui framework
// - rlyeh, public domain
//
// @todo: logger/console
// @todo: surround-adaptive window resizing. ie, surrounding windows adapting theirselves to fit dragged active window

//--STRIP
//#include "core/color.h"
//#include "core/int_types.h"
//#include "core/vector2.h"
//--STRIP


enum PANEL_FLAGS {
    PANEL_OPEN = 1,
};

int ui_notify(const char *title, const char *body);
int ui_window(const char *title, int *enabled);
int  ui_panel(const char *title, int flags); // may be embedded inside a window, or standalone
int   ui_collapse(const char *label, const char *id);
int   ui_collapseo(const char *label, const char *id);
int   ui_contextual();
int    ui_section(const char *title);
int    ui_int(const char *label, int *value);
int    ui_bool(const char *label, bool *value);
int    ui_short(const char *label, short *value);
int    ui_float_(const char *label, float *value, float step);
int    ui_float2_(const char *label, float value[2], float step);
int    ui_float3_(const char *label, float value[3], float step);
int    ui_float4_(const char *label, float value[4], float step);
int    ui_float(const char *label, float *value);
int    ui_float2(const char *label, float value[2]);
int    ui_float3(const char *label, float value[3]);
int    ui_float4(const char *label, float value[4]);
int    ui_mat33(const char *label, float mat33[9]);
int    ui_mat34(const char *label, float mat34[12]);
int    ui_mat44(const char *label, float mat44[16]);
int    ui_double(const char *label, double *value);
int    ui_buffer(const char *label, char *buffer, int buflen);
int    ui_string(const char *label, char **string);
int    ui_color3(const char *label, unsigned *color); //[0..255]
int    ui_color3f(const char *label, float color[3]); //[0..1]
int    ui_color4(const char *label, unsigned *color); //[0..255]
int    ui_color4f(const char *label, float color[4]); //[0..1]
int    ui_unsigned(const char *label, unsigned *value);
int    ui_unsigned2(const char *label, unsigned *value);
int    ui_unsigned3(const char *label, unsigned *value);
int    ui_button(const char *label);
int    ui_button_transparent(const char *label);
int    ui_buttons(int buttons, /*labels*/...);
int    ui_toolbar(const char *options); // int choice = ui_toolbar("A;B;C;D");
int    ui_submenu(const char *options); // int choice = ui_submenu("A;B;C;D");
int    ui_browse(const char **outfile, bool *inlined); // may be embedded inside a window or inside a panel
int    ui_toggle(const char *label, bool *value);
int    ui_dialog(const char *title, const char *text, int choices, bool *show); // @fixme: return
int    ui_list(const char *label, const char **items, int num_items, int *selector);
int    ui_radio(const char *label, const char **items, int num_items, int *selector);
int    ui_texture(const char *label, texture_t t);
int    ui_subtexture(const char *label, texture_t t, unsigned x, unsigned y, unsigned w, unsigned h);
int    ui_image(const char *label, handle id, unsigned w, unsigned h); //(w,h) can be 0
int    ui_subimage(const char *label, handle id, unsigned iw, unsigned ih, unsigned sx, unsigned sy, unsigned sw, unsigned sh);
int    ui_colormap(const char *label, colormap_t *cm); // returns num member changed: 1 for color, 2 for texture map
int    ui_separator();
int    ui_bitmask8(const char *label, uint8_t *bits);
int    ui_bitmask16(const char *label, uint16_t *bits);
int    ui_console();
int    ui_clampf_(const char *label, float *value, float minf, float maxf, float step);
int    ui_clampf(const char *label, float *value, float minf, float maxf);
int    ui_label(const char *label);
int    ui_label2(const char *label, const char *caption);
int    ui_label2_bool(const char *label, bool enabled);
int    ui_label2_float(const char *label, float value);
int    ui_label2_toolbar(const char *label, const char *icons);
int    ui_slider(const char *label, float *value);
int    ui_slider2(const char *label, float *value, const char *caption);
int   ui_contextual_end(int close);
int   ui_collapse_clicked();
int   ui_collapse_end();
int  ui_panel_end();
int ui_window_end();

int  ui_show(const char *panel_or_window_title, int enabled);
int  ui_dims(const char *panel_or_window_title, float width, float height);
int  ui_visible(const char *panel_or_window_title); // @todo: include ui_collapse() items that are open as well?
vec2 ui_get_dims();

int  ui_enable();
int  ui_enabled();
int  ui_disable();

int ui_has_menubar();
int ui_menu(const char *items); // semicolon-separated or comma-separated items
int ui_menu_editbox(char *buf, int bufcap);
int ui_item();

int ui_popups(); // ui_any_popup()? ui_has_popups()?
int ui_hover(); // ui_is_hover()?
int ui_active(); // ui_is_active()?

int ui_demo(int do_windows);
void *ui_handle();


//--STRIP
#endif
//--STRIP

