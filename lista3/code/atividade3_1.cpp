#include <cstdlib>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>

using namespace std;
using namespace cv;
using namespace std::chrono;
typedef high_resolution_clock clk;

string toString(int value);

int main(int argc, char** argv){
	if(argc < 4){
		cerr << "Usage: atividade3_1 <period> <video> <folder>" << endl;
        return -1;
	}

	//Inicializacao de variaveis
	VideoCapture capture;
    Mat frame;
    bool stop = false;
    int i = 0;
    //entradas do usuario no console
    string dir(argv[3]);
    capture.open(argv[2]);
    int period = atoi(argv[1]);
    //controle de tempo
    int fps = capture.get(CAP_PROP_FPS);
    float waitTime = 1000.0/fps;
    long timepassed = 0;
    long cumulatedTime = 0;
    //janela de exibicao do video
   	namedWindow("Video player", WINDOW_AUTOSIZE);

    while (!stop) {
    	clk::time_point t1 = clk::now();//captura o tempo inicial
        capture >> frame;
        if (frame.empty())
            stop = true;
        else {
            imshow("Video player", frame);
            if(waitKey(waitTime) == 'q')
            	stop = true;
        }
        clk::time_point t2 = clk::now();
    	timepassed = (long)duration_cast<milliseconds>( t2 - t1 ).count();
    	cumulatedTime += timepassed;
    	if(cumulatedTime>period*1000){
    		string path(dir + "/" + toString(i) + ".jpg");
            cout << path << endl;
            imwrite(path, frame);
            i++;
            cumulatedTime = 0;
    	}
    }

    return 0;

}

string toString(int value) {
  stringstream ss;
  ss << value;
  return ss.str();
}