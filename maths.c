// (c) 2006 Karol Maciaszek <karol.maciaszek@gmail.com>

#include "struct.h"
#include "maths.h"
#include "math.h"

float xcircle(float radius, int angle) {
  float radian;
  float y;

  if (angle >= 0) {
    angle = angle - floor(angle / 360) * 360;
  } else {
    angle = 360 + angle - floor(angle / 360) * 360;
  }

  if (angle <= 90) {
    radian = 2 * M_PI * angle / 360;
    y = radius / sqrt(1 / tan(radian) + 1);
    return sqrt(radius*radius - y*y);
  } else if (angle > 90 && angle <= 180) {
    radian = 2 * M_PI * (180 - angle) / 360;
    y = radius / sqrt(1 / tan(radian) + 1);
    return -1 * sqrt(radius*radius - y*y);
  } else if (angle > 180 && angle <= 270) {
    radian = 2 * M_PI * (angle - 180) / 360;
    y = -1 * radius / sqrt(1 / tan(radian) + 1);
    return -1 * sqrt(radius*radius - y*y);
  } else if (angle > 270 && angle <= 360) {
    radian = 2 * M_PI * (360 - angle) / 360;
    y = -1 * radius / sqrt(1 / tan(radian) + 1);
    return sqrt(radius*radius - y*y);
  }
}

float ycircle(float radius, int angle) {
  float radian;

  if (angle >= 0) {
    angle = angle - floor(angle / 360) * 360;
  } else {
    angle = 360 + angle - floor(angle / 360) * 360;
  }

  if (angle <= 90) {
    radian = 2 * M_PI * angle / 360;
    return radius / sqrt(1 / tan(radian) + 1);
  } else if (angle > 90 && angle <= 180) {
    radian = 2 * M_PI * (180 - angle) / 360;
    return radius / sqrt(1 / tan(radian) + 1);
  } else if (angle > 180 && angle <= 270) {
    radian = 2 * M_PI * (angle - 180) / 360;
    return -1 * radius / sqrt(1 / tan(radian) + 1);
  } else if (angle > 270 && angle <= 360) {
    radian = 2 * M_PI * (360 - angle) / 360;
    return -1 * radius / sqrt(1 / tan(radian) + 1);
  }
}

