#include <cstdlib>
#include <iostream>
#include <sndfile.hh>
#include <cmath>

using namespace std;

#define FRAME_BUFFER_SIZE 1

float maxValue(string);
void normalize(string, float);

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: atividade3_6 <src>" << endl;

        return -1;
    }

    float max = maxValue(argv[1]);
    normalize(argv[1], max);
    float peak = maxValue("../../audio/output_atividade3_6.wav");
    peak = 20*log10(peak);
    cout << "Peak do sinal em db: " << peak << endl;

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

void normalize(string input, float max){
    SndfileHandle inputAudioHandle(input, SFM_READ);

    if (inputAudioHandle.frames() == 0) {
        cerr << "Error opening input file";

        return;
    }
    if (
        inputAudioHandle.format() != (SF_FORMAT_WAV | SF_FORMAT_PCM_16) || 
        inputAudioHandle.channels() > 1) {
        cerr << "Input file must be mono WAV PCM 16" << endl;

        return;
    }
    string dest = "../../audio/output_atividade3_6.wav";
    SndfileHandle outputAudioHandle(
        dest, 
        SFM_WRITE, 
        inputAudioHandle.format(), 
        inputAudioHandle.channels(), 
        inputAudioHandle.samplerate());

    sf_count_t count = -1;

    while (count != 0) {
        float *inBuffer = new float;
        float *outBuffer = new float;
        count = inputAudioHandle.read(inBuffer, FRAME_BUFFER_SIZE);
        *outBuffer = (*inBuffer) / max;
        outputAudioHandle.write(outBuffer, FRAME_BUFFER_SIZE);
    }
}