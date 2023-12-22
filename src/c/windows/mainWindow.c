#include <pebble.h>
#include "mainWindow.h"
#include "../modules/ImageCollection.h"
#include "../modules/TextCollection.h"

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

static Window *s_window;
static Layer *canvas;
static GBitmap *bg;
static BitmapLayer *bg_layer;

struct ImageCollection * background;
struct ImageCollection * time;


static void window_load(Window *window)
{
    // Get the layer for this window to put stuff on it.
    Layer *window_layer = window_get_root_layer(s_window);
    GRect window_bounds = layer_get_bounds(window_layer);

    APP_LOG(APP_LOG_LEVEL_INFO, "Initializing ImageCollection struct");
    background = init_image_collection((uint32_t) 1);
    if (background == NULL)
    {
        APP_LOG(APP_LOG_LEVEL_ERROR, "ImageCollection pointer is NULL");
        return;
    }

    // Time collection. 4 digits and the semicolon in the middle.
    APP_LOG(APP_LOG_LEVEL_INFO, "Initializing ImageCollection struct");
    time = init_image_collection((uint32_t) 5);
    if (time == NULL)
    {
        APP_LOG(APP_LOG_LEVEL_ERROR, "ImageCollection pointer is NULL");
        return;
    }

    add_image(background, window_bounds, RESOURCE_ID_BGV2, window_layer);
    add_image(time, GRect(0,0,23,39), NUMBERS[0],window_layer);
    add_image(time, GRect(0,0,23,39), NUMBERS[0],window_layer);
    add_image(time, GRect(0,0,23,39), RESOURCE_ID_MIDDLE_DOTS,window_layer);
    add_image(time, GRect(0,0,23,39), NUMBERS[0],window_layer);
    add_image(time, GRect(0,0,23,39), NUMBERS[0],window_layer);
}

void window_unload(Window *window)
{
    destroy_image_collection(background);
    destroy_image_collection(time);
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