#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sndfile.hh>

using namespace std;
#define FRAME_BUFFER_SIZE 1

int main(int argc, char** argv){
	if(argc<4 || argc%2!=0){
		cerr << "Usage: atividade3_4 <a1> <x1> <a2> <x2> ... <ak> <xk> <dest_file>" << endl;
        return -1;
	}
	int i = 1;
	vector<float> weights;
	vector<SndfileHandle> tracks;

	while(i<argc-1){
		weights.push_back(atof(argv[i]));
		SndfileHandle inputAudioHandle(argv[i+1],SFM_READ);
		if (inputAudioHandle.frames() == 0) {
        	cerr << "Error opening input file";
        	return -1;
   		}
	    tracks.push_back(inputAudioHandle);
		i+=2;
	}

	SndfileHandle outputAudioHandle(
        argv[argc-1],
        SFM_WRITE, 
        tracks[0].format(), 
        tracks[0].channels(), 
        tracks[0].samplerate());

	int size = tracks.size();
    float *inBuffer[size];
    for(int i=0; i<size; i++)
    	inBuffer[i] = new float;

    float *outBuffer = new float;
    sf_count_t count = -1;

    while (count != 0) {
    	for(int i=0; i<size; i++){
        	count = tracks[i].read(inBuffer[i], FRAME_BUFFER_SIZE);
    	}
    	for(int i=0; i<size; i++){
    		*outBuffer += *inBuffer[i] * weights[i];
    		*inBuffer[i] = 0;
    	}
        outputAudioHandle.write(outBuffer, FRAME_BUFFER_SIZE);
        *outBuffer = 0;
    }

	return 0;
}