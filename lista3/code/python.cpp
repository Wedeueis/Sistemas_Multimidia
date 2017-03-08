#include <Python.h>

int main(int argc, char *argv[]) {
	Py_SetProgramName(argv[0]);
	Py_Initialize();
		from scipy.io.wavfile import read
		import matplotlib.pyplot as plt
		import os
		import sys

		def main():
			if len(sys.argv) < 2:
				print "Usage: plot_audio <audio>"

				return -1
			audio = read(sys.argv[1])    
			data = audio[1]
			plt.plot(data)
			plt.ylabel("Amplitude")
			plt.xlabel("Time")
			# set the title
			plt.title(os.path.basename(sys.argv[1]))
			# display the plot
			plt.show()


		if __name__ == "__main__":
			main()
	Py_Finalize();
	return 0;
}