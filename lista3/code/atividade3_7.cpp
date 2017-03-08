#include <cstdlib>
#include <iostream>
#include <sndfile.hh>
#include <cmath>

using namespace std;

#define FRAME_BUFFER_SIZE 1

float maxValue(string);
bool normalize(string, float);
bool clipping(float);

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Usage: atividade3_7 <src> <factor>" << endl;

        return -1;
    }

    float peak = maxValue(argv[1]);
    float newPeak = pow(10, atof(argv[2])/20);
    float s = newPeak/peak;
    cout << s << endl;
    bool clipped = normalize(argv[1], s);
    if(clipped)
        cout << "A normalização causou efeito de clipping!"<<endl;

    return 0;
}

float maxValue(string input){
    SndfileHandle inputAudioHandle(input, SFM_READ);

    if (inputAudioHandle.frames() == 0) {
        cerr << "Error opening input file";

        return -1;
    }
    if (
        inputAudioHandle.format() != (SF_FORMAT_WAV | SF_FORMAT_PCM_16) || 
        inputAudioHandle.channels() > 1) {
        cerr << "Input file must be mono WAV PCM 16" << endl;

        return -1;
    }
    float *inBuffer = new float;
    sf_count_t count = -1;
    float max = 0;

    while (count != 0) {
        count = inputAudioHandle.read(inBuffer, FRAME_BUFFER_SIZE);
        float absValue = abs(*inBuffer);
        if(absValue > max)
            max=absValue;
        *inBuffer = 0;
    }
    return max;
}

bool normalize(string input, float newPeak){
    SndfileHandle inputAudioHandle(input, SFM_READ);

    if (inputAudioHandle.frames() == 0) {
        cerr << "Error opening input file";

        return false;
    }
    if (
        inputAudioHandle.format() != (SF_FORMAT_WAV | SF_FORMAT_PCM_16) || 
        inputAudioHandle.channels() > 1) {
        cerr << "Input file must be mono WAV PCM 16" << endl;

        return false;
    }
    string dest = "../../audio/output_atividade3_7.wav";
    SndfileHandle outputAudioHandle(
        dest, 
        SFM_WRITE, 
        inputAudioHandle.format(), 
        inputAudioHandle.channels(), 
        inputAudioHandle.samplerate());

    sf_count_t count = -1;
    bool clipped = false;

    while (count != 0) {
        float *inBuffer = new float;
        float *outBuffer = new float;
        count = inputAudioHandle.read(inBuffer, FRAME_BUFFER_SIZE);
        *outBuffer = (*inBuffer) * newPeak;
        clipped = clipped || clipping(*outBuffer);
        outputAudioHandle.write(outBuffer, FRAME_BUFFER_SIZE);
    }
    return clipped;
}

bool clipping(float value){
    bool clipped = false;
    if(value > (pow(2,16)-1) )
        clipped = true;
    return clipped;
}