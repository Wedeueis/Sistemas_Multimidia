#include <cstdlib>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace cv;

string toString(int value);

int main(int argc, char** argv){
	if(argc < 3){
		cerr << "Usage: atividade3_2 <video> <folder>" << endl;
        return -1;
	}

	//Inicializacao de variaveis
	VideoWriter writer;
    Mat frame;
    bool stop = false;
    int i = 0;
    int fps = 25;
    int height = 400;
    int width = 720;

    //entradas do usuario no console
    string dir(argv[2]);
    string name(argv[1]);
    string path(dir + "/" + name);

    cout << fps << " " << name << " " << width << " " << height << endl;

    writer.open(
        name, // input file
        CV_FOURCC('M', 'J', 'P', 'G'), // codec code
        fps, // fps
        Size(width, height),  // dimensions
        true); // include color
    if (!writer.isOpened()) {
        cerr << "Failed to open output video" << endl;
        return -1;
    }


    while (!stop) {
        string framesPath(dir + "/" + toString(i) + ".jpg");
        frame = imread(framesPath);
        cout << i << " " << framesPath << endl;
        i++;
        if (frame.empty())
            stop = true;
        else {
            writer << frame;
        }
    }

    return 0;

}

string toString(int value) {
  stringstream ss;
  ss << value;
  return ss.str();
}