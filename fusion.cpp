void clearCamLidFuzzyFusionResult(detected_obstacles &CamLidFuzzyFusionResult);
// #define COMPILE_FUZZYFUSION
void print_txt(vector<vector<tDetection>> &camdetections, vector<vector<tDetection>> &liddetections,std::vector<int32_t> &indices){
    for(int i = 0; i < liddetections.size(); i++){
            // std::cout << " " << indices.at(i) << std::endl;  
            std::ofstream test;
            char file_name[256];
            sprintf(file_name,"%06d.txt",indices.at(i));
            string test2 = file_name;
            test.open("output/data/"+test2,std::ios_base::app);
            test << std::setprecision(17) << liddetections[0][0].thresh;
            test.close();
    }
}

void DoPrint_txt(detected_obstacles &CamLidFusionResult, int txt){
            std::ofstream test;
            char file_name[256];
            sprintf(file_name,"%06d.txt",txt);
            std::cout << txt << endl;
            
            string test2 = file_name;
            std::cout << test2 << endl;
            // Car -1 -1 -10 1155.50 225.78 1224.98 254.70 -1 -1 -1 -1000 -1000 -1000 -10 3.8522 
            test.open("output/data/"+test2,std::ios_base::app);    
            std::cout << CamLidFusionResult.BoundingBoxes.size() << endl;
            std::cout << CamLidFusionResult.ClassCategories.size() << endl;
#ifdef COMPILE_2D
    {
        for(int i = 0; i < CamLidFusionResult.BoundingBoxes.size(); i++){
            // std::cout << " " << indices.at(i) << std::endl;  
            // std::cout << i << endl;
            // std::cout << CamLidFusionResult.ClassCategories[i] << endl;
            test << CamLidFusionResult.ClassCategories[i];
            test << " ";
            test << "-1";
            test << " ";
            test << "-1";
            test << " ";
            test << "-10";
            test << " ";
            test << CamLidFusionResult.BoundingBoxes[i].x;
            test << " ";
            test << CamLidFusionResult.BoundingBoxes[i].y;
            test << " ";
            test << (CamLidFusionResult.BoundingBoxes[i].width + CamLidFusionResult.BoundingBoxes[i].x);
            test << " ";
            test << (CamLidFusionResult.BoundingBoxes[i].height + CamLidFusionResult.BoundingBoxes[i].y);
            test << " ";
            test << "-1";
            test << " ";
            test << "-1";
            test << " ";
            test << "-1";
            test << " ";
            test << "-1000";
            test << " ";
            test << "-1000";
            test << " ";
            test << "-1000";
            test << " ";
            test << "-10";
            test << " ";
            test << CamLidFusionResult.Score[i];
            test << "\n";
        }
    }
#else
    {
        for(int i = 0; i < CamLidFusionResult.BoundingBoxes.size(); i++){
            // std::cout << " " << indices.at(i) << std::endl;  
            // std::cout << i << endl;
            // std::cout << CamLidFusionResult.ClassCategories[i] << endl;
            test << CamLidFusionResult.ClassCategories[i];
            test << " ";
            test << "-1";
            test << " ";
            test << "-1";
            test << " ";
            test << CamLidFusionResult.Alpha[i];
            test << " ";
            test << CamLidFusionResult.BoundingBoxes[i].x;
            test << " ";
            test << CamLidFusionResult.BoundingBoxes[i].y;
            test << " ";
            test << (CamLidFusionResult.BoundingBoxes[i].width + CamLidFusionResult.BoundingBoxes[i].x);
            test << " ";
            test << (CamLidFusionResult.BoundingBoxes[i].height + CamLidFusionResult.BoundingBoxes[i].y);
            test << " ";
            test << CamLidFusionResult.BoundingBoxes3D[i].h;
            test << " ";
            test << CamLidFusionResult.BoundingBoxes3D[i].w;
            test << " ";
            test << CamLidFusionResult.BoundingBoxes3D[i].l;
            test << " ";
            test << CamLidFusionResult.BoundingBoxes3D[i].x;
            test << " ";
            test << CamLidFusionResult.BoundingBoxes3D[i].y;
            test << " ";
            test << CamLidFusionResult.BoundingBoxes3D[i].z;
            test << " ";
            test << CamLidFusionResult.BoundingBoxes3D[i].rot;
            test << " ";
            test << CamLidFusionResult.Score[i];
            test << "\n";
        }
    }
#endif

    
    test.close();
}

