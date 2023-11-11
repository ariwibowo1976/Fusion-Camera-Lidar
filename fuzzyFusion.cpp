void defuzzification(membershipFunction &outputFuzzy,membershipFunction &outputDefuzzification, MFStructValue &MFunction, std::vector<double> &crispOutput){
    double tmp = 0.0;
    for (int i = 0; i < 2; ++i){
        tmp = 0.0;
        //LOW Descending Graphics
        //   .\    
        //   . \
        //   .  \
        // u ....\
        //   .  . \  
        //   b  x a
        // x = a - (u * (a - b))
        if(outputFuzzy.low[i]>0){
            outputDefuzzification.low.push_back(MFunction.low_a[3] - (outputFuzzy.low[i] * (MFunction.low_a[3] - MFunction.low_b[3])));
        }else{
            outputDefuzzification.low.push_back(0.0);
        }
        //MED Ascending Graphics    //MED Descending Graphics
        //        /.                //   .\  
        //       / .                //   . \
        //      /  .                //   .  \
        // u ../.  .                // u ....\
        //    / .  .                //   .  . \  
        //   b1 x  a1               //  b2  x a2
        // x = (u*(a1-b1)) + b1     // x = a2 - (u * (a2 - b2))
       if(outputFuzzy.medium[i]>0){
            outputDefuzzification.medium.push_back((outputFuzzy.medium[i]*(MFunction.medium_a1[3] - MFunction.medium_b1[3])) + MFunction.medium_b1[3]);
            outputDefuzzification.medium2.push_back(MFunction.medium_a2[3] - (outputFuzzy.medium[i] * (MFunction.medium_a2[3] - MFunction.medium_b2[3])));
        }else{
            outputDefuzzification.medium.push_back(0.0);
            outputDefuzzification.medium2.push_back(0.0);
        }
        //HIGH Ascending Graphics    
        //        /.                
        //       / .                
        //      /  .            
        // u ../.  .           
        //    / .  .              
        //   b  x  a            
        // x = (u*(a-b)) + b
        if(outputFuzzy.high[i]>0){
            outputDefuzzification.high.push_back((outputFuzzy.high[i]*(MFunction.high_a[3] - MFunction.high_b[3])) + MFunction.high_b[3]);
        }else{
            outputDefuzzification.high.push_back(0.0);
        }

        tmp = outputFuzzy.low[i] + outputFuzzy.medium[i] + outputFuzzy.medium[i] + outputFuzzy.high[i];
        // std::cout << "SUM : " << outputFuzzy.low[i] << std::endl;
        if(tmp > 0){
            double out = ((outputFuzzy.low[i] * outputDefuzzification.low[i]) +
                (outputFuzzy.medium[i] * outputDefuzzification.medium[i]) +
                (outputFuzzy.medium[i] * outputDefuzzification.medium2[i]) +
                (outputFuzzy.high[i] * outputDefuzzification.high[i]))/tmp;
                std::cout << "OUT " << i << " : " << out << std::endl;
            crispOutput.push_back(out);
        }else{
            crispOutput.push_back(0.0);    
        }
    }
};

