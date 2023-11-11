// initialize class names
void initGlobals () {
  CLASS_NAMES.push_back("Car");
  // CLASS_NAMES.push_back("pedestrian");
  // CLASS_NAMES.push_back("cyclist");
}
vector<int32_t> indices;

vector<tDetection> loadDetections(string file_name, bool &compute_aos,
        vector<bool> &eval_image, vector<bool> &eval_ground,
        vector<bool> &eval_3d) {

  // holds all detections (ignored detections are indicated by an index vector
  vector<tDetection> detections;
  FILE *fp = fopen(file_name.c_str(),"r");
  std::cout << "fp : " << file_name << std::endl;
  if (!fp) {
    return detections;
  }
  while (!feof(fp)) {
    tDetection d;
    double trash;
    char str[255];
    if (fscanf(fp, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
                   str, &trash, &trash, &d.box.alpha, &d.box.x1, &d.box.y1,
                   &d.box.x2, &d.box.y2, &d.h, &d.w, &d.l, &d.t1, &d.t2, &d.t3,
                   &d.ry, &d.thresh)==16) {

        // d.thresh = 1;
      d.box.type = str;
      detections.push_back(d);

      // orientation=-10 is invalid, AOS is not evaluated if at least one orientation is invalid
      if(d.box.alpha == -10)
        compute_aos = false;

      // a class is only evaluated if it is detected at least once
      for (int c = 0; c < NUM_CLASS; c++) {
        if (!strcasecmp(d.box.type.c_str(), CLASS_NAMES[c].c_str())) {
          if (!eval_image[c] && d.box.x1 >= 0){
            // std::cout << "d.box.x1 : " << d.box.x1 << std::endl;
            eval_image[c] = true;
          };
            
          if (!eval_ground[c] && d.t1 != -1000 && d.t3 != -1000 && d.w > 0 && d.l > 0)
            eval_ground[c] = true;
          if (!eval_3d[c] && d.t1 != -1000 && d.t2 != -1000 && d.t3 != -1000 && d.h > 0 && d.w > 0 && d.l > 0)
            eval_3d[c] = true;
          break;
        }
      }
    }
  }
  fclose(fp);
  return detections;
}

vector<int32_t> getEvalIndices(const string& lid_dir) {

    DIR* dir;
    dirent* entity;
    dir = opendir(lid_dir.c_str());
    if (dir) {
        while (entity = readdir(dir)) {
            string path(entity->d_name);
            int32_t len = path.size();
            if (len < 10) continue;
            int32_t index = atoi(path.substr(len - 10, 10).c_str());
            indices.push_back(index);
        }
    }
    return indices;
}

bool loadtxt(string cam_dir, string lid_dir, vector<vector<tDetection>> &camdetections, vector<vector<tDetection>> &liddetections,std::vector<int32_t> &indices){

  // set some global parameters
  initGlobals();
  // holds wether orientation similarity shall be computed (might be set to false while loading detections)
  // and which labels where provided by this submission
  bool compute_aos=true;
  bool compute_aos_ground=false;
  vector<bool> eval_image(NUM_CLASS, false);
  vector<bool> eval_ground(NUM_CLASS, false);
  vector<bool> eval_3d(NUM_CLASS, false);

  indices = getEvalIndices(lid_dir);
  std::cout << "indices : " << indices.size() << std::endl;
  std::cout << "============================== " << std::endl;
  for (int32_t i = 0; i < indices.size(); i++) {
    // file name
    std::cout << "n : " << i << std::endl;
    char file_name[256];
    sprintf(file_name,"%06d.txt",indices.at(i));
    // std::cout << "file_name : " << file_name << std::endl;
    vector<tDetection> cam = loadDetections(cam_dir + file_name,
            compute_aos, eval_image, eval_ground, eval_3d);
    vector<tDetection> lid = loadDetections(lid_dir + file_name,
            compute_aos, eval_image, eval_ground, eval_3d);
    camdetections.push_back(cam);
    liddetections.push_back(lid);
    std::cout << "cam size   : " << cam.size() << std::endl;
    std::cout << "lidar size : " << lid.size() << std::endl;
    std::cout << "============================== " << std::endl;
  }

  return true;
}
