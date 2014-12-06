// (c) 2006 Karol Maciaszek <karol.maciaszek@gmail.com>

#define SPEED 0.3

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "load.h"
#include "maths.h"

#include "Data/texParquet.c"
#include "Data/texSkeleton.c"
#include "Data/texSteel.c"
#include "Data/texWarning.c"

TScene   *scene;
TCamera  *camera;
TLight   *light;
TActionJump     *actionJump;
TActionLCalf    *actionLCalf;
TActionLElbow   *actionLElbow;
TActionLFoot    *actionLFoot;
TActionLForearm *actionLForearm;
TActionLHand    *actionLHand;
TActionLThigh   *actionLThigh;
TActionRCalf    *actionRCalf;
TActionRElbow   *actionRElbow;
TActionRFoot    *actionRFoot;
TActionRForearm *actionRForearm;
TActionRHand    *actionRHand;
TActionRThigh   *actionRThigh;
TActionSkull    *actionSkull;

unsigned int tex[10];
int mode;
int cameraAnim;

void timerFunc(int a) {
  if (cameraAnim) camera->angle += 1;
  camera->x = xcircle(camera->radius, camera->angle);
  camera->z = ycircle(camera->radius, camera->angle);

  blinkLight0();
  blinkLight1();
  blinkLight2();
  blinkLight3();
  moveJump();
  moveLCalf();    /*  1 */
  moveLElbow();   /*  2 */
  moveLFoot();    /*  3 */
  moveLForearm(); /*  4 */
  moveLHand();    /*  5 */
  moveLThigh();   /*  6 */
  moveRCalf();    /*  7 */
  moveRElbow();   /*  8 */
  moveRFoot();    /*  9 */
  moveRForearm(); /* 10 */
  moveRHand();    /* 11 */
  moveRThigh();   /* 12 */
  moveSkull();    /* 13 */

  glutTimerFunc(50, timerFunc, 1);
  glutPostRedisplay();
}

void keyEvent(unsigned char c,int x, int y) {
  int i;

  switch (c) {
    case 'a':
      camera->angle += 5;
      camera->x = xcircle(camera->radius, camera->angle);
      camera->z = ycircle(camera->radius, camera->angle);
      break;
    case 'z':
      camera->angle -= 5;
      camera->x = xcircle(camera->radius, camera->angle);
      camera->z = ycircle(camera->radius, camera->angle);
      break;
    case 's':
      camera->radius += 1;
      camera->x = xcircle(camera->radius, camera->angle);
      camera->z = ycircle(camera->radius, camera->angle);
      break;
    case 'x':
      camera->radius -= 1;
      camera->x = xcircle(camera->radius, camera->angle);
      camera->z = ycircle(camera->radius, camera->angle);
      break;
    case 'd':
      camera->y++;
      break;
    case 'c':
      camera->y--;
      break;
    case 'f':
      for (i = 0; i < M_LIGHTS; i++) light[i].position->y = light[i].position->y + 1;
      break;
    case 'v':
      for (i = 0; i < M_LIGHTS; i++) light[i].position->y = light[i].position->y - 1;
      break;
    case '1':
      if (light[0].enabled == 1) {
        light[0].enabled = 0;
      } else {
        light[0].enabled = 1;
      }
      break;
    case '2':
      if (light[1].enabled == 1) {
        light[1].enabled = 0;
      } else {
        light[1].enabled = 1;
      }
      break;
    case '3':
      if (light[2].enabled == 1) {
        light[2].enabled = 0;
      } else {
        light[2].enabled = 1;
      }
      break;
    case '4':
      if (light[3].enabled == 1) {
        light[3].enabled = 0;
      } else {
        light[3].enabled = 1;
      }
      break;
    case '5':
      if (light[4].enabled == 1) {
        light[4].enabled = 0;
      } else {
        light[4].enabled = 1;
      }
      break;
    case 'q':
      switch(mode) {
        case GL_TRIANGLES:
          mode = GL_LINES;
          break;
        case GL_LINES:
          mode = GL_POINTS;
          break;
        case GL_POINTS:
          mode = GL_TRIANGLES;
          break;
      }
      break;
    case 'w':
      switch(cameraAnim) {
        case 0:
          cameraAnim = 1;
          break;
        case 1:
          cameraAnim = 0;
          break;
      }
      break;
  }

  glutPostRedisplay();
}