float FindIoU(rectF a, rectF b)
{
    float 
    x1 = a.x, 
    y1 = a.y, 
    x2 = a.x + a.width, 
    y2 = a.y + a.height;

    float 
    x3 = b.x, 
    y3 = b.y, 
    x4 = b.x + b.width, 
    y4 = b.y + b.height;

    // top right
    float x5 = std::max(x1, x3);
    float y5 = std::max(y1, y3);
    // buttom right
    float x6 = std::min(x2, x4);
    float y6 = std::min(y2, y4);

    // no intersection
    if (x5 > x6 || y5 > y6) {
        // "No intersection";
        return 0;
    }
    // std::cout << x5 << " " << x6 << std::endl;
    // std::cout << y5 << " " << y6 << std::endl;

    float i = (x6 - x5) * (y6 - y5);
    // std::cout << i << std::endl;
    float u = ((x2 - x1) * (y2 - y1)) + ((x4 - x3) * (y4 - y3)) - i;

    return i/u;
}

rectF convertKittiToRect(double &left, double &top, double &right, double &buttom){
    rectF output;
    output.x = left;
    output.y = top;
    output.width = right-left;
    output.height = buttom-top;

    return output;
}

rectF convertKittiToDimLoc(double &left, double &top, double &right, double &buttom){
    rectF output;
    output.x = left;
    output.y = top;
    output.width = right-left;
    output.height = buttom-top;

    return output;
}

