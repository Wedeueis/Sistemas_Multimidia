from scipy.io.wavfile import read
import matplotlib.pyplot as plt
import os
import sys

def plotwave(filename, title):
    audio = read(filename)    
    data = audio[1]
    plt.plot(data)
    plt.ylabel("Amplitude")
    plt.xlabel("Time")
    # set the title
    plt.title(title)
    # display the plot
    plt.show()

plotwave("dont_speak-no_doubt.wav","3.6 input")