#include <pebble.h>
#include "mainWindow.h"

static Window *s_window;
static Layer *canvas;
static GBitmap *bg;
static BitmapLayer *bg_layer;

void eye_dot_setup()
{
    
}

static void canvas_update_proc(Layer *layer, GContext *ctx)
{

}

static void window_load(Window *window)
{
    Layer *window_layer = window_get_root_layer(s_window);
    GRect window_bounds = layer_get_bounds(window_layer);

    // Setting up the layer I'll draw on.
    canvas = layer_create(window_bounds);
    layer_set_update_proc(canvas, canvas_update_proc);
    layer_add_child(window_layer, canvas);

    // Setting up the background image
    bg = gbitmap_create_with_resource(RESOURCE_ID_BG);
    bg_layer = bitmap_layer_create(window_bounds);
    bitmap_layer_set_compositing_mode(bg_layer, GCompOpSet);
    bitmap_layer_set_bitmap(bg_layer, bg);
    layer_add_child(window_layer, bitmap_layer_get_layer(bg_layer));
}

void window_unload(Window *window)
{
    gbitmap_destroy(bg);
    bitmap_layer_destroy(bg_layer);
}

void main_window_create(void)
{
    s_window = window_create();
    // Tell it which functions to call for loading and unloading.
    window_set_window_handlers(s_window, (WindowHandlers){
                                             .load = window_load,
                                             .unload = window_unload,
                                         });
    window_stack_push(s_window, true); // true == animated
}

void main_window_destroy(void)
{
    window_destroy(s_window);
}