void DoInferenceFuzzyFusion(detected_obstacles &detectionLidar, detected_obstacles &detectionCamera, detected_obstacles &CamLidFusionResult, MFStructValue &MFunction, membershipFunction &outputFuzzy){
    membershipFunction MFValue,outputDefuzzification;
    std::vector<double> score;
    std::vector<double> crispOutput;
    
    detected_obstacles CamLidFuzzyFusionResult;
    
    if (!detectionLidar.ClassCategories.empty())
        {
            for (auto it = detectionLidar.ClassCategories.begin();
                 it != detectionLidar.ClassCategories.end(); ++it)
            {
                auto idx = it - detectionLidar.ClassCategories.begin();
                //Camera Prediction
                if (!detectionCamera.ClassCategories.empty())
                {
                    for (auto it2 = detectionCamera.ClassCategories.begin();
                        it2 != detectionCamera.ClassCategories.end(); ++it2)
                    {
                        auto idx2 = it2 - detectionCamera.ClassCategories.begin(); 
                        // std::cout << "** ==IDX2== **" << idx2 << std::endl;
                        float IoU = FindIoU(detectionLidar.BoundingBoxes[idx],detectionCamera.BoundingBoxes[idx2]);
                        // IOU > 0 , Process Fuzzy step 1
                        if(IoU > 0){
                            std::cout << "** ==IDX2== ** id Cam : " << idx2 << std::endl;
                            score.clear();
                            MFValue.low.clear();
                            MFValue.medium.clear();
                            MFValue.medium2.clear();
                            MFValue.high.clear();
                            outputDefuzzification.low.clear();
                            outputDefuzzification.medium.clear();
                            outputDefuzzification.medium2.clear();
                            outputDefuzzification.high.clear();
                            crispOutput.clear();
                            std::cout << " CAMERA |  LIDAR  | IoU" << endl;
                            std::cout << detectionCamera.Score[idx2] << " | " << detectionLidar.Score[idx2] << " | " << IoU << endl;
                            // normalized
                            if(detectionCamera.Score[idx2] > MFunction.high_a[0]){
                                score.push_back(MFunction.high_a[0]); 
                            }else{
                                score.push_back(detectionCamera.Score[idx2]);
                            }

                            if(detectionLidar.Score[idx2] > MFunction.high_a[1]){
                                score.push_back(MFunction.high_a[1]); 
                            }else{
                                score.push_back(detectionLidar.Score[idx2]);
                            }
                            
                            score.push_back(IoU*100.0); //IoU
                            fuzzification(score, MFValue, MFunction);
                            fuzzyInference(MFValue,outputFuzzy);
                            defuzzification(outputFuzzy,outputDefuzzification,MFunction,crispOutput);
                            std::cout << " CAMERA (L,M,H)   |    LIDAR (L,M,H)" << endl;
                            std::cout << " " << outputFuzzy.low[0] << "   " <<  outputFuzzy.medium[0] << "   " << outputFuzzy.high[0] << "    |    " << outputFuzzy.low[1] << "   " << outputFuzzy.medium[1] << "   " << outputFuzzy.high[1] << endl;
                            std::cout << " " << endl;
                            std::cout << " CAM | LIDAR" << endl;
                            std::cout << " " << crispOutput[0] << "       " <<  crispOutput[1] << std::endl;

                            if(crispOutput[0] > 40 || crispOutput[1] > 40){
                                detectionLidar.IoUCamLid[idx] = IoU;
                                detectionCamera.IoUCamLid[idx2] = IoU;
                                // if(crispOutput[0] > crispOutput[1]){
                                    // CamLidFuzzyFusionResult.BoundingBoxes.push_back(detectionCamera.BoundingBoxes[idx2]);
                                    // CamLidFuzzyFusionResult.Depths.push_back(0.0);
                                    // CamLidFuzzyFusionResult.IoUCamLid.push_back(0.0);
                                    // CamLidFuzzyFusionResult.Score.push_back(detectionCamera.Score[idx2]);
                                    // CamLidFuzzyFusionResult.ClassCategories.push_back(detectionCamera.ClassCategories[idx2]);

                                    CamLidFuzzyFusionResult.BoundingBoxes.push_back(detectionLidar.BoundingBoxes[idx]);
                                    CamLidFuzzyFusionResult.BoundingBoxes3D.push_back(detectionLidar.BoundingBoxes3D[idx]);
                                    CamLidFuzzyFusionResult.Alpha.push_back(detectionLidar.Alpha[idx]);
                                    CamLidFuzzyFusionResult.Depths.push_back(0.0);
                                    CamLidFuzzyFusionResult.IoUCamLid.push_back(0.0);
                                    CamLidFuzzyFusionResult.Score.push_back(detectionLidar.Score[idx]);
                                    CamLidFuzzyFusionResult.ClassCategories.push_back(detectionLidar.ClassCategories[idx]);
                                // }else{
                                //     CamLidFuzzyFusionResult.BoundingBoxes.push_back(detectionLidar.BoundingBoxes[idx]);
                                //     CamLidFuzzyFusionResult.Depths.push_back(0.0);
                                //     CamLidFuzzyFusionResult.IoUCamLid.push_back(0.0);
                                //     CamLidFuzzyFusionResult.Score.push_back(detectionLidar.Score[idx]);
                                //     CamLidFuzzyFusionResult.ClassCategories.push_back(detectionLidar.ClassCategories[idx]);
                                // }
                            }
                        }
                    }
                } 
                // LIDAR THRESHOLD
                if(detectionLidar.IoUCamLid[idx] == 0.0 ){
                    if(detectionLidar.Score[idx] >= 0.9){
                        std::cout << "** CASE 1 **" <<  std::endl;
                        std::cout << "IoU : " << 0 << std::endl;
                        std::cout << "Class Lidar : " << detectionLidar.ClassCategories[idx] << " " << detectionLidar.Score[idx] << std::endl;
                                
                        //Return from Cam DATA
                        CamLidFusionResult.BoundingBoxes.push_back(detectionLidar.BoundingBoxes[idx]);
                        CamLidFusionResult.BoundingBoxes3D.push_back(detectionLidar.BoundingBoxes3D[idx]);
                        CamLidFusionResult.Alpha.push_back(detectionLidar.Alpha[idx]);
                        CamLidFusionResult.Depths.push_back(0.0);
                        CamLidFusionResult.IoUCamLid.push_back(0.0);
                        CamLidFusionResult.Score.push_back(detectionLidar.Score[idx]);
                        CamLidFusionResult.ClassCategories.push_back(detectionLidar.ClassCategories[idx]);
                    }
                }   
            }
        }

    // NMS
    std::vector<int> deleted;
    deleted.clear();
    std::cout << "CamLidFuzzyFusionResult.size() " << CamLidFuzzyFusionResult.ClassCategories.size() << endl;
    for (auto it = CamLidFuzzyFusionResult.ClassCategories.begin();
         it != CamLidFuzzyFusionResult.ClassCategories.end(); ++it)
    {
        auto idx = it - CamLidFuzzyFusionResult.ClassCategories.begin();
        int total = CamLidFuzzyFusionResult.ClassCategories.size(); 
        int start = 1;

        for (uint32_t i = 0; i < CamLidFuzzyFusionResult.ClassCategories.size(); ++i)
        {
            if(i+idx+start >= CamLidFuzzyFusionResult.ClassCategories.size()){
                break;
            }else{
                std::cout << "index ke " << idx << " terhadap ke " << i+idx+start << endl;
                std::cout << "            deleted.size() " << deleted.size() << endl;
                float IoU = FindIoU(CamLidFuzzyFusionResult.BoundingBoxes[idx],CamLidFuzzyFusionResult.BoundingBoxes[i+idx+start]);
                // NMS IoU #################################################
                if(IoU >= 0.9){
                    if(CamLidFuzzyFusionResult.Score[idx] > CamLidFuzzyFusionResult.Score[i+idx+start]){
                        //delete index i+start
                        std::cout << "            logic deleted.idx : " << (std::find(deleted.begin(), deleted.end(), i+idx+start) != deleted.end()) << endl;
                        if ( std::find(deleted.begin(), deleted.end(), i+idx+start) != deleted.end()){

                            //notfound
                        }else{
                            std::cout << "            deleted.idx : " << i+idx+start << endl;
                            deleted.push_back(i+idx+start);
                        }
                        
                    }else{
                        //delete idx
                        std::cout << "            logic deleted.idx : " << (std::find(deleted.begin(), deleted.end(), idx) != deleted.end()) << std::endl;
                        if ( std::find(deleted.begin(), deleted.end(), idx) != deleted.end()){
                            //notfound
                        }else{
                            std::cout << "            deleted.idx : " << idx << endl;
                            deleted.push_back(idx);
                        }
                        break;
                    }
                }
                std::cout << "      " << endl;
            }
        }
    }
    std::cout << "CamLidFuzzyFusionResult.size() " << CamLidFuzzyFusionResult.BoundingBoxes.size() << endl;
    std::cout << "deleted.size() " << deleted.size() << endl;
    for (auto it = CamLidFuzzyFusionResult.ClassCategories.begin();
         it != CamLidFuzzyFusionResult.ClassCategories.end(); ++it)
    {
        auto idx = it - CamLidFuzzyFusionResult.ClassCategories.begin();
        if ( std::find(deleted.begin(), deleted.end(), idx) != deleted.end()){

        }else{
            CamLidFusionResult.BoundingBoxes.push_back(CamLidFuzzyFusionResult.BoundingBoxes[idx]);
            CamLidFusionResult.BoundingBoxes3D.push_back(CamLidFuzzyFusionResult.BoundingBoxes3D[idx]);
            CamLidFusionResult.Alpha.push_back(CamLidFuzzyFusionResult.Alpha[idx]);
            CamLidFusionResult.Depths.push_back(0.0);
            CamLidFusionResult.IoUCamLid.push_back(CamLidFuzzyFusionResult.IoUCamLid[idx]);
            CamLidFusionResult.Score.push_back(CamLidFuzzyFusionResult.Score[idx]);
            CamLidFusionResult.ClassCategories.push_back(CamLidFuzzyFusionResult.ClassCategories[idx]);
        }
    }
    clearCamLidFuzzyFusionResult(CamLidFuzzyFusionResult);

#ifdef COMPILE_2D
    {
        //Camera Prediction
        if (!detectionCamera.ClassCategories.empty())
        {
            for (auto it2 = detectionCamera.ClassCategories.begin();
            it2 != detectionCamera.ClassCategories.end(); ++it2)
            {   
                auto idx2 = it2 - detectionCamera.ClassCategories.begin(); 
                if(detectionCamera.IoUCamLid[idx2] == 0.0 ){
                    // CAMERA THRESHOLD #################################################
                    if(detectionCamera.Score[idx2] >= 1){
                        std::cout << "** CASE 3 **" <<  std::endl;
                        std::cout << "IoU : " << 0 << std::endl;
                        std::cout << "Class Camera : " << detectionCamera.ClassCategories[idx2] << " " << detectionCamera.Score[idx2] << std::endl;
                                
                        //Return from Cam DATA
                        CamLidFusionResult.BoundingBoxes.push_back(detectionCamera.BoundingBoxes[idx2]);
                        CamLidFusionResult.Depths.push_back(0.0);
                        CamLidFusionResult.IoUCamLid.push_back(0.0);
                        CamLidFusionResult.Score.push_back(detectionCamera.Score[idx2]);
                        CamLidFusionResult.ClassCategories.push_back(detectionCamera.ClassCategories[idx2]);
                    }
                }
            }
        }
    }
#endif
}

