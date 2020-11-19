#ifndef __OCR_ANGLENET_H__
#define __OCR_ANGLENET_H__

#include "OcrStruct.h"
#include "onnx/onnxruntime_cxx_api.h"
#include <opencv/cv.hpp>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

using namespace cv;
using namespace std;
using namespace Ort;

class AngleNet {
public:

    ~AngleNet();

    bool initModel(AAssetManager *mgr, Env &ortEnv, SessionOptions &sessionOptions);

    vector<Angle> getAngles(vector<cv::Mat> &partImgs, bool doAngle, bool mostAngle);

private:
    unique_ptr<Session> session;
    vector<const char *> inputNames;
    vector<const char *> outputNames;

    const float meanValues[3] = {127.5, 127.5, 127.5};
    const float normValues[3] = {1.0 / 127.5, 1.0 / 127.5, 1.0 / 127.5};
    const int angleCols = 2;
    const int dstWidth = 192;
    const int dstHeight = 32;

    Angle getAngle(cv::Mat &src);
};


#endif //__OCR_ANGLENET_H__