void calculateNormals(TTriangle *t, int c) {
  int i, j, k;

  printf("  Calculating normals...");

  for (i = 0; i < c; i++) {
//    printf("  Triangle #%d: a[%f,%f,%f] b[%f,%f,%f] c[%f,%f,%f]\n", i, t[i].a->x, t[i].a->y, t[i].a->z, t[i].b->x, t[i].b->y, t[i].b->z, t[i].c->x, t[i].c->y, t[i].c->z);

//    printf("    Vertex: a[%f,%f,%f]\n", t[i].a->x, t[i].a->y, t[i].a->z, k);
    k = 0;
    t[i].a->nx = 0; t[i].a->ny = 0; t[i].a->nz = 0;
    for (j = 0; j < c; j++) {
      if (t[i].a->x == t[j].a->x && t[i].a->y == t[j].a->y && t[i].a->z == t[j].a->z) {
        normalv(&t[i].a->nx, &t[i].a->ny, &t[i].a->nz, t[i].a->x, t[i].a->y, t[i].a->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z);
//        printf("      #%d: *a[%f,%f,%f] b[%f,%f,%f] c[%f,%f,%f] normal[%f,%f,%f]\n", j, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z, t[i].a->nx, t[i].a->ny, t[i].a->nz);
        k++;
      }
      if (t[i].a->x == t[j].b->x && t[i].a->y == t[j].b->y && t[i].a->z == t[j].b->z) {
        normalv(&t[i].a->nx, &t[i].a->ny, &t[i].a->nz, t[i].a->x, t[i].a->y, t[i].a->z, t[j].c->x, t[j].c->y, t[j].c->z, t[j].a->x, t[j].a->y, t[j].a->z);
//        printf("      #%d: a[%f,%f,%f] *b[%f,%f,%f] c[%f,%f,%f] normal[%f,%f,%f]\n", j, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z, t[i].a->nx, t[i].a->ny, t[i].a->nz);
        k++;
      }
      if (t[i].a->x == t[j].c->x && t[i].a->y == t[j].c->y && t[i].a->z == t[j].c->z) {
        normalv(&t[i].a->nx, &t[i].a->ny, &t[i].a->nz, t[i].a->x, t[i].a->y, t[i].a->z, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z);
//        printf("      #%d: a[%f,%f,%f] b[%f,%f,%f] *c[%f,%f,%f] normal[%f,%f,%f]\n", j, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z, t[i].a->nx, t[i].a->ny, t[i].a->nz);
        k++;
      }
    }

//    printf("    Vertex: b[%f,%f,%f]\n", t[i].b->x, t[i].b->y, t[i].b->z, k);
    k = 0;
    t[i].b->nx = 0; t[i].b->ny = 0; t[i].b->nz = 0;
    for (j = 0; j < c; j++) {
      if (t[i].b->x == t[j].a->x && t[i].b->y == t[j].a->y && t[i].b->z == t[j].a->z)  {
        normalv(&t[i].b->nx, &t[i].b->ny, &t[i].b->nz, t[i].b->x, t[i].b->y, t[i].b->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z);
//        printf("      #%d: *a[%f,%f,%f] b[%f,%f,%f] c[%f,%f,%f] normal[%f,%f,%f]\n", j, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z, t[i].a->nx, t[i].a->ny, t[i].a->nz);
        k++;
      }
      if (t[i].b->x == t[j].b->x && t[i].b->y == t[j].b->y && t[i].b->z == t[j].b->z) {
	normalv(&t[i].b->nx, &t[i].b->ny, &t[i].b->nz, t[i].b->x, t[i].b->y, t[i].b->z, t[j].c->x, t[j].c->y, t[j].c->z, t[j].a->x, t[j].a->y, t[j].a->z);
//        printf("      #%d: a[%f,%f,%f] *b[%f,%f,%f] c[%f,%f,%f] normal[%f,%f,%f]\n", j, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z, t[i].a->nx, t[i].a->ny, t[i].a->nz);
        k++;
      }
      if (t[i].b->x == t[j].c->x && t[i].b->y == t[j].c->y && t[i].b->z == t[j].c->z) {
	normalv(&t[i].b->nx, &t[i].b->ny, &t[i].b->nz, t[i].b->x, t[i].b->y, t[i].b->z, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z);
//        printf("      #%d: a[%f,%f,%f] b[%f,%f,%f] *c[%f,%f,%f] normal[%f,%f,%f]\n", j, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z, t[i].a->nx, t[i].a->ny, t[i].a->nz);
        k++;
      }
    }

//    printf("    Vertex: c[%f,%f,%f]\n", t[i].c->x, t[i].c->y, t[i].c->z, k);
    k = 0;
    t[i].c->nx = 0; t[i].c->ny = 0; t[i].c->nz = 0;
    for (j = 0; j < c; j++) {
      if (t[i].c->x == t[j].a->x && t[i].c->y == t[j].a->y && t[i].c->z == t[j].a->z) {
        normalv(&t[i].c->nx, &t[i].c->ny, &t[i].c->nz, t[i].c->x, t[i].c->y, t[i].c->z, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z);
//        printf("      #%d: *a[%f,%f,%f] b[%f,%f,%f] c[%f,%f,%f] normal[%f,%f,%f]\n", j, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z, t[i].a->nx, t[i].a->ny, t[i].a->nz);
        k++;
      }
      if (t[i].c->x == t[j].b->x && t[i].c->y == t[j].b->y && t[i].c->z == t[j].b->z) {
        normalv(&t[i].c->nx, &t[i].c->ny, &t[i].c->nz, t[i].c->x, t[i].c->y, t[i].c->z, t[j].c->x, t[j].c->y, t[j].c->z, t[j].a->x, t[j].a->y, t[j].a->z);
//        printf("      #%d: a[%f,%f,%f] *b[%f,%f,%f] c[%f,%f,%f] normal[%f,%f,%f]\n", j, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z, t[i].a->nx, t[i].a->ny, t[i].a->nz);
        k++;
      }
      if (t[i].c->x == t[j].c->x && t[i].c->y == t[j].c->y && t[i].c->z == t[j].c->z) {
        normalv(&t[i].c->nx, &t[i].c->ny, &t[i].c->nz, t[i].c->x, t[i].c->y, t[i].c->z, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z);
//        printf("      #%d: a[%f,%f,%f] b[%f,%f,%f] *c[%f,%f,%f] normal[%f,%f,%f]\n", j, t[j].a->x, t[j].a->y, t[j].a->z, t[j].b->x, t[j].b->y, t[j].b->z, t[j].c->x, t[j].c->y, t[j].c->z, t[i].a->nx, t[i].a->ny, t[i].a->nz);
        k++;
      }
    }
  }

  printf(" Done!\n");
}

/*   /c
    /
  a/_________b
*/

void normalv(float *ox, float *oy, float *oz, float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz) {
  *ox += (by - ay) * (cz - az) - (bz - az) * (cy - ay);
  *oy += (bz - az) * (cx - ax) - (bx - ax) * (cz - az);
  *oz += (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

float xRotateByPoint(float x, float y, float angle, float px, float py) {
  float xTmp, yTmp;

  x = x - px;
  y = y - py;

  xTmp = x * cos(2 * M_PI * angle / 360) - y * sin(2 * M_PI * angle / 360);
  yTmp = x * sin(2 * M_PI * angle / 360) + y * cos(2 * M_PI * angle / 360);

  xTmp = xTmp + px;
  yTmp = yTmp + py;

  return xTmp;
}

float yRotateByPoint(float x, float y, float angle, float px, float py) {
  float xTmp, yTmp;

  x = x - px;
  y = y - py;

  xTmp = x * cos(2 * M_PI * angle / 360) - y * sin(2 * M_PI * angle / 360);
  yTmp = x * sin(2 * M_PI * angle / 360) + y * cos(2 * M_PI * angle / 360);

  xTmp = xTmp + px;
  yTmp = yTmp + py;

  return yTmp;
}
