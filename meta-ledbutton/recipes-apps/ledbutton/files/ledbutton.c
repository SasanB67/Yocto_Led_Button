// LED on while button pressed, off when released (libgpiod v2)
#include <gpiod.h>
#include <stdio.h>

#define CHIP    "/dev/gpiochip0"
#define LED     17   // GPIO17 (pin 11)
#define BUTTON  27   // GPIO27 (pin 13), button to GND

int main(void)
{
	unsigned int led = LED, button = BUTTON;

	struct gpiod_chip *chip = gpiod_chip_open(CHIP);
	if (!chip) {
		perror("gpiod_chip_open");
		return 1;
	}

	struct gpiod_line_settings *led_set = gpiod_line_settings_new();
	gpiod_line_settings_set_direction(led_set, GPIOD_LINE_DIRECTION_OUTPUT);

	struct gpiod_line_settings *btn_set = gpiod_line_settings_new();
	gpiod_line_settings_set_direction(btn_set, GPIOD_LINE_DIRECTION_INPUT);
	gpiod_line_settings_set_bias(btn_set, GPIOD_LINE_BIAS_PULL_UP);
	gpiod_line_settings_set_active_low(btn_set, true);  // pressed = 1
	gpiod_line_settings_set_edge_detection(btn_set, GPIOD_LINE_EDGE_BOTH);
	gpiod_line_settings_set_debounce_period_us(btn_set, 10000);

	struct gpiod_line_config *cfg = gpiod_line_config_new();
	gpiod_line_config_add_line_settings(cfg, &led, 1, led_set);
	gpiod_line_config_add_line_settings(cfg, &button, 1, btn_set);

	struct gpiod_line_request *req = gpiod_chip_request_lines(chip, NULL, cfg);
	if (!req) {
		perror("gpiod_chip_request_lines");
		return 1;
	}

	struct gpiod_edge_event_buffer *events = gpiod_edge_event_buffer_new(1);

	while (1) {
		
		gpiod_line_request_set_value(req, led,
			gpiod_line_request_get_value(req, button));

		
		gpiod_line_request_wait_edge_events(req, -1);
		gpiod_line_request_read_edge_events(req, events, 1);
	}
}