void DoInferenceFusion(detected_obstacles &detectionLidar, detected_obstacles &detectionCamera, detected_obstacles &CamLidFusionResult){
    if (!detectionLidar.ClassCategories.empty())
        {
            for (auto it = detectionLidar.ClassCategories.begin();
                 it != detectionLidar.ClassCategories.end(); ++it)
            {
                auto idx = it - detectionLidar.ClassCategories.begin();
                std::cout << "** ==IDX== **" << idx << std::endl;
                //Camera Prediction
                if (!detectionCamera.ClassCategories.empty())
                {
                    for (auto it2 = detectionCamera.ClassCategories.begin();
                        it2 != detectionCamera.ClassCategories.end(); ++it2)
                    {
                        auto idx2 = it2 - detectionCamera.ClassCategories.begin(); 
                        std::cout << "** ==IDX2== **" << idx2 << std::endl;
                        float IoU = FindIoU(detectionLidar.BoundingBoxes[idx],detectionCamera.BoundingBoxes[idx2]);
                        if(IoU > 0.5 && detectionCamera.IoUCamLid[idx2] == 0.0 ){
                            //Case 2 A
                            std::cout << "** CASE 2 A **" <<  std::endl;
                            std::cout << "IoU : " << IoU << std::endl;
                            std::cout << "Class Lidar  : " << detectionLidar.ClassCategories[idx] << " " << detectionLidar.Score[idx] <<  std::endl;
                            std::cout << "Class Camera : " << detectionCamera.ClassCategories[idx2] << " " << detectionCamera.Score[idx2] << std::endl;
                            
                            //If IoU > 5, then IoU has been filled in the old vector, so it is not processed again later
                            detectionLidar.IoUCamLid[idx] = IoU;
                            detectionCamera.IoUCamLid[idx2] = IoU;

                            if(detectionLidar.ClassCategories[idx] == detectionCamera.ClassCategories[idx2]){
                                //Case 2 A 1 Same Class
                                std::cout << "** CASE 2 A 1**" <<  std::endl;
                                //Return from CAM DATA
                                CamLidFusionResult.BoundingBoxes.push_back(detectionCamera.BoundingBoxes[idx2]);
                                CamLidFusionResult.Depths.push_back(0.0);
                                CamLidFusionResult.IoUCamLid.push_back(IoU);
                                CamLidFusionResult.Score.push_back(detectionCamera.Score[idx2]);
                                CamLidFusionResult.ClassCategories.push_back(detectionCamera.ClassCategories[idx2]);
                                
                            }else{
                                 //Case 2 A 2 Different Class
                                std::cout << "** CASE 2 A 2**" <<  std::endl;
                                if(detectionLidar.Score[idx] > 0.55){
                                    //Return from Lidar DATA
                                    CamLidFusionResult.BoundingBoxes.push_back(detectionLidar.BoundingBoxes[idx]);
                                    CamLidFusionResult.Depths.push_back(0.0);
                                    CamLidFusionResult.IoUCamLid.push_back(0.0);
                                    CamLidFusionResult.Score.push_back(detectionLidar.Score[idx]);
                                    CamLidFusionResult.ClassCategories.push_back(detectionLidar.ClassCategories[idx]);
                                }else{
                                    detectionLidar.IoUCamLid[idx] = 0.0;
                                }
                                
                                if(detectionCamera.Score[idx2] > 0.55){
                                    //Return from Lidar DATA
                                    CamLidFusionResult.BoundingBoxes.push_back(detectionCamera.BoundingBoxes[idx2]);
                                    CamLidFusionResult.Depths.push_back(0.0);
                                    CamLidFusionResult.IoUCamLid.push_back(0.0);
                                    CamLidFusionResult.Score.push_back(detectionCamera.Score[idx2]);
                                    CamLidFusionResult.ClassCategories.push_back(detectionCamera.ClassCategories[idx2]);
                                }else{
                                    detectionCamera.IoUCamLid[idx2] = 0.0;
                                }
                               
                            }
                            break;
                        }else if(IoU > 0 && IoU <= 0.5 && detectionCamera.IoUCamLid[idx2] == 0.0 ){
                            //IOU 0.1 - 0/5
                            //Case 2 B
                            std::cout << "** CASE 2 B **" <<  std::endl;
                            std::cout << "IoU : " << IoU << std::endl;
                            std::cout << "Class Lidar  : " << detectionLidar.ClassCategories[idx] << " " << detectionLidar.Score[idx] <<  std::endl;
                            std::cout << "Class Camera : " << detectionCamera.ClassCategories[idx2] << " " << detectionCamera.Score[idx2] << std::endl;
                            
                            //If IoU, then IoU has been filled in the old vector, so it is not processed again later
                            detectionLidar.IoUCamLid[idx] = IoU;
                            detectionCamera.IoUCamLid[idx2] = IoU;

                            if(detectionLidar.ClassCategories[idx] == detectionCamera.ClassCategories[idx2]){
                                //Case 2 B 1
                                if(detectionCamera.Score[idx2] > 0.45){
                                    std::cout << "** CASE 2 B 1**" <<  std::endl;
                                    //Return from CAM DATA
                                    CamLidFusionResult.BoundingBoxes.push_back(detectionCamera.BoundingBoxes[idx2]);
                                    CamLidFusionResult.Depths.push_back(0.0);
                                    CamLidFusionResult.IoUCamLid.push_back(IoU);
                                    CamLidFusionResult.Score.push_back(detectionCamera.Score[idx2]);
                                    CamLidFusionResult.ClassCategories.push_back(detectionCamera.ClassCategories[idx2]);
                                }else{
                                    detectionLidar.IoUCamLid[idx] = 0.0;
                                    detectionCamera.IoUCamLid[idx2] = 0.0;
                                }
                                
                            }else{
                                //Case 2 B 2
                                std::cout << "** CASE 2 B 2**" <<  std::endl;
                                if(detectionLidar.Score[idx] > 0.65){
                                    //Return from Lidar DATA
                                    CamLidFusionResult.BoundingBoxes.push_back(detectionLidar.BoundingBoxes[idx]);
                                    CamLidFusionResult.Depths.push_back(0.0);
                                    CamLidFusionResult.IoUCamLid.push_back(0.0);
                                    CamLidFusionResult.Score.push_back(detectionLidar.Score[idx]);
                                    CamLidFusionResult.ClassCategories.push_back(detectionLidar.ClassCategories[idx]);
                                }else{
                                    detectionLidar.IoUCamLid[idx] = 0.0;
                                }
                                if(detectionCamera.Score[idx2] > 0.65){
                                    //Return from Cam DATA
                                    CamLidFusionResult.BoundingBoxes.push_back(detectionCamera.BoundingBoxes[idx2]);
                                    CamLidFusionResult.Depths.push_back(0.0);
                                    CamLidFusionResult.IoUCamLid.push_back(0.0);
                                    CamLidFusionResult.Score.push_back(detectionCamera.Score[idx2]);
                                    CamLidFusionResult.ClassCategories.push_back(detectionCamera.ClassCategories[idx2]);
                                }else{
                                    detectionCamera.IoUCamLid[idx2] = 0.0;
                                }
                            }
                            break;
                        }
                    }
                }

                if(detectionLidar.IoUCamLid[idx] == 0.0 ){
                    if(detectionLidar.Score[idx] > 0.50){
                        std::cout << "** CASE 1 **" <<  std::endl;
                        std::cout << "IoU : " << 0 << std::endl;
                        std::cout << "Class Camera : " << detectionLidar.ClassCategories[idx] << " " << detectionLidar.Score[idx] << std::endl;
                                
                        //Return from Cam DATA
                        CamLidFusionResult.BoundingBoxes.push_back(detectionLidar.BoundingBoxes[idx]);
                        CamLidFusionResult.Depths.push_back(0.0);
                        CamLidFusionResult.IoUCamLid.push_back(0.0);
                        CamLidFusionResult.Score.push_back(detectionLidar.Score[idx]);
                        CamLidFusionResult.ClassCategories.push_back(detectionLidar.ClassCategories[idx]);
                    }
                }
                
                
            }
        }

    //Camera Prediction
    if (!detectionCamera.ClassCategories.empty())
    {
        for (auto it2 = detectionCamera.ClassCategories.begin();
        it2 != detectionCamera.ClassCategories.end(); ++it2)
        {
            auto idx2 = it2 - detectionCamera.ClassCategories.begin(); 
            if(detectionCamera.IoUCamLid[idx2] == 0.0 ){
                if(detectionCamera.Score[idx2] > 0.65){
                    std::cout << "** CASE 3 **" <<  std::endl;
                    std::cout << "IoU : " << 0 << std::endl;
                    std::cout << "Class Camera : " << detectionCamera.ClassCategories[idx2] << " " << detectionCamera.Score[idx2] << std::endl;
                            
                    //Return from Cam DATA
                    CamLidFusionResult.BoundingBoxes.push_back(detectionCamera.BoundingBoxes[idx2]);
                    CamLidFusionResult.Depths.push_back(0.0);
                    CamLidFusionResult.IoUCamLid.push_back(0.0);
                    CamLidFusionResult.Score.push_back(detectionCamera.Score[idx2]);
                    CamLidFusionResult.ClassCategories.push_back(detectionCamera.ClassCategories[idx2]);
                }
            }
        }
    }
}

