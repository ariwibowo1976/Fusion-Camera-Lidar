struct MFStructValue {
    // CAM / LIDAR / IOU
    std::vector<double> low_a{};
    std::vector<double> low_b{};
    std::vector<double> medium_a1{};
    std::vector<double> medium_b1{};
    std::vector<double> medium_a2{};
    std::vector<double> medium_b2{};
    std::vector<double> high_a{};
    std::vector<double> high_b{};
};


struct membershipFunction {
    std::vector<double> low{};
    std::vector<double> medium{};
    std::vector<double> medium2{};
    std::vector<double> high{};
};

double max(double &a, double &b, double &c){
    if(a > b){
        if(a > c){
            return a;
        }else{
            return c;
        }
    }else{
        if(b > c){
            return b;
        }else{
            return c;
        }
    }
}

double min(double &a, double &b, double &c){
    if(a < b){
        if(a < c){
            return a;
        }else{
            return c;
        }
    }else{
        if(b < c){
            return b;
        }else{
            return c;
        }
    }
}