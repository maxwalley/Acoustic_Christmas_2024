/*
  ==============================================================================

    VideoProcessor.h
    Created: 15 Nov 2024 10:12:50am
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

//==============================================================================
class VideoProcessor
{
public:
    VideoProcessor();
    ~VideoProcessor();
    
private:
    void detectAndDisplay(cv::Mat& frame);
    
    cv::CascadeClassifier handClassifier;
};
