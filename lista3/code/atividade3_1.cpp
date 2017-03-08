/**
* Grabs one frame at each time period and saves them to the file system
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace cv;

string toString(int value);

int main(int argc, char** argv) {
    if (argc < 4) {
        cerr << "Usage: atividade3_1 <period> <video> <folder>" << endl;

        return -1;
    }

    VideoCapture capture;
    Mat frame;
    bool stop = false;
    string dir(argv[3]);
    int i = 0;
    int period = atoi(argv[1]);
    int cont = 0;

    capture.open(argv[2]);
    int fps = capture.get(CAP_PROP_FPS);

    while (!stop) {
        capture >> frame;
        if (frame.empty()) // no data
            stop = true;
        else if(cont == period*fps){
            cont = -1;
            string path(dir + "/" + toString(i) + ".jpg");

            cout << path << endl;
            imwrite(path, frame);
            i++;
        }
        cont++;
    }

    return 0;
}

string toString(int value) {
  stringstream ss;

  ss << value;

  return ss.str();
}
