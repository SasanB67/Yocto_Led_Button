Description: Controls an LED using a pushbutton. The LED turns ON while the button is pressed and OFF when released.

Pin connections and wiring:
- GPIO17 (physical pin 11): Connect to a 220–330 Ω resistor, then to the LED's positive leg (anode).
- GND (physical pin 6): Connect to the LED's negative leg (cathode).
- GPIO27 (physical pin 13): Connect to one side of the pushbutton.
- GND (physical pin 6): Connect to the other side of the pushbutton.
- The button uses the Raspberry Pi's internal pull-up resistor, so no external pull-up resistor is needed.
