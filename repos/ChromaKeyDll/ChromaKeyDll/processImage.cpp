#include "processImage.h"
#include "pch.h"


#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

#include "processImage.h"

using namespace cv;
using namespace std;

#pragma comment(lib, "opencv_world490d.lib")


// 이미지 처리 함수
extern "C" __declspec(dllexport) cv::Mat processImage(Mat AFrame, int min_h, int min_s, int min_v, int max_h, int max_s, int max_v) {

    cv::Mat hsv, mask, mask_inv, fg;

    // 이미지를 HSV로 변환
    cvtColor(AFrame, hsv, COLOR_BGR2HSV);

    // HSV 범위에 따라 마스크 생성
    inRange(hsv, Scalar(min_h, min_s, min_v), Scalar(max_h, max_s, max_v), mask);
    bitwise_not(mask, mask_inv);

    // 전경 추출
    bitwise_and(AFrame, AFrame, fg, mask_inv);

    return fg;
}