/**
* Scale an audio file to a given factor
*/

#include <cstdlib>
#include <iostream>
#include <sndfile.hh>
#include <math.h>

using namespace std;

#define FRAME_BUFFER_SIZE 1
#define BIT_DEPTH 16

int main(int argc, char** argv) {
    if (argc < 4) {
        cerr << "Usage: atividade3_5 <audio> <dest> <factor>" << endl;

        return -1;
    }

    SndfileHandle inputAudioHandle(argv[1], SFM_READ);

    if (inputAudioHandle.frames() == 0) {
        cerr << "Error opening input file";

        return -1;
    }

    // we only accept mono WAV PCM 16  as input
    if (
        inputAudioHandle.format() != (SF_FORMAT_WAV | SF_FORMAT_PCM_16) ||
        inputAudioHandle.channels() > 1) {
        cerr << "Input file must be mono WAV PCM 16" << endl;

        return -1;
    }

    SndfileHandle outputAudioHandle(
        argv[2],
        SFM_WRITE,
        inputAudioHandle.format(),
        inputAudioHandle.channels(),
        inputAudioHandle.samplerate());

    float *inBuffer = new float;
    float *outBuffer = new float;
    sf_count_t count = -1;
    float sf = atof(argv[3]);

    bool clipping = false;
    float threshold = pow(2,BIT_DEPTH)-1;

    while (count != 0) {
        *outBuffer = (*inBuffer) * sf;
        if(*outBuffer > threshold) clipping = true;
        count = inputAudioHandle.read(inBuffer, FRAME_BUFFER_SIZE);
        outputAudioHandle.write(outBuffer, FRAME_BUFFER_SIZE);
    }

    clipping == true? cerr << "Clipping effect detected" << endl : cerr << "Undetected clipping effect" << endl;

    return 0;
}
