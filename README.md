# ESPLedLamp

ESP32 firmware to control a custom led floor lamp, made up of **10 led** strips with 60 adjustable leds each one. Each strip is **arranged vertically** with the first LED at the bottom and connects to a separate ESP port.

If needed, the firmware can be easily modified to allow a different number of strips, LEDs per strip, or a different connection and disposittion (a single split strip with a snake pattern, connected to a single port).

The firmware connects the ESP32 to WiFi, and starts a web server capable of sending the lamp the status and settings, and receiving http requests to modify the current status, mode, and settings derived from the current mode (colors, brightness, palettes, refresh rates, etc.).

It is designed to work together with the Android app to control the led floor lamp, but accepts requests from any device from the local network, which allows you to easily develop other clients to control it, whether they are simple web pages, IOS apps, Android TV apps or simple controllers based on any chipset with WiFi capabilities
