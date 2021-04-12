import sensor, image, lcd, time
import KPU as kpu
import gc
import video
from fpioa_manager import fm
from machine import UART
from board import board_info
from Maix import GPIO,I2S
lcd.init()
#num=0
classmates = [b'1 1厨余垃圾',b'2 1可回收垃圾',b'无垃圾放置',b'3 1其他垃圾',b'4 1有害垃圾']

fm.register(10, fm.fpioa.UART1_TX, force=True)
fm.register(11, fm.fpioa.UART1_RX, force=True)
fm.register(34,  fm.fpioa.I2S0_OUT_D1, force=True)
fm.register(35,  fm.fpioa.I2S0_SCLK, force=True)
fm.register(33,  fm.fpioa.I2S0_WS, force=True)
uart = UART(UART.UART1, 115200, 8, 1, 0, timeout=1000, read_buf_len=4096)

AUDIO_PA_EN_PIN = 32
i2s = I2S(I2S.DEVICE_0)#新建一个I2S对象
i2s.channel_config(i2s.CHANNEL_1, I2S.TRANSMITTER, resolution=I2S.RESOLUTION_16_BIT,
                       cycles=I2S.SCLK_CYCLES_32, align_mode=I2S.RIGHT_JUSTIFYING_MODE)#I2S通道配置函数


if AUDIO_PA_EN_PIN:
    fm.register(AUDIO_PA_EN_PIN, fm.fpioa.GPIO1, force=True)
    wifi_en = GPIO(GPIO.GPIO1, GPIO.OUT)
    wifi_en.value(1)

boot_pin = 16 # board_info.BOOT_KEY
fm.register(boot_pin, fm.fpioa.GPIOHS0)
key = GPIO(GPIO.GPIOHS0, GPIO.PULL_UP)

boot_win = 17
fm.register(boot_win, fm.fpioa.GPIOHS1)
win = GPIO(GPIO.GPIOHS1, GPIO.IN)


def Video_Play():
    v = video.open("/sd/badapple.avi")
    print(v)
    v.volume(50)
    while True:
       if v.play() == 0 or key.value() == 0:
            #print("play end")
            break
    v.__del__()


def main(labels = None, model_addr="/sd/m.kmodel", sensor_window=(224, 224), lcd_rotation=0, sensor_hmirror=False, sensor_vflip=False):
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.set_windowing(sensor_window)
    sensor.set_hmirror(sensor_hmirror)
    sensor.set_vflip(sensor_vflip)
    sensor.run(1)

    lcd.init(type=1)
    lcd.rotation(lcd_rotation)
    lcd.clear(lcd.WHITE)

    try:
        task = None
        task = kpu.load(model_addr)
        while(True):
            img = sensor.snapshot()
            t = time.ticks_ms()
            fmap = kpu.forward(task, img)
            t = time.ticks_ms() - t
            image.font_load(image.UTF8, 16, 16, '/sd/0xA00000_font_uincode_16_16_tblr.Dzk')
            plist=fmap[:]
            pmax=max(plist)
            max_index=plist.index(pmax)
            img.draw_string(0,0,b"你检测到的物体是:\n" ,x_spacing=2, mono_space=2)
            img.draw_string(0,20,classmates[max_index],x_spacing=2, mono_space=2)
            output_str="%d" % (max_index+1) #方式1
            #print('you send:',output_str)
            if output_str != '3':
              if win.value() == 1:
               uart.write(output_str+'\r\n')
               #global num
               #num=num+1
               #img.draw_string(0,20,str(num),x_spacing=2, mono_space=2,color=(255,0,0))
               img.draw_string(150,20,b'OK',x_spacing=2, mono_space=2,color=(255,0,0))
               #print('you send:','1')
            lcd.display(img)
    finally:
        if not task is None:
            kpu.deinit(task)


if __name__ == "__main__":
  Video_Play()
  if key.value() == 0:
    try:
        labels = ["youhai", "qita", "mianban", "kehui", "chuyv"]
        # main(anchors = anchors, labels=labels, model_addr=0x300000, lcd_rotation=0)
        main(labels=labels, model_addr="/sd/m.kmodel")
    finally:
        gc.collect()