void displayFrame(void) {
  int i;

  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glClearColor(0, 0, 0, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(camera->x, camera->y, camera->z, 0, 10, 0, 0, 1, 0);
  for (i = 0; i < M_LIGHTS; i++) {
    if (light[i].enabled == 1) {
      glEnable(light[i].light);
    } else {
      glDisable(light[i].light);
    }
  }
  renderLight();

  glEnable(GL_NORMALIZE);
  glEnable(GL_TEXTURE_2D);

  for (i = 0; i < M_SCENE_PARTS; i++) renderPart(&scene->part[i]);

  glutSwapBuffers();
}

void renderPart(TPart *p) {
  int i;
  int iCurrentTex;

  iCurrentTex = -2;

  glPushMatrix();

  glRotated(p->rotateA->angle, p->rotateA->v->x, p->rotateA->v->y, p->rotateA->v->z);
  glTranslated(p->translateA->v->x, p->translateA->v->y, p->translateA->v->z);
  glTranslated(p->translateB->v->x, p->translateB->v->y, p->translateB->v->z);
  glTranslated(p->rotateByA->p->x, p->rotateByA->p->y, p->rotateByA->p->z);
  glRotated(p->rotateByA->angle, p->rotateByA->v->x, p->rotateByA->v->y, p->rotateByA->v->z);
  glTranslated(-1 * p->rotateByA->p->x, -1 * p->rotateByA->p->y, -1 * p->rotateByA->p->z);

  glRotated(p->rotateB->angle, p->rotateB->v->x, p->rotateB->v->y, p->rotateB->v->z);
  glTranslated(p->rotateByB->p->x, p->rotateByB->p->y, p->rotateByB->p->z);
  glRotated(p->rotateByB->angle, p->rotateByB->v->x, p->rotateByB->v->y, p->rotateByB->v->z);
  glTranslated(-1 * p->rotateByB->p->x, -1 * p->rotateByB->p->y, -1 * p->rotateByB->p->z);

  glRotated(p->rotateC->angle, p->rotateC->v->x, p->rotateC->v->y, p->rotateC->v->z);
  glTranslated(p->translateC->v->x, p->translateC->v->y, p->translateC->v->z);
  glTranslated(p->rotateByC->p->x, p->rotateByC->p->y, p->rotateByC->p->z);
  glRotated(p->rotateByC->angle, p->rotateByC->v->x, p->rotateByC->v->y, p->rotateByC->v->z);
  glTranslated(-1 * p->rotateByC->p->x, -1 * p->rotateByC->p->y, -1 * p->rotateByC->p->z);

  glTranslated(p->rotateByD->p->x, p->rotateByD->p->y, p->rotateByD->p->z);
  glRotated(p->rotateByD->angle, p->rotateByD->v->x, p->rotateByD->v->y, p->rotateByD->v->z);
  glTranslated(-1 * p->rotateByD->p->x, -1 * p->rotateByD->p->y, -1 * p->rotateByD->p->z);

  glBegin(mode);

  for (i = 0; i < p->iT; i++) {
    if (iCurrentTex == p->t[i].iTex) {
      renderTriangle(&p->t[i]);
    } else {
      iCurrentTex = p->t[i].iTex;
      glEnd();
      glBindTexture(GL_TEXTURE_2D, tex[p->t[i].iTex]);
      glBegin(mode);
      if (mode == GL_TRIANGLES) renderTriangle(&p->t[i]);
      if (mode == GL_LINES) renderLines(&p->t[i]);
      if (mode == GL_POINTS) renderPoints(&p->t[i]);
    }
  }

  glEnd();
  glPopMatrix();
}

void renderTriangle(TTriangle *t) {
  glTexCoord2f(t->a->tx, t->a->ty);
  glNormal3f(t->a->nx, t->a->ny, t->a->nz);
  glVertex3f(t->a->x,  t->a->y,  t->a->z);
  glTexCoord2f(t->b->tx, t->b->ty);
  glNormal3f(t->b->nx, t->b->ny, t->b->nz);
  glVertex3f(t->b->x,  t->b->y,  t->b->z);
  glTexCoord2f(t->c->tx, t->c->ty);
  glNormal3f(t->c->nx, t->c->ny, t->c->nz);
  glVertex3f(t->c->x,  t->c->y,  t->c->z);
}

void renderLines(TTriangle *t) {
  glVertex3f(t->a->x,  t->a->y,  t->a->z);
  glVertex3f(t->b->x,  t->b->y,  t->b->z);
  glVertex3f(t->a->x,  t->a->y,  t->a->z);
  glVertex3f(t->c->x,  t->c->y,  t->c->z);
  glVertex3f(t->b->x,  t->b->y,  t->b->z);
  glVertex3f(t->c->x,  t->c->y,  t->c->z);
}

void renderPoints(TTriangle *t) {
  glVertex3f(t->a->x,  t->a->y,  t->a->z);
  glVertex3f(t->b->x,  t->b->y,  t->b->z);
  glVertex3f(t->c->x,  t->c->y,  t->c->z);
}

void renderLight() {
  int i;
  float position[4];
  float diffuse[4];

  for (i = 0; i < M_LIGHTS; i++) {
    position[0] = light[i].position->x;
    position[1] = light[i].position->y;
    position[2] = light[i].position->z;
    position[3] = 1;
    diffuse[0] = light[i].diffuse->x;
    diffuse[1] = light[i].diffuse->y;
    diffuse[2] = light[i].diffuse->z;
    diffuse[3] = 0;
    glLightfv(light[i].light, GL_POSITION, position);
    glLightfv(light[i].light, GL_DIFFUSE, diffuse);
    glLightf(light[i].light, GL_CONSTANT_ATTENUATION, light[i].attenuation->x);
    glLightf(light[i].light, GL_LINEAR_ATTENUATION, light[i].attenuation->y);
    glLightf(light[i].light, GL_QUADRATIC_ATTENUATION, light[i].attenuation->z);
  }
}

int main(int argc, char* argv[])
{
  float ambient[]={1,1,1,1};
  float emission[]={1,1,1,1};
  float diffuse[]={0.7,0.7,0.7,1};
  float specular[]={0.5,0.5,0.5,1};
  int i;

  // initialization of structures
  scene = (TScene *)malloc(sizeof(TScene));
  loadScene(scene);
  camera   = (TCamera   *)malloc(sizeof(TCamera  ));
  camera->angle = 0;
  camera->radius = 30;
  camera->x = camera->radius;
  camera->y = 15;
  camera->z = 0;
  light = (TLight *)malloc(M_LIGHTS * sizeof(TLight));
  light[0].position = (TVertex *)malloc(sizeof(TVertex));
  light[0].diffuse = (TVector *)malloc(sizeof(TVector));
  light[0].attenuation = (TVector *)malloc(sizeof(TVector));
  light[0].light = GL_LIGHT0;
  light[0].enabled = 1;
  light[0].blinkStep = 0;
  light[0].position->x = 20; light[0].position->y = 5; light[0].position->z = 20;
  light[0].diffuse->x = 1; light[0].diffuse->y = 1; light[0].diffuse->z = 1;
  light[0].attenuation->x = 0; light[0].attenuation->y = 0.001; light[0].attenuation->z = 0.001;
  light[1].position = (TVertex *)malloc(sizeof(TVertex));
  light[1].diffuse = (TVector *)malloc(sizeof(TVector));
  light[1].attenuation = (TVector *)malloc(sizeof(TVector));
  light[1].light = GL_LIGHT1;
  light[1].enabled = 1;
  light[1].blinkStep = 0;
  light[1].position->x = -20; light[1].position->y = 5; light[1].position->z = -20;
  light[1].diffuse->x = 1; light[1].diffuse->y = 0; light[1].diffuse->z = 0;
  light[1].attenuation->x = 0; light[1].attenuation->y = 0.001; light[1].attenuation->z = 0.001;
  light[2].position = (TVertex *)malloc(sizeof(TVertex));
  light[2].diffuse = (TVector *)malloc(sizeof(TVector));
  light[2].attenuation = (TVector *)malloc(sizeof(TVector));
  light[2].light = GL_LIGHT2;
  light[2].enabled = 1;
  light[2].blinkStep = 0;
  light[2].position->x = 20; light[2].position->y = 5; light[2].position->z = -20;
  light[2].diffuse->x = 0; light[2].diffuse->y = 1; light[2].diffuse->z = 0;
  light[2].attenuation->x = 0; light[2].attenuation->y = 0.001; light[2].attenuation->z = 0.001;
  light[3].position = (TVertex *)malloc(sizeof(TVertex));
  light[3].diffuse = (TVector *)malloc(sizeof(TVector));
  light[3].attenuation = (TVector *)malloc(sizeof(TVector));
  light[3].light = GL_LIGHT3;
  light[3].enabled = 1;
  light[3].blinkStep = 0;
  light[3].position->x = -20; light[3].position->y = 5; light[3].position->z = 20;
  light[3].diffuse->x = 0; light[3].diffuse->y = 0; light[3].diffuse->z = 1;
  light[3].attenuation->x = 0; light[3].attenuation->y = 0.001; light[3].attenuation->z = 0.001;
  light[4].position = (TVertex *)malloc(sizeof(TVertex));
  light[4].diffuse = (TVector *)malloc(sizeof(TVector));
  light[4].attenuation = (TVector *)malloc(sizeof(TVector));
  light[4].light = GL_LIGHT4;
  light[4].enabled = 0;
  light[4].blinkStep = 0;
  light[4].position->x = 20; light[4].position->y = 5; light[4].position->z = 20;
  light[4].diffuse->x = 1; light[4].diffuse->y = 1; light[4].diffuse->z = 1;
  light[4].attenuation->x = 1; light[4].attenuation->y = 0; light[4].attenuation->z = 0;
  mode = GL_TRIANGLES;
  cameraAnim = 1;

  actionJump = (TActionJump *)malloc(sizeof(TActionJump)); actionJump->step = 0;
  actionLCalf = (TActionLCalf *)malloc(sizeof(TActionLCalf)); actionLCalf->step = 0;
  actionLElbow = (TActionLElbow *)malloc(sizeof(TActionLElbow)); actionLElbow->step = 0;
  actionLFoot = (TActionLFoot *)malloc(sizeof(TActionLFoot)); actionLFoot->step = 0;
  actionLForearm = (TActionLForearm *)malloc(sizeof(TActionLForearm)); actionLForearm->step = 0;
  actionLHand = (TActionLHand *)malloc(sizeof(TActionLHand)); actionLHand->step = 0;
  actionLThigh = (TActionLThigh *)malloc(sizeof(TActionLThigh)); actionLThigh->step = 0;
  actionRCalf = (TActionRCalf *)malloc(sizeof(TActionRCalf)); actionRCalf->step = 0;
  actionRElbow = (TActionRElbow *)malloc(sizeof(TActionRElbow)); actionRElbow->step = 0;
  actionRFoot = (TActionRFoot *)malloc(sizeof(TActionRFoot)); actionRFoot->step = 0;
  actionRForearm = (TActionRForearm *)malloc(sizeof(TActionRForearm)); actionRForearm->step = 0;
  actionRHand = (TActionRHand *)malloc(sizeof(TActionRHand)); actionRHand->step = 0;
  actionRThigh = (TActionRThigh *)malloc(sizeof(TActionRThigh)); actionRThigh->step = 0;
  actionSkull = (TActionSkull *)malloc(sizeof(TActionSkull)); actionSkull->step = 0;

  // creating window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Danse Macabre (c) Karol Maciaszek <karol.maciaszek@gmail.com>");

  // binding functions
  glutDisplayFunc(displayFrame);
  glutKeyboardFunc(keyEvent);
  glutTimerFunc(30, timerFunc, 1);

  // setting up scene
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(55,4/3,1,150);
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);

  // loading textures
  glGenTextures(10, tex);
  glBindTexture(GL_TEXTURE_2D, tex[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texParquet.width, texParquet.height, 0, GL_RGB,GL_UNSIGNED_BYTE,&texParquet.pixel_data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, tex[1]);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texWarning.width, texWarning.height, 0, GL_RGB,GL_UNSIGNED_BYTE,&texWarning.pixel_data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, tex[2]);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texSkeleton.width, texSkeleton.height, 0, GL_RGB,GL_UNSIGNED_BYTE,&texSkeleton.pixel_data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, tex[3]);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texSteel.width, texSteel.height, 0, GL_RGB,GL_UNSIGNED_BYTE,&texSteel.pixel_data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);

