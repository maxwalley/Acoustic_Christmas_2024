/*
  ==============================================================================

    VideoProcessor.cpp
    Created: 15 Nov 2024 10:12:50am
    Author:  Max Walley

  ==============================================================================
*/

#include "VideoProcessor.h"

//==============================================================================
VideoProcessor::VideoProcessor()
{
    if(!handClassifier.load("/Users/maxwalley/Documents/Dev/Acoustic_Christmas_2024/hand.xml"))
    {
        std::cout << "Error: Can't load classifier" << std::endl;
        return;
    }
    
    cv::Mat frame;
    
    cv::VideoCapture capture(0);
    
    if (!capture.isOpened())
    {
        std::cout << "ERROR: Can't initialize camera capture" << std::endl;
        return;
    }
    
    for (;;)
    {
        capture >> frame;
        
        detectAndDisplay(frame);
        
        cv::imshow("Frame", frame);
        
        int key = cv::waitKey(1);
        if (key == 27/*ESC*/)
        {
            break;
        }
    }
}

VideoProcessor::~VideoProcessor()
{
    
}

void VideoProcessor::detectAndDisplay(cv::Mat& frame)
{
    cv::Mat frame_gray;
    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );
    
    std::vector<cv::Rect> detections;
    handClassifier.detectMultiScale( frame_gray, detections );
    for ( size_t i = 0; i < detections.size(); i++ )
    {
        cv::Point center( detections[i].x + detections[i].width/2, detections[i].y + detections[i].height/2 );
        cv::ellipse( frame, center, cv::Size( detections[i].width/2, detections[i].height/2 ), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4 );
        cv::Mat faceROI = frame_gray( detections[i] );
        
            
        }
}
