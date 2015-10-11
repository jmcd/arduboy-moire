#include <SPI.h>
#include <EEPROM.h>
#include "Arduboy.h"
#include "Scene.h"

Arduboy display;

Scene *scene;

void setup() {
  SPI.begin();
  display.start();
  display.clearDisplay();
  display.display();

  scene = (Scene *)malloc(sizeof(struct Scene));
  sceneInit(scene);
}

void loop() {

  if (!(display.nextFrame())) {
    return;
  }

  Line *tail = sceneLine(scene, 0);
  drawLine(tail, 0);

  sceneAdvance(scene);

  for (int i = 0; i < numberOfLines; i++) {
    Line *line = sceneLine(scene, i);
    drawLine(line, 1);
  }

  display.display();
}

void drawLine(Line *line, uint16_t color) {
    display.drawLine(line->e0.p.x, line->e0.p.y, line->e1.p.x, line->e1.p.y, color);
}

