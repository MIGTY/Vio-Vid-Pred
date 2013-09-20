// Vio-Vid-Pred.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include <opencv.hpp>

#include "MotionAngle.h"
#include "MotionFlow.h"

using namespace std;
using namespace cv;

int main(){

	const std::string file_name = "twinkle.mp4";

	vector<double> ma_feature;	//角度向量
	vector<double> mf_feature;	//运动向量

	cv::VideoCapture capture(file_name);
	if(!capture.isOpened()){
		std::cerr << "Sorry, failed to open " << file_name << "! " << std::endl;
		return -1;
	}

	cv::Mat frame;

	MotionAngle cMA;
	MotionFlow cMF;

	capture>>frame;

	cv::Mat m_buf[4];

	unsigned long int frame_num;
	frame_num = static_cast<unsigned long int>(capture.get(CV_CAP_PROP_FRAME_COUNT));

	cv::Size key_frame_size = cv::Size(640,360);
	cv::Mat key_frame = cv::Mat::Mat(key_frame_size, CV_32FC3); /*存储缩放帧*/

	for(;;){
		capture >> frame;
		if(frame.empty()) break;
		cv::resize(frame, key_frame, key_frame.size(), 0, 0, CV_INTER_AREA);
		cMA.motion_angle_feature(key_frame, ma_feature, true);
		cMF.cal_motion_vector(key_frame, mf_feature, true);
	}

	std::cout << "The program is over! Thank you! " << std::endl;

}


