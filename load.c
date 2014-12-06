// (c) 2006 Karol Maciaszek <karol.maciaszek@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "struct.h"
#include "maths.h"
#include "load.h"

void loadScene(TScene *s) {
  s->part = (TPart *)malloc(M_SCENE_PARTS * sizeof(TPart));
  s->iPart = M_SCENE_PARTS;

  printf("Loading scene...\n");
  loadPart("Data/skeleton_corpse.raw",   &s->part[0]);
  setRotate(s->part[0].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[0].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_lcalf.raw",    &s->part[1]);
  setRotate(s->part[1].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[1].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_lelbow.raw",   &s->part[2]);
  setRotateBy(s->part[2].rotateByD, -20, B_LFOREARM_X, B_LFOREARM_Y, B_LFOREARM_Z, 0, 0, 1);
  setRotate(s->part[2].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[2].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_lfoot.raw",    &s->part[3]);
  setRotate(s->part[3].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[3].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_lforearm.raw", &s->part[4]);
  setRotateBy(s->part[4].rotateByD, -20, B_LFOREARM_X, B_LFOREARM_Y, B_LFOREARM_Z, 0, 0, 1);
  setRotate(s->part[4].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[4].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_lhand.raw",    &s->part[5]);
  setRotateBy(s->part[5].rotateByD, -20, B_LFOREARM_X, B_LFOREARM_Y, B_LFOREARM_Z, 0, 0, 1);
  setRotate(s->part[5].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[5].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_lthigh.raw",   &s->part[6]);
  setRotate(s->part[6].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[6].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_rcalf.raw",    &s->part[7]);
  setRotate(s->part[7].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[7].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_relbow.raw",   &s->part[8]);
  setRotateBy(s->part[8].rotateByD, 20, B_RFOREARM_X, B_RFOREARM_Y, B_RFOREARM_Z, 0, 0, 1);
  setRotate(s->part[8].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[8].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_rfoot.raw",    &s->part[9]);
  setRotate(s->part[9].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[9].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_rforearm.raw", &s->part[10]);
  setRotateBy(s->part[10].rotateByD, 20, B_RFOREARM_X, B_RFOREARM_Y, B_RFOREARM_Z, 0, 0, 1);
  setRotate(s->part[10].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[10].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_rhand.raw",    &s->part[11]);
  setRotateBy(s->part[11].rotateByD, 20, B_RFOREARM_X, B_RFOREARM_Y, B_RFOREARM_Z, 0, 0, 1);
  setRotate(s->part[11].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[11].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_rthigh.raw",   &s->part[12]);
  setRotate(s->part[12].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[12].translateA, 0, 0, 8.52);

  loadPart("Data/skeleton_skull.raw",    &s->part[13]);
  setRotate(s->part[13].rotateA, -90, 1, 0, 0);
  setTranslate(s->part[13].translateA, 0, 0, 8.52);

  loadPart("Data/parquet_parquet.raw",   &s->part[14]);

  printf("Done!\n");
}

void loadPart(char *sFilename, TPart *p) {
  FILE *pFile;
  char cLineBuf[1024];
  int i;

  printf("  Loading %s... ", sFilename);
  pFile = fopen(sFilename, "r");
  i = 0;

  while (fgets(cLineBuf, 1024, pFile)) i++;
  p->t = (TTriangle *)malloc(i * sizeof(TTriangle));
  p->iT = i;
  rewind(pFile);

  i = 0;
  while (fgets(cLineBuf, 1024, pFile)) {
    p->t[i].a = (TVertex *)malloc(sizeof(TVertex));
    p->t[i].b = (TVertex *)malloc(sizeof(TVertex));
    p->t[i].c = (TVertex *)malloc(sizeof(TVertex));

    p->t[i].iTex = -1;
    sscanf(cLineBuf, "%f %f %f %f %f %f %f %f %f (%f %f %f %f %f %f #%d)", 
      &p->t[i].a->x, &p->t[i].a->y, &p->t[i].a->z, 
      &p->t[i].b->x, &p->t[i].b->y, &p->t[i].b->z, 
      &p->t[i].c->x, &p->t[i].c->y, &p->t[i].c->z, 
      &p->t[i].a->tx, &p->t[i].a->ty, 
      &p->t[i].b->tx, &p->t[i].b->ty, 
      &p->t[i].c->tx, &p->t[i].c->ty, 
      &p->t[i].iTex);

    i++;
  }

  printf("%d triangles.\n", i);

  calculateNormals(p->t, p->iT);

  p->rotateA = (TRotate *)malloc(sizeof(TRotate));
  p->rotateA->v = (TVector *)malloc(sizeof(TVector));
  setRotate(p->rotateA, 0, 0, 0, 0);

  p->rotateB = (TRotate *)malloc(sizeof(TRotate));
  p->rotateB->v = (TVector *)malloc(sizeof(TVector));
  setRotate(p->rotateB, 0, 0, 0, 0);

  p->rotateC = (TRotate *)malloc(sizeof(TRotate));
  p->rotateC->v = (TVector *)malloc(sizeof(TVector));
  setRotate(p->rotateC, 0, 0, 0, 0);

  p->rotateByA = (TRotateBy *)malloc(sizeof(TRotateBy));
  p->rotateByA->p = (TVertex *)malloc(sizeof(TVertex));
  p->rotateByA->v = (TVector *)malloc(sizeof(TVector));
  setRotateBy(p->rotateByA, 0, 0, 0, 0, 0, 0, 0);

  p->rotateByB = (TRotateBy *)malloc(sizeof(TRotateBy));
  p->rotateByB->p = (TVertex *)malloc(sizeof(TVertex));
  p->rotateByB->v = (TVector *)malloc(sizeof(TVector));
  setRotateBy(p->rotateByB, 0, 0, 0, 0, 0, 0, 0);

  p->rotateByC = (TRotateBy *)malloc(sizeof(TRotateBy));
  p->rotateByC->p = (TVertex *)malloc(sizeof(TVertex));
  p->rotateByC->v = (TVector *)malloc(sizeof(TVector));
  setRotateBy(p->rotateByC, 0, 0, 0, 0, 0, 0, 0);

  p->rotateByD = (TRotateBy *)malloc(sizeof(TRotateBy));
  p->rotateByD->p = (TVertex *)malloc(sizeof(TVertex));
  p->rotateByD->v = (TVector *)malloc(sizeof(TVector));
  setRotateBy(p->rotateByD, 0, 0, 0, 0, 0, 0, 0);

  p->translateA = (TTranslate *)malloc(sizeof(TTranslate));
  p->translateA->v = (TVector *)malloc(sizeof(TVector));
  setTranslate(p->translateA, 0, 0, 0);

  p->translateB = (TTranslate *)malloc(sizeof(TTranslate));
  p->translateB->v = (TVector *)malloc(sizeof(TVector));
  setTranslate(p->translateB, 0, 0, 0);

  p->translateC = (TTranslate *)malloc(sizeof(TTranslate));
  p->translateC->v = (TVector *)malloc(sizeof(TVector));
  setTranslate(p->translateC, 0, 0, 0);

  fclose(pFile);
}

void setRotate(TRotate *r, float angle, float x, float y, float z) {
  r->v->x = x;
  r->v->y = y;
  r->v->z = z;
  r->angle = angle;
}

void setRotateBy(TRotateBy *r, float angle, float px, float py, float pz, float vx, float vy, float vz) {
  r->p->x = px;
  r->p->y = py;
  r->p->z = pz;
  r->v->x = vx;
  r->v->y = vy;
  r->v->z = vz;
  r->angle = angle;
}

void setRotateByAs(TRotateBy *r, TRotateBy *as) {
  r->p->x = as->p->x;
  r->p->y = as->p->y;
  r->p->z = as->p->z;
  r->v->x = as->v->x;
  r->v->y = as->v->y;
  r->v->z = as->v->z;
  r->angle = as->angle;
}

void setTranslate(TTranslate *t, float x, float y, float z) {
  t->v->x = x;
  t->v->y = y;
  t->v->z = z;
}
