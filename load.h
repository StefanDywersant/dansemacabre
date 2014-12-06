// (c) 2006 Karol Maciaszek <karol.maciaszek@gmail.com>

void loadScene(TScene *s);
void loadPart(char *sFilename, TPart *t);
void setRotate(TRotate *r, float angle, float x, float y, float z);
void setRotateBy(TRotateBy *r, float angle, float px, float py, float pz, float vx, float vy, float vz);
void setRotateByAs(TRotateBy *r, TRotateBy *as);
void setTranslate(TTranslate *t, float x, float y, float z);