void cleardetectionLidar(detected_obstacles &detectionLidar){
    detectionLidar.BoundingBoxes.clear();
    detectionLidar.BoundingBoxes3D.clear();
    detectionLidar.Alpha.clear();
    detectionLidar.ClassCategories.clear();
    detectionLidar.Depths.clear();
    detectionLidar.Score.clear();
    detectionLidar.IoUCamLid.clear();
}

void cleardetectionCamera(detected_obstacles &detectionCamera){
    detectionCamera.BoundingBoxes.clear();
    detectionCamera.ClassCategories.clear();
    detectionCamera.Depths.clear();
    detectionCamera.Score.clear();
    detectionCamera.IoUCamLid.clear();
}

void clearCamLidFusionResult(detected_obstacles &CamLidFusionResult){
    CamLidFusionResult.BoundingBoxes.clear();
    CamLidFusionResult.BoundingBoxes3D.clear();
    CamLidFusionResult.Alpha.clear();
    CamLidFusionResult.ClassCategories.clear();
    CamLidFusionResult.Depths.clear();
    CamLidFusionResult.Score.clear();
    CamLidFusionResult.IoUCamLid.clear();
}

void clearCamLidFuzzyFusionResult(detected_obstacles &CamLidFuzzyFusionResult){
    CamLidFuzzyFusionResult.BoundingBoxes.clear();
    CamLidFuzzyFusionResult.BoundingBoxes3D.clear();
    CamLidFuzzyFusionResult.Alpha.clear();
    CamLidFuzzyFusionResult.ClassCategories.clear();
    CamLidFuzzyFusionResult.Depths.clear();
    CamLidFuzzyFusionResult.Score.clear();
    CamLidFuzzyFusionResult.IoUCamLid.clear();
}

