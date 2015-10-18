
const int screenWidth = 128;
const int screenHeight = 64;

const int numberOfLines = 30;

const int maxSpeed = 6;

/*
 * structs that describe the scene
 */

struct Point {
  int x;
  int y;
};

struct Velocity {
  int dx;
  int dy;
};

struct End {
  Point p;
  Velocity v;
};

struct Line {
  End e0;
  End e1;
};

struct Scene {
  Line lines[numberOfLines];
  int indexOfHeadLine = numberOfLines - 1;
};

/*
 * scene initialization
 */

Point randomPoint() {
  return { random(screenWidth), random(screenHeight) };
}

int randomSpeed() {
  return random(1, maxSpeed);
}

Velocity randomVelocity() {
  return { randomSpeed(), randomSpeed() };
}

End randomEnd() {
  return { randomPoint(), randomVelocity() };
}

Line randomLine() {
  return { randomEnd(), randomEnd() };
}

Point PointZero = { 0, 0 };
Velocity VelocityZero = { 0, 0 };
End EndZero = { PointZero, VelocityZero };
Line LineZero = { EndZero, EndZero };

/*
 * functions to advance basic value types
 */

int sign(int x) {
    return (x > 0) - (x < 0);
}

End endByAdvancingEnd(End en) {  
  
  int ndx = en.v.dx;
  int ndy = en.v.dy;
  
  int nx = en.p.x + ndx;
  int ny = en.p.y + ndy;

  if (nx < 0 || nx > screenWidth) {
    ndx = -1 * sign(ndx) * randomSpeed();
    nx = en.p.x + ndx;
  }
  if (ny < 0 || ny > screenHeight) {
    ndy  = -1 * sign(ndy) * randomSpeed();
    ny = en.p.y + ndy;
  }

  return {
    { nx, ny },
    { ndx, ndy }
  };
}

Line lineByAdvancingLine(Line line) {
  return {
    endByAdvancingEnd(line.e0),
    endByAdvancingEnd(line.e1)
  };
}

/*
 * functions to operate on pointer to scene
 */

void sceneInit(Scene *scene) {
  for (int i = 0; i < numberOfLines; i++) {
    scene->lines[i] = LineZero;
  }
  scene->lines[scene->indexOfHeadLine] = randomLine();
}

Line *sceneLine(Scene *scene, int index) {
  int j = (scene->indexOfHeadLine + 1 + index) % numberOfLines;
  return &(scene->lines[j]);
}

void sceneAdvance(Scene *scene) {  
  Line head = scene->lines[scene->indexOfHeadLine];
  Line nextHead = lineByAdvancingLine(head);
  scene->indexOfHeadLine = (scene->indexOfHeadLine + 1) % numberOfLines;
  scene->lines[scene->indexOfHeadLine] = nextHead;
}
