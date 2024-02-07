#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// 이미지 처리 함수
cv::Mat processImage(Mat AFrame, int min_h, int min_s, int min_v, int max_h, int max_s, int max_v) {

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

int main() {

    // 웹캠 인덱스 설정
    int webcam_index = 0;

    // 웹캠 열기
    VideoCapture cap(1);

    if (!cap.isOpened()) {
        cerr << "카메라를 열 수 없습니다." << endl;
        return -1;
    }
    else {
        cap.set(CAP_PROP_WHITE_BALANCE_BLUE_U, 0.5);
    }

    cv::Mat frame, result;

    while (true) {
        cap >> frame;

        // 이미지 처리 함수 호출
        result = processImage(frame, 14, 70, 116, 92, 255, 255);

        // 결과 이미지 표시
        imshow("result fg", result);

        result.release();

        if (waitKey(33) == 27)
            break;
    }

    // 자원 해제
    cap.release();
    destroyAllWindows();

    return 0;
}
