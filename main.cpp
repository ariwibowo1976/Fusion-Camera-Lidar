#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
#include <numeric>
#include <cstring>
#include <cassert>
#include <fstream>
#include <dirent.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>

BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > Polygon;
using namespace std;

#define COMPILE_FUZZYFUSION
// #define COMPILE_2D

#include "main.h"
#include "fuzzyfusion.h"

#include "fuzzyFusion.cpp"
#include "load_kitti.cpp"
#include "fusion.cpp"

int32_t main2(int32_t argc,char *argv[]) {
    // we need 2 or 4 arguments!
    if (argc!=3) {
        cout << "Usage: ./load_kitti cam_dir lid_dir" << endl;
        return 1;
    }
    fuzzyFusion();
    return 0;
};

int32_t main(int32_t argc,char *argv[]) {
    membershipFunction outputFuzzy;
    MFStructValue MFunction;

#ifdef COMPILE_FUZZYFUSION
    {
        std::cout << "======= INIT FUZZY ======= " << std::endl;
        initFuzzy(MFunction,outputFuzzy);
    }
#endif
    // we need 2 or 4 arguments!
    if (argc!=3) {
        cout << "Usage: ./load_kitti cam_dir lid_dir" << endl;
        return 1;
    }
    // read arguments
    string cam_dir = argv[1];
    string lid_dir = argv[2];
        
    // /media/ssd1T/dataset/kitti_training/training
    // run evaluation
    
    vector<vector<tDetection>> camdetections;
    vector<vector<tDetection>> liddetections;
    std::vector<int32_t> indices;
    //laod TXT
    {
        //KITTI DATA LOADER 
        loadtxt(cam_dir, lid_dir,camdetections,liddetections,indices);
    }
    {
        // std::cout << " " << std::endl;  
        std::cout << "CamDetection   : " << camdetections.size() << std::endl;  
        // std::cout << "LidarDetection : " << liddetections.size() << std::endl;
        // std::cout << " " << std::endl; 

        // std::cout << liddetections[0][0].box.alpha << std::endl;
        // std::cout << liddetections[0][0].h << " " << liddetections[0][0].w << " " << liddetections[0][0].l << std::endl;
        // std::cout << liddetections[0][0].t1 << " " << liddetections[0][0].t2 << " " << liddetections[0][0].t3 << std::endl;
        // std::cout << liddetections[0][0].ry << std::endl; 
    }

    {
        processFusion(camdetections,liddetections,indices,MFunction,outputFuzzy);
    }

    return 0;
}
