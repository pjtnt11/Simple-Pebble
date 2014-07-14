#include "pebble.h"

Window *window;
TextLayer *text_date1_layer;
TextLayer *text_date2_layer;
TextLayer *text_time_layer;
Layer *line_layer;

void line_layer_update_callback(Layer *layer, GContext* ctx) 
{
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}

void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) 
{
  static char date2_text[] = "Xxx 00";
	static char time_text[] = "00:00";
  static char date1_text[] = "Xxx 0000";
  char *time_format;

  strftime(date2_text, sizeof(date2_text), "%a %e", tick_time);
  text_layer_set_text(text_date2_layer, date2_text); 
  strftime(date1_text, sizeof(date1_text), "%b %Y", tick_time);
  text_layer_set_text(text_date1_layer, date1_text);
  
  if (clock_is_24h_style()) 
	{
    time_format = "%R";
  } 
	else 
	{
    time_format = "%I:%M";
  }

  strftime(time_text, sizeof(time_text), time_format, tick_time);

  if (!clock_is_24h_style() && (time_text[0] == '0')) 
	{
    memmove(time_text, &time_text[1], sizeof(time_text) - 1);
  }
	text_layer_set_text(text_time_layer, time_text);
}

void handle_deinit(void) 
{
  tick_timer_service_unsubscribe();
}

static void handle_tick(struct tm *tick_time, TimeUnits units_changed) 
{
  if (HOUR_UNIT) 
  {
    update_hours(tick_time);
  }
}

void handle_init(void) 
{
  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
  
  window = window_create();
  window_stack_push(window, true /* Animated */);
  window_set_background_color(window, GColorBlack);
	Layer *window_layer = window_get_root_layer(window);
  
  text_date2_layer = text_layer_create(GRect(0, 37, 144, 168-6));
  text_layer_set_text_color(text_date2_layer, GColorWhite);
  text_layer_set_background_color(text_date2_layer, GColorClear);
  text_layer_set_font(text_date2_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_DATE_22)));
  text_layer_set_text_alignment(text_date2_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_date2_layer));
  
  text_time_layer = text_layer_create(GRect(0, 55, 144, 168-6));
  text_layer_set_text_color(text_time_layer, GColorWhite);
  text_layer_set_background_color(text_time_layer, GColorClear);
  text_layer_set_font(text_time_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_TIME_45)));
  text_layer_set_text_alignment(text_time_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_time_layer));
  
  text_date1_layer = text_layer_create(GRect(0, 100, 144, 168-6));
  text_layer_set_text_color(text_date1_layer, GColorWhite);
  text_layer_set_background_color(text_date1_layer, GColorClear);
  text_layer_set_font(text_date1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_DATE_22)));
  text_layer_set_text_alignment(text_date1_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_date1_layer));
}

int main(void) 
{
  handle_init();
  app_event_loop();
  handle_deinit();
}