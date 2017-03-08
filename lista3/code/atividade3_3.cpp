#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat convertByAverage(const vector<Mat>&);

int main(int argc, char** argv){
	if(argc < 2){
		cerr << "Usage: atividade3_3 <video>" << endl;
        return -1;
	}

	Mat frame;

	VideoCapture capture;
	capture.open(argv[1]);
	int fps = capture.get(CAP_PROP_FPS);
    float waitTime = 1000.0/fps;
    bool stop = false;

    namedWindow("Video player", WINDOW_AUTOSIZE);

    while(!stop){
    	capture >> frame;
    	if (frame.empty())
            stop = true;
        else {
        	vector<Mat> channels;
		    split(frame, channels);
        	frame = convertByAverage(channels);
            imshow("Video player", frame);
            if(waitKey(waitTime) == 'q')
            	stop = true;
        }
    }
}

Mat convertByAverage(const vector<Mat> &channels) {
    Mat result(channels[0].rows, channels[0].cols, CV_8UC1);

    for (int i = 0; i < result.rows; i++)
        for (int j = 0; j < result.cols; j++) {
            result.at<uchar>(i,j) = round((
                channels[0].at<uchar>(i,j) + 
                channels[1].at<uchar>(i,j) + 
                channels[2].at<uchar>(i,j)) / 3.0f);
        }

    return result;
}
