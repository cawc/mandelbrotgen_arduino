/*
 * Mandelbrot generator for 128x64 OLED screen with Arduino
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <complex.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int mandelbrot(Complex z0, int maxiter) {
  Complex z = z0;
  for(int i=0; i<maxiter; i++) {
    if(sqrt(z.real()*z.real() + z.imag()*z.imag()) > 2){
      //Serial.println(sqrt(z.real()*z.real() + z.imag()*z.imag()),20);
      return i;
    }
    z = z*z + z0;
  }
  //Serial.println("STABLE FOUND");
  return 0;
}

void setup() {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.fillScreen(WHITE);

  int width = 128,
      height = 64,
      xc = 0,
      yc = 0;

  double x = -0.745428,
         y =  0.113009,
         r =  0.00003;

  double xmin = x-r,
         xmax = x+r,
         ymin = y-r,
         ymax = y+r;

  
  
  display.display();

   for(double x=xmin; x<xmax; x=x+abs(xmax-xmin)/width){
    xc+=1;
    for(double y=ymin; y<ymax; y=y+abs(ymax-ymin)/height){
      yc+=1;
      Complex c(x,y);
      if (mandelbrot(c,200) == 0){
        //Serial.print(xc);
        //Serial.print(", ");
        //Serial.print(64-yc);
        display.drawPixel(xc,64-yc,BLACK);
        //Serial.println(" stable, turned on");
        display.display();
      }
    }
    yc = 0;
  }
  
  display.display();
}


void loop() {
  
}