void fuzzyInference(membershipFunction &MFValue, membershipFunction &outputFuzzy){
    double tmp = 0.0;
    // std::cout << MFValue.low[0] << " " << MFValue.low[1] << " " << MFValue.low[2] << std::endl;
    outputFuzzy.low[0] = 0.0;
    outputFuzzy.medium[0] = 0.0;
    outputFuzzy.high[0] = 0.0;
    outputFuzzy.low[1] = 0.0;
    outputFuzzy.medium[1] = 0.0;
    outputFuzzy.high[1] = 0.0;


    if(MFValue.low[0] > 0.0 && MFValue.low[1] > 0.0 && MFValue.low[2] > 0.0){
        std::cout << "LOW LOW LOW : LOW LOW" << std::endl;
        tmp = min(MFValue.low[0],MFValue.low[1],MFValue.low[2]);
        if(tmp > outputFuzzy.low[0]){
            outputFuzzy.low[0] = tmp;
        }
        if(tmp > outputFuzzy.low[1]){
            outputFuzzy.low[1] = tmp;
        }
    }

    if(MFValue.low[0] > 0.0 && MFValue.low[1] > 0.0 && MFValue.medium[2] > 0.0){
        std::cout << "LOW LOW MED : MED MED" << std::endl;
        tmp = min(MFValue.low[0],MFValue.low[1],MFValue.medium[2]);
        if(tmp > outputFuzzy.medium[0]){
            outputFuzzy.medium[0] = tmp;
        }
        if(tmp > outputFuzzy.medium[1]){
            outputFuzzy.medium[1] = tmp;
        }
    }

    if(MFValue.low[0] > 0.0 && MFValue.low[1] > 0.0 && MFValue.high[2] > 0.0){
        std::cout << "LOW LOW HIGH : HIGH HIGH" << std::endl;
        tmp = min(MFValue.low[0],MFValue.low[1],MFValue.high[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 4
    if(MFValue.low[0] > 0.0 && MFValue.medium[1] > 0.0 && MFValue.low[2] > 0.0){
        std::cout << "LOW MED LOW : LOW MED" << std::endl;
        tmp = min(MFValue.low[0],MFValue.medium[1],MFValue.low[2]);
        if(tmp > outputFuzzy.low[0]){
            outputFuzzy.low[0] = tmp;
        }
        if(tmp > outputFuzzy.medium[1]){
            outputFuzzy.medium[1] = tmp;
        }
    }
    // 5
    if(MFValue.low[0] > 0.0 && MFValue.medium[1] > 0.0 && MFValue.medium[2] > 0.0){
        std::cout << "LOW MED MED : MED HIGH" << std::endl;
        tmp = min(MFValue.low[0],MFValue.medium[1],MFValue.medium[2]);
        if(tmp > outputFuzzy.medium[0]){
            outputFuzzy.medium[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 6
    if(MFValue.low[0] > 0.0 && MFValue.medium[1] > 0.0 && MFValue.high[2] > 0.0){
        std::cout << "LOW MED HIGH : HIGH HIGH" << std::endl;
        tmp = min(MFValue.low[0],MFValue.medium[1],MFValue.high[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 7
    if(MFValue.low[0] > 0.0 && MFValue.high[1] > 0.0 && MFValue.low[2] > 0.0){
        std::cout << "LOW HIGH LOW : LOW HIGH" << std::endl;
        tmp = min(MFValue.low[0],MFValue.high[1],MFValue.low[2]);
        if(tmp > outputFuzzy.low[0]){
            outputFuzzy.low[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 8
    if(MFValue.low[0] > 0.0 && MFValue.high[1] > 0.0 && MFValue.medium[2] > 0.0){
        std::cout << "LOW HIGH MED : MED HIGH" << std::endl;
        tmp = min(MFValue.low[0],MFValue.high[1],MFValue.medium[2]);
        if(tmp > outputFuzzy.medium[0]){
            outputFuzzy.medium[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 9
    if(MFValue.low[0] > 0.0 && MFValue.high[1] > 0.0 && MFValue.high[2] > 0.0){
        std::cout << "LOW HIGH HIGH : HIGH HIGH" << std::endl;
        tmp = min(MFValue.low[0],MFValue.high[1],MFValue.high[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 10
    if(MFValue.medium[0] > 0.0 && MFValue.low[1] > 0.0 && MFValue.low[2] > 0.0){
        std::cout << "MED LOW LOW : MED LOW" << std::endl;
        tmp = min(MFValue.medium[0],MFValue.low[1],MFValue.low[2]);
        if(tmp > outputFuzzy.medium[0]){
            outputFuzzy.medium[0] = tmp;
        }
        if(tmp > outputFuzzy.low[1]){
            outputFuzzy.low[1] = tmp;
        }
    }
    // 11
    if(MFValue.medium[0] > 0.0 && MFValue.low[1] > 0.0 && MFValue.medium[2] > 0.0){
        std::cout << "MED LOW MED : HIGH MED" << std::endl;
        tmp = min(MFValue.medium[0],MFValue.low[1],MFValue.medium[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.medium[1]){
            outputFuzzy.medium[1] = tmp;
        }
    }
    // 12
    if(MFValue.medium[0] > 0.0 && MFValue.low[1] > 0.0 && MFValue.high[2] > 0.0){
        std::cout << "MED LOW HIGH : HIGH HIGH" << std::endl;
        tmp = min(MFValue.medium[0],MFValue.low[1],MFValue.high[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 13
    if(MFValue.medium[0] > 0.0 && MFValue.medium[1] > 0.0 && MFValue.low[2] > 0.0){
        std::cout << "MED MED LOW : MED MED" << std::endl;
        tmp = min(MFValue.medium[0],MFValue.medium[1],MFValue.low[2]);
        if(tmp > outputFuzzy.medium[0]){
            outputFuzzy.medium[0] = tmp;
        }
        if(tmp > outputFuzzy.medium[1]){
            outputFuzzy.medium[1] = tmp;
        }
    }
    // 14
    if(MFValue.medium[0] > 0.0 && MFValue.medium[1] > 0.0 && MFValue.medium[2] > 0.0){
        std::cout << "MED MED MED : HIGH HIGH" << std::endl;
        tmp = min(MFValue.medium[0],MFValue.medium[1],MFValue.medium[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 15
    if(MFValue.medium[0] > 0.0 && MFValue.medium[1] > 0.0 && MFValue.high[2] > 0.0){
        std::cout << "MED MED HIGH : HIGH HIGH" << std::endl;
        tmp = min(MFValue.medium[0],MFValue.medium[1],MFValue.high[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 16
    if(MFValue.medium[0] > 0.0 && MFValue.high[1] > 0.0 && MFValue.low[2] > 0.0){
        std::cout << "MED HIGH LOW : MED HIGH" << std::endl;
        tmp = min(MFValue.medium[0],MFValue.high[1],MFValue.low[2]);
        if(tmp > outputFuzzy.medium[0]){
            outputFuzzy.medium[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 17
    if(MFValue.medium[0] > 0.0 && MFValue.high[1] > 0.0 && MFValue.medium[2] > 0.0){
        std::cout << "MED HIGH MED : HIGH HIGH" << std::endl;
        tmp = min(MFValue.medium[0],MFValue.high[1],MFValue.medium[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 18
    if(MFValue.medium[0] > 0.0 && MFValue.high[1] > 0.0 && MFValue.high[2] > 0.0){
        std::cout << "MED HIGH HIGH : HIGH HIGH" << std::endl;
        tmp = min(MFValue.medium[0],MFValue.high[1],MFValue.high[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 19
    if(MFValue.high[0] > 0.0 && MFValue.low[1] > 0.0 && MFValue.low[2] > 0.0){
        std::cout << "HIGH LOW LOW : HIGH LOW" << std::endl;
        tmp = min(MFValue.high[0],MFValue.low[1],MFValue.low[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.low[1]){
            outputFuzzy.low[1] = tmp;
        }
    }
    // 20
    if(MFValue.high[0] > 0.0 && MFValue.low[1] > 0.0 && MFValue.medium[2] > 0.0){
        std::cout << "HIGH LOW MED : HIGH MED" << std::endl;
        tmp = min(MFValue.high[0],MFValue.low[1],MFValue.medium[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.medium[1]){
            outputFuzzy.medium[1] = tmp;
        }
    }
    // 21
    if(MFValue.high[0] > 0.0 && MFValue.low[1] > 0.0 && MFValue.high[2] > 0.0){
        std::cout << "HIGH LOW HIGH : HIGH HIGH" << std::endl;
        tmp = min(MFValue.high[0],MFValue.low[1],MFValue.high[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 22
    if(MFValue.high[0] > 0.0 && MFValue.medium[1] > 0.0 && MFValue.low[2] > 0.0){
        std::cout << "HIGH MED LOW : HIGH MED" << std::endl;
        tmp = min(MFValue.high[0],MFValue.medium[1],MFValue.low[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.medium[1]){
            outputFuzzy.medium[1] = tmp;
        }
    }
    // 23
    if(MFValue.high[0] > 0.0 && MFValue.medium[1] > 0.0 && MFValue.medium[2] > 0.0){
        std::cout << "HIGH MED MED : HIGH MED" << std::endl;
        tmp = min(MFValue.high[0],MFValue.medium[1],MFValue.medium[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.medium[1]){
            outputFuzzy.medium[1] = tmp;
        }
    }
    // 24
    if(MFValue.high[0] > 0.0 && MFValue.medium[1] > 0.0 && MFValue.high[2] > 0.0){
        std::cout << "HIGH MED HIGH : HIGH HIGH" << std::endl;
        tmp = min(MFValue.high[0],MFValue.medium[1],MFValue.high[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 25
    if(MFValue.high[0] > 0.0 && MFValue.high[1] > 0.0 && MFValue.low[2] > 0.0){
        std::cout << "HIGH HIGH LOW : HIGH HIGH" << std::endl;
        tmp = min(MFValue.high[0],MFValue.high[1],MFValue.low[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 26
    if(MFValue.high[0] > 0.0 && MFValue.high[1] > 0.0 && MFValue.medium[2] > 0.0){
        std::cout << "HIGH HIGH MED : HIGH HIGH" << std::endl;
        tmp = min(MFValue.high[0],MFValue.high[1],MFValue.medium[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
    // 27
    if(MFValue.high[0] > 0.0 && MFValue.high[1] > 0.0 && MFValue.high[2] > 0.0){
        std::cout << "HIGH HIGH HIGH : HIGH HIGH" << std::endl;
        tmp = min(MFValue.high[0],MFValue.high[1],MFValue.high[2]);
        if(tmp > outputFuzzy.high[0]){
            outputFuzzy.high[0] = tmp;
        }
        if(tmp > outputFuzzy.high[1]){
            outputFuzzy.high[1] = tmp;
        }
    }
}

void fuzzification(std::vector<double> &score, membershipFunction &MFValue, MFStructValue &MFunction){
    // MFValue.low[0,1,2] < Cam , Lidar, IoU
    for (int i = 0; i < 3; ++i){
        //LOW Descending Graphics
        //   .\    
        //   . \
        //   .  \
        // u ....\
        //   .  . \  
        //   b  x a
        // u = (a - x)/(a - b)

        if(score[i] > MFunction.low_b[i] && score[i] < MFunction.low_a[i]){
            MFValue.low.push_back((MFunction.low_a[i] - score[i])/(MFunction.low_a[i] - MFunction.low_b[i]));
        }else{
            MFValue.low.push_back(0.0);
        }

        //MED Ascending Graphics    //MED Descending Graphics
        //        /.                //   .\  
        //       / .                //   . \
        //      /  .                //   .  \
        // u ../.  .                // u ....\
        //    / .  .                //   .  . \  
        //   b1 x  a1               //  b2  x a2
        // u = (x - b1)/(a1 - b1)   //  u = (a2 - x)/(a2 - b2).

        if(score[i] >= MFunction.medium_b1[i] && score[i] <= MFunction.medium_a1[i]){
            MFValue.medium.push_back((score[i] - MFunction.medium_b1[i])/(MFunction.medium_a1[i] - MFunction.medium_b1[i]));
        }else if(score[i] > MFunction.medium_b2[i] && score[i] <= MFunction.medium_a2[i]){
            MFValue.medium.push_back((MFunction.medium_a2[i] - score[i])/(MFunction.medium_a2[i] - MFunction.medium_b2[i]));
        }else{
            MFValue.medium.push_back(0.0);
        }

        //HIGH Ascending Graphics    
        //        /.                
        //       / .                
        //      /  .            
        // u ../.  .           
        //    / .  .              
        //   b  x  a            
        // u = (x - b)/(a - b)  

        if(score[i] >= MFunction.high_b[i] && score[i] <= MFunction.high_a[i]){
            MFValue.high.push_back((score[i] - MFunction.high_b[i])/(MFunction.high_a[i] - MFunction.high_b[i]));
        }else{
            MFValue.high.push_back(0.0);
        }
         std::cout << "Input FUzzy" << std::endl;
        std::cout << MFValue.low[i] << " | " <<  MFValue.medium[i] << " | " << MFValue.high[i] << std::endl;
    }
};

void initFuzzy(MFStructValue &MFunction, membershipFunction &outputFuzzy){
    // CAMERA [0]
    MFunction.low_a.push_back(0.5);
    MFunction.low_b.push_back(0.0);
    MFunction.medium_a1.push_back(0.5);
    MFunction.medium_b1.push_back(0.25);
    MFunction.medium_a2.push_back(0.75);
    MFunction.medium_b2.push_back(0.5);
    MFunction.high_a.push_back(1.0);
    MFunction.high_b.push_back(0.5);
    // MFunction.low_a.push_back(3.0);
    // MFunction.low_b.push_back(-3.0);
    // MFunction.medium_a1.push_back(5.0);
    // MFunction.medium_b1.push_back(1.0);
    // MFunction.medium_a2.push_back(9.0);
    // MFunction.medium_b2.push_back(5.0);
    // MFunction.high_a.push_back(10.0);
    // MFunction.high_b.push_back(6.0);
    // // LIDAR [1]
    MFunction.low_a.push_back(0.5);
    MFunction.low_b.push_back(0.0);
    MFunction.medium_a1.push_back(0.5);
    MFunction.medium_b1.push_back(0.25);
    MFunction.medium_a2.push_back(0.75);
    MFunction.medium_b2.push_back(0.5);
    MFunction.high_a.push_back(1.0);
    MFunction.high_b.push_back(0.5);
    // MFunction.low_a.push_back(15.0);
    // MFunction.low_b.push_back(0.0);
    // MFunction.medium_a1.push_back(25.0);
    // MFunction.medium_b1.push_back(5.0);
    // MFunction.medium_a2.push_back(45.0);
    // MFunction.medium_b2.push_back(25.0);
    // MFunction.high_a.push_back(50.0);
    // MFunction.high_b.push_back(30.0);
    // // IOU [2]
    MFunction.low_a.push_back(50.0);
    MFunction.low_b.push_back(0.0);
    MFunction.medium_a1.push_back(50.0);
    MFunction.medium_b1.push_back(25.0);
    MFunction.medium_a2.push_back(75.0);
    MFunction.medium_b2.push_back(50.0);
    MFunction.high_a.push_back(100.0);
    MFunction.high_b.push_back(50.0);
    // // CONFIDENCE [3]
    MFunction.low_a.push_back(50.0);
    MFunction.low_b.push_back(0.0);
    MFunction.medium_a1.push_back(50.0);
    MFunction.medium_b1.push_back(25.0);
    MFunction.medium_a2.push_back(75.0);
    MFunction.medium_b2.push_back(50.0);
    MFunction.high_a.push_back(100.0);
    MFunction.high_b.push_back(50.0);

    outputFuzzy.low.push_back(0.0);
    outputFuzzy.medium.push_back(0.0);
    outputFuzzy.medium2.push_back(0.0);
    outputFuzzy.high.push_back(0.0);

};

void fuzzyFusion(){
    membershipFunction outputFuzzy, MFValue, outputDefuzzification;
    MFStructValue MFunction;
    std::vector<double> score;
    std::vector<double> crispOutput;
    
    // CRISP INPUT
    score.push_back(30.0);
    score.push_back(40.0);
    score.push_back(20.0);

    initFuzzy(MFunction,outputFuzzy);
    fuzzification(score, MFValue, MFunction);
    fuzzyInference(MFValue,outputFuzzy);
    defuzzification(outputFuzzy,outputDefuzzification,MFunction,crispOutput);
    
    std::cout << " CAMERA (L,M,H)   |    LIDAR (L,M,H)" << endl;
    std::cout << " " << outputFuzzy.low[0] << "   " <<  outputFuzzy.medium[0] << "   " << outputFuzzy.high[0] << "    |    " << outputFuzzy.low[1] << "   " << outputFuzzy.medium[1] << "   " << outputFuzzy.high[1] << endl;
    std::cout << " " << endl;
    std::cout << " CAM | LIDAR" << endl;
    std::cout << " " << crispOutput[0] << "       " <<  crispOutput[1] << std::endl;
};

void processFuzzyFusion(){

}