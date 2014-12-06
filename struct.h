// (c) 2006 Karol Maciaszek <karol.maciaszek@gmail.com>

#define M_LIGHTS 5
#define M_SCENE_PARTS 15
#define B_LCALF_X 0.7
#define B_LCALF_Y 0.1
#define B_LCALF_Z -4
#define B_LELBOW_X 4.3
#define B_LELBOW_Y 0
#define B_LELBOW_Z 5.3
#define B_LFOOT_X 0.7
#define B_LFOOT_Y 0.1
#define B_LFOOT_Z -7.82
#define B_LFOREARM_X 1.4
#define B_LFOREARM_Y 0
#define B_LFOREARM_Z 5.3
#define B_LHAND_X 7.1
#define B_LHAND_Y 0
#define B_LHAND_Z 5.3
#define B_LTHIGH_X 0.7
#define B_LTHIGH_Y 0
#define B_LTHIGH_Z 0.03
#define B_RCALF_X -0.7
#define B_RCALF_Y 0.1
#define B_RCALF_Z -4
#define B_RELBOW_X -4.3
#define B_RELBOW_Y 0
#define B_RELBOW_Z 5.3
#define B_RFOOT_X -0.7
#define B_RFOOT_Y 0.1
#define B_RFOOT_Z -7.82
#define B_RFOREARM_X -1.4
#define B_RFOREARM_Y 0
#define B_RFOREARM_Z 5.3
#define B_RHAND_X -7.1
#define B_RHAND_Y 0
#define B_RHAND_Z 5.3
#define B_RTHIGH_X -0.7
#define B_RTHIGH_Y 0
#define B_RTHIGH_Z 0.03

typedef struct {
  float x, y, z;
  float nx, ny, nz;
  float tx, ty;
} TVertex;

typedef struct {
  float x, y, z, w;
} TVector;

typedef struct {
  TVertex *a;
  TVertex *b;
  TVertex *c;
  int     iTex;
} TTriangle;

typedef struct {
  TVector *v;
  float   angle;
} TRotate;

typedef struct {
  TVertex *p;
  TVector *v;
  float   angle;
} TRotateBy;

typedef struct {
  TVector *v;
} TTranslate;

typedef struct {
  TTriangle  *t;
  int        iT;
  TRotate    *rotateA;
  TRotate    *rotateB;
  TRotate    *rotateC;
  TRotateBy  *rotateByA;
  TRotateBy  *rotateByB;
  TRotateBy  *rotateByC;
  TRotateBy  *rotateByD;
  TTranslate *translateA;
  TTranslate *translateB;
  TTranslate *translateC;
} TPart;

typedef struct {
  TPart *part;
  int   iPart;
} TScene;

typedef struct {
  int   angle;
  float radius;
  float x;
  float y;
  float z;
} TCamera;

typedef struct {
  int     light;
  float   blinkStep;
  int     enabled;
  TVertex *position;
  TVector *diffuse;
  TVector *attenuation;
} TLight;

typedef struct {
  float step;
} TActionJump;

typedef struct {
  float step;
} TActionLCalf;

typedef struct {
  float step;
} TActionLElbow;

typedef struct {
  float step;
} TActionLFoot;

typedef struct {
  float step;
} TActionLForearm;

typedef struct {
  float step;
} TActionLHand;

typedef struct {
  float step;
} TActionLThigh;

typedef struct {
  float step;
} TActionRCalf;

typedef struct {
  float step;
} TActionRElbow;

typedef struct {
  float step;
} TActionRFoot;

typedef struct {
  float step;
} TActionRForearm;

typedef struct {
  float step;
} TActionRHand;

typedef struct {
  float step;
} TActionRThigh;

typedef struct {
  float step;
} TActionSkull;
