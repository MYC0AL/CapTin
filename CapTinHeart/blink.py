from machine import Pin
import time

led = Pin(17, Pin.OUT)

while True:
    led.value(1)  # Set pin HIGH
    time.sleep(1)
    led.value(0)  # Set pin LOW
    time.sleep(1)