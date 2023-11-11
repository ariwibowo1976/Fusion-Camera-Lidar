struct rectF {
  double x;
  double y;
  double width;
  double height;
};

struct dimLocRot {
  double h;
  double w;
  double l;
  double x;
  double y;
  double z;
  double rot;
};

struct detected_obstacles
{
    std::vector<rectF> BoundingBoxes{};
    std::vector<dimLocRot> BoundingBoxes3D{};
    std::vector<const char *> ClassCategories;
    std::vector<float> Alpha{};
    std::vector<float> Depths{};
    std::vector<float> Score{};
    std::vector<float> IoUCamLid{};
};

struct tBox {
  string  type;     // object type as car, pedestrian or cyclist,...
  double   x1;      // left corner
  double   y1;      // top corner
  double   x2;      // right corner
  double   y2;      // bottom corner
  double   alpha;   // image orientation
  tBox (string type, double x1,double y1,double x2,double y2,double alpha) :
    type(type),x1(x1),y1(y1),x2(x2),y2(y2),alpha(alpha) {}
};

struct tDetection {
  tBox    box;    // object type, box, orientation
  double  thresh; // detection score
  double  ry;
  double  t1, t2, t3;
  double  h, w, l;
  tDetection ():
    box(tBox("invalid",-1,-1,-1,-1,-10)),thresh(-1000) {}
  tDetection (tBox box,double thresh) :
    box(box),thresh(thresh) {}
  tDetection (string type,double x1,double y1,double x2,double y2,double alpha,double thresh) :
    box(tBox(type,x1,y1,x2,y2,alpha)),thresh(thresh) {}
};

vector<string> CLASS_NAMES;
const int NUM_CLASS = 3;