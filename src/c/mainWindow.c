#include <pebble.h>
#include "mainWindow.h"

#define NUMBER_OF_DIGITS 4

static const int NUMBERS[] = {
    RESOURCE_ID_NUM_0,
    RESOURCE_ID_NUM_1,
    RESOURCE_ID_NUM_2,
    RESOURCE_ID_NUM_3,
    RESOURCE_ID_NUM_4,
    RESOURCE_ID_NUM_5,
    RESOURCE_ID_NUM_6,
    RESOURCE_ID_NUM_7,
    RESOURCE_ID_NUM_8,
    RESOURCE_ID_NUM_9
};

static GBitmap *digits[NUMBER_OF_DIGITS];
static BitmapLayer *digit_layers[NUMBER_OF_DIGITS];

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
    // Get the layer for this window to put stuff on it.
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

    // Time layer
    // TODO store coords for each digit within the time display area I made in GIMP
    // and use a for loop to create the layers, giving it offset values so I can easily move
    // the whole thing.
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