void processFusion(vector<vector<tDetection>> &camdetections, vector<vector<tDetection>> &liddetections,std::vector<int32_t> &indices,MFStructValue &MFunction, membershipFunction &outputFuzzy){
    for(int i = 0; i < liddetections.size(); i++){          // list of txt indices.at(i) 000001.txt
        std::cout << "======= FUSION " << indices.at(i) << ".txt =======" << std::endl;
        detected_obstacles detectionLidar;
        for(int j = 0; j < liddetections[i].size(); j++){   // content of txt / line
            // std::cout << ""<< indices.at(i) << ".txt :" << liddetections[i][j].box.type << " " << liddetections[i][j].box.x1 << " " << liddetections[i][j].box.y1 << " " << liddetections[i][j].box.x2 << " " << liddetections[i][j].box.y2 << " score : " << liddetections[i][j].thresh << std::endl;
            rectF xywh = convertKittiToRect(liddetections[i][j].box.x1,liddetections[i][j].box.y1,liddetections[i][j].box.x2,liddetections[i][j].box.y2);
            
            dimLocRot hwlxyzrot;
            hwlxyzrot.h = liddetections[i][j].h;
            hwlxyzrot.w = liddetections[i][j].w;
            hwlxyzrot.l = liddetections[i][j].l;
            hwlxyzrot.x = liddetections[i][j].t1;
            hwlxyzrot.y = liddetections[i][j].t2;
            hwlxyzrot.z = liddetections[i][j].t3;
            hwlxyzrot.rot = liddetections[i][j].ry;
            // std::cout << "xywh : "<< xywh.x << " " << xywh.y << " " << xywh.width << " " << xywh.height << std::endl;
            detectionLidar.BoundingBoxes.push_back(xywh);
            detectionLidar.BoundingBoxes3D.push_back(hwlxyzrot);
            detectionLidar.Alpha.push_back(liddetections[i][j].box.alpha);
            detectionLidar.Depths.push_back(0.0);
            detectionLidar.IoUCamLid.push_back(0.0);
            detectionLidar.Score.push_back(liddetections[i][j].thresh);
            detectionLidar.ClassCategories.push_back(liddetections[i][j].box.type.c_str());
        };
        std::cout << "Lidar Found : " << detectionLidar.BoundingBoxes.size() << " object" << std::endl;
        detected_obstacles detectionCamera;
        for(int j = 0; j < camdetections[i].size(); j++){   // content of txt / line
            // std::cout << ""<< indices.at(i) << ".txt :" << camdetections[i][j].box.type << " " << camdetections[i][j].box.x1 << " " << camdetections[i][j].box.y1 << " " << camdetections[i][j].box.x2 << " " << camdetections[i][j].box.y2 << " score : " << camdetections[i][j].thresh << std::endl;
            rectF xywh = convertKittiToRect(camdetections[i][j].box.x1,camdetections[i][j].box.y1,camdetections[i][j].box.x2,camdetections[i][j].box.y2);
            // std::cout << "xywh : "<< xywh.x << " " << xywh.y << " " << xywh.width << " " << xywh.height << std::endl;
            detectionCamera.BoundingBoxes.push_back(xywh);
            detectionCamera.Depths.push_back(0.0);
            detectionCamera.IoUCamLid.push_back(0.0);
            detectionCamera.Score.push_back(camdetections[i][j].thresh);
            detectionCamera.ClassCategories.push_back(camdetections[i][j].box.type.c_str());
        };
        std::cout << "Camera Found : " << detectionCamera.BoundingBoxes.size() << " object" << std::endl;

        detected_obstacles CamLidFusionResult;

#ifdef COMPILE_FUZZYFUSION
    {
        std::cout << "FUZZY : " << std::endl;
        DoInferenceFuzzyFusion(detectionLidar,detectionCamera,CamLidFusionResult, MFunction, outputFuzzy);
    }
#else
    {
        DoInferenceFusion(detectionLidar,detectionCamera,CamLidFusionResult);
    }
#endif
        std::cout << "CamLidFusionResult Found : " << CamLidFusionResult.BoundingBoxes.size() << " object" << std::endl;
        DoPrint_txt(CamLidFusionResult,indices.at(i));

        cleardetectionLidar(detectionLidar);
        std::cout << "======= cleardetectionLidar ======= " << std::endl;
        cleardetectionCamera(detectionCamera);
        std::cout << "======= cleardetectionCamera ======= " << std::endl;
        clearCamLidFusionResult(CamLidFusionResult);
        // clearCamLidFuzzyFusionResult(CamLidFuzzyFusionResult);

#ifdef COMPILE_FUZZYFUSION
    {
        std::cout << "======= FUZZY ======= " << std::endl;
    }
#endif
        std::cout << "====== FINISH FUSION ======" << std::endl;
        std::cout << " " << std::endl;
    }

    std::cout << "===============================" << std::endl;
}