// (c) 2006 Karol Maciaszek <karol.maciaszek@gmail.com>

float xcircle(float radius, int angle);
float ycircle(float radius, int angle);
void calculateNormals(TTriangle *t, int c);
void normalv(float *ox, float *oy, float *oz, float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz);
float xRotateByPoint(float x, float y, float angle, float px, float py);
float yRotateByPoint(float x, float y, float angle, float px, float py);
