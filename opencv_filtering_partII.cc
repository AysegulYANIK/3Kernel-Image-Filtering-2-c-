//2.07.2019 code version 0.1 
/*
3D kernel image filtering for STM Assignment Work Part2
with OpenCV no restrictions

input form: 3D kernels single RGB color image
output form: 3D kernels filtered single RGB color image
**/

/*
Please be sure that you have opencv and its dependecies on your system installed.
Tip: you may check the installation guide.
**/
// implemented by Ayşegül Demirtaş
 
//compiling command
//g++ main.cpp -o output `pkg-config --cflags --libs opencv`

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <vector>
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

void filtering(const char *channel, const cv::Mat &img, cv::Mat &result)
{
	//construct the kernel such that all entries are initialised to 0
	cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));

	//assign the kernels value

	//R Channel Filter
	if(channel=="r"){

	kernel.at<float>(0,0) = 1.0;
	kernel.at<float>(0,1) = 1.0;
	kernel.at<float>(0,2) = 1.0;
	kernel.at<float>(1,0) = 1.0;
	kernel.at<float>(1,1) = 1.0;
	kernel.at<float>(1,2) = 1.0;
	kernel.at<float>(2,0) = 1.0;
	kernel.at<float>(2,1) = 1.0;
	kernel.at<float>(2,2) = 1.0;
	};

	//G Channel Filter
	if(channel=="g"){

	kernel.at<float>(0,0) = 1.0;
	kernel.at<float>(0,1) = 2.0;
	kernel.at<float>(0,2) = 1.0;
	kernel.at<float>(1,0) = 2.0;
	kernel.at<float>(1,1) = 4.0;
	kernel.at<float>(1,2) = 2.0;
	kernel.at<float>(2,0) = 1.0;
	kernel.at<float>(2,1) = 2.0;
	kernel.at<float>(2,2) = 1.0;
	};
	
	//B Channel Filter
	if(channel=="b"){

	kernel.at<float>(0,0) = 1.0;
	kernel.at<float>(0,2) = -1.0;
	kernel.at<float>(1,0) = 2.0;
	kernel.at<float>(1,2) = -2.0;
	kernel.at<float>(2,0) = 1.0;
	kernel.at<float>(2,2) = -1.0;
	};
	

    //now filter the image
    cv::filter2D (img, result, img.depth(), kernel);
}

int main( int argc, char** argv ) {
  
 	cv::Mat image;
 	image = cv::imread("image.jpg" , CV_LOAD_IMAGE_COLOR);
	
	imshow("Source",image);
	waitKey();
 
 	if(! image.data ) {
     		std::cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}

	//split RGB channels of input image
	cv::Mat BGR[3];
	split(image,BGR);

	//filtering seperately
	filtering("r",BGR[2],BGR[2]);
	filtering("g",BGR[1],BGR[1]);
	filtering("b",BGR[0],BGR[0]);

	imshow("R channel filtered by R kernel",BGR[2]);
	imshow("G channel filtered by G kernel",BGR[1]);
	imshow("B channel filtered by B kernel",BGR[0]);
	waitKey();

	//merging
	cv::Mat output;
	merge(BGR, 3, output);
	imshow("Merged",output);
	waitKey();

}

//end code