//  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
//  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emission);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
//  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
//  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,10);

  glutMainLoop();
  return 0;
}

void blinkLight0() {
  light[0].blinkStep += 4 * SPEED;
  light[0].attenuation->y = 1.000000 + sin(light[0].blinkStep) * sin(light[0].blinkStep) * sin(light[0].blinkStep);
}

void blinkLight1() {
  light[1].blinkStep += SPEED;
  light[1].attenuation->y = 1.000001 + sin(light[1].blinkStep);
}

void blinkLight2() {
  light[2].blinkStep += SPEED;
  light[2].attenuation->y = 1.000001 + cos(light[2].blinkStep);
}

void blinkLight3() {
  light[3].blinkStep += SPEED / 2;
  light[3].attenuation->y = 1.000001 + sin(light[3].blinkStep);
}

void moveJump() {
  actionJump->step += SPEED;
  setTranslate(scene->part[0].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[1].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[2].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[3].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[4].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[5].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[6].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[7].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[8].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[9].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[10].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[11].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[12].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
  setTranslate(scene->part[13].translateB, 0, 0, 1.5 + sin(actionJump->step) * 3);
}

void moveSkull() {
  actionSkull->step += SPEED * 1.5;
  setRotateBy(scene->part[13].rotateByA, sin(actionSkull->step) * 15, 0, 0, 7.5, 1, 0, 0);
}

void moveLCalf() {
  actionLCalf->step += SPEED;

  setRotateBy(
    scene->part[1].rotateByA, 
    -20 + sin(actionLThigh->step + 0.1 - 0.2) * 20, 
    B_LTHIGH_X, 
    B_LTHIGH_Y, 
    B_LTHIGH_Z, 
    1, 0, 0);

  setRotateBy(scene->part[1].rotateByB, 
    40 + sin(actionLCalf->step) * -40, 
    B_LCALF_X, 
    B_LCALF_Y, 
    B_LCALF_Z, 
    1, 0 ,0);
}

void moveLElbow() {
  actionLElbow->step += SPEED;

  setRotateBy(
    scene->part[2].rotateByA, 
    -50 + sin(actionLForearm->step + 0.3) * 40, 
    B_LFOREARM_X, 
    B_LFOREARM_Y, 
    B_LFOREARM_Z, 
    0, 1, 0);

  setRotateBy(scene->part[2].rotateByB, 
    cos(actionLElbow->step) * 30, 
    B_LELBOW_X, 
    B_LELBOW_Y, 
    B_LELBOW_Z, 
    0, 1 ,0);
}

void moveLFoot() {
  actionLFoot->step += SPEED;

  setRotateBy(
    scene->part[3].rotateByA, 
    -20 + sin(actionLThigh->step + 0.1 - 0.4) * 20, 
    B_LTHIGH_X, 
    B_LTHIGH_Y, 
    B_LTHIGH_Z, 
    1, 0, 0);

  setRotateBy(scene->part[3].rotateByB, 
    40 + sin(actionLCalf->step) * -40, 
    B_LCALF_X, 
    B_LCALF_Y, 
    B_LCALF_Z, 
    1, 0 ,0);

  setRotateBy(scene->part[3].rotateByC, 
    -20 + sin(actionLCalf->step) * 50, 
    B_LFOOT_X, 
    B_LFOOT_Y, 
    B_LFOOT_Z, 
    1, 0 ,0);
}

void moveLForearm() {
  actionLForearm->step += SPEED;
  setRotateBy(scene->part[4].rotateByA, -50 + sin(actionLForearm->step) * 40, B_LFOREARM_X, B_LFOREARM_Y, B_LFOREARM_Z, 0, 1, 0);
}

void moveLHand() {
  actionLHand->step += SPEED;
  setRotateBy(scene->part[5].rotateByA, -50 + sin(actionLForearm->step) * 40, B_LFOREARM_X, B_LFOREARM_Y, B_LFOREARM_Z, 0, 1, 0);
  setRotateBy(scene->part[5].rotateByB, cos(actionLElbow->step) * 30, B_LELBOW_X, B_LELBOW_Y, B_LELBOW_Z, 0, 1, 0);
  setRotateBy(scene->part[5].rotateByC, sin(actionLHand->step) * 40, B_LHAND_X, B_LHAND_Y, B_LHAND_Z, 0, 1, 0);
}

void moveLThigh() {
  actionLThigh->step += SPEED;
  setRotateBy(scene->part[6].rotateByA, -20 + sin(actionLThigh->step - 0.4) * 20, B_LTHIGH_X, B_LTHIGH_Y, B_LTHIGH_Z, 1, 0, 0);
}

void moveRCalf() {
  actionRCalf->step += SPEED;

  setRotateBy(
    scene->part[7].rotateByA, 
    -20 + sin(actionRThigh->step + 0.1) * 20, 
    B_RTHIGH_X, 
    B_RTHIGH_Y, 
    B_RTHIGH_Z, 
    1, 0, 0);

  setRotateBy(scene->part[7].rotateByB, 
    40 + sin(actionRCalf->step) * -40, 
    B_RCALF_X, 
    B_RCALF_Y, 
    B_RCALF_Z, 
    1, 0 ,0);
}

void moveRElbow() {
  actionRElbow->step += SPEED;
  setRotateBy(scene->part[8].rotateByA, 50 + sin(actionRForearm->step + 0.3) * -40, B_RFOREARM_X, B_RFOREARM_Y, B_RFOREARM_Z, 0, 1, 0);
  setRotateBy(scene->part[8].rotateByB, cos(actionRElbow->step) * -30, B_RELBOW_X, B_RELBOW_Y, B_RELBOW_Z, 0, 1, 0);
}

void moveRFoot() {
  actionRFoot->step += SPEED;

  setRotateBy(
    scene->part[9].rotateByA, 
    -20 + sin(actionRThigh->step + 0.1) * 20, 
    B_RTHIGH_X, 
    B_RTHIGH_Y, 
    B_RTHIGH_Z, 
    1, 0, 0);

  setRotateBy(scene->part[9].rotateByB, 
    40 + sin(actionRCalf->step) * -40, 
    B_RCALF_X, 
    B_RCALF_Y, 
    B_RCALF_Z, 
    1, 0 ,0);

  setRotateBy(scene->part[9].rotateByC, 
    -20 + cos(actionRCalf->step) * 50, 
    B_RFOOT_X, 
    B_RFOOT_Y, 
    B_RFOOT_Z, 
    1, 0 ,0);
}

void moveRForearm() {
  actionRForearm->step += SPEED;
  setRotateBy(scene->part[10].rotateByA, 50 + sin(actionRForearm->step) * -40, B_RFOREARM_X, B_RFOREARM_Y, B_RFOREARM_Z, 0, 1, 0);
}

void moveRHand() {
  actionRHand->step += SPEED;
  setRotateBy(scene->part[11].rotateByA, 50 + sin(actionRForearm->step) * -40, B_RFOREARM_X, B_RFOREARM_Y, B_RFOREARM_Z, 0, 1, 0);
  setRotateBy(scene->part[11].rotateByB, cos(actionRElbow->step) * -30, B_RELBOW_X, B_RELBOW_Y, B_RELBOW_Z, 0, 1, 0);
  setRotateBy(scene->part[11].rotateByC, sin(actionRHand->step) * -40, B_RHAND_X, B_RELBOW_Y, B_RHAND_Z, 0, 1, 0);
}

void moveRThigh() {
  actionRThigh->step += SPEED;
  setRotateBy(scene->part[12].rotateByA, -20 + sin(actionRThigh->step) * 20, B_RTHIGH_X, B_RTHIGH_Y, B_RTHIGH_Z, 1, 0, 0);
}
