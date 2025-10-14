import pyb, sensor, time
from pyb import UART

sensor.reset()  # Reset and initialize the sensor.

LED = pyb.LED(2)

LED.on()
sensor.set_pixformat(sensor.RGB565)  # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)  # Set frame size to QVGA (320x240)
sensor.set_auto_whitebal(False)
sensor.set_auto_exposure(False)
# sensor.set_auto_exposure(False, exposure_us = 38000)
# sensor.set_auto_gain(True, gain_db = 100)
sensor.set_brightness(-3)
sensor.set_windowing((240, 240))

sensor.skip_frames(time=2000)  # Wait for settings take effect.
clock = time.clock()  # Create a clock object to track the FPS.

DEBUG = True
CROSSHAIR = False

# Ball, Yellow, Blue
thresholds = [(23, 63, 9, 57, 21, 41), (46, 81, -16, 6, 23, 43), (18, 33, -18, -5, -27, -5)]

uart = UART(3, 115200, timeout_char = 10)

LED.off()

while True:
    clock.tick()  # Update the FPS clock.
    img = sensor.snapshot()  # Take a picture and return the image.
    ballBlobs = img.find_blobs([thresholds[0]], x_stride=1, y_stride=1, area_threshold=1, pixels_threshold=1, merge=True, margin=0)
    goalBlobs = img.find_blobs([thresholds[1], thresholds[2]], x_stride=5, y_stride=5, area_threshold=30, pixels_threshold=30, merge=True, margin=5)

    # Ball, Yellow, Blue
    data = [255, 255, 120, 120, 120, 120, 120, 120]

    largestBlob = [None, None]
    for blob in ballBlobs:
        if largestBlob[0] == None:
            largestBlob[0] = blob
        elif blob.area() > largestBlob[0].area():
            largestBlob[0] = blob
    if largestBlob[0] != None:
        data[2] = largestBlob[0].cx()
        data[3] = largestBlob[0].cy()

    largestBlob = [None, None]
    for blob in goalBlobs:
        if blob.code() == 1:
            if largestBlob[0] == None:
                largestBlob[0] = blob
            elif blob.area() > largestBlob[0].area():
                largestBlob[0] = blob
        else:
            if largestBlob[1] == None:
                largestBlob[1] = blob
            elif blob.area() > largestBlob[1].area():
                largestBlob[1] = blob
    if largestBlob[0] != None:
        data[4] = largestBlob[0].cx()
        data[5] = largestBlob[0].cy()
    if largestBlob[1] != None:
        data[6] = largestBlob[1].cx()
        data[7] = largestBlob[1].cy()

    if CROSSHAIR:
        img.draw_line(115, 120, 125, 120)
        img.draw_line(120, 115, 120, 125)
    if DEBUG:
        img.draw_line(120, 120, data[2], data[3]);
        img.draw_line(120, 120, data[4], data[5]);
        img.draw_line(120, 120, data[6], data[7]);

    # print(clock.fps())
    # print(data)
    for byte in data:
        uart.writechar(byte)
