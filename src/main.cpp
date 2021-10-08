#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cout << "Usage: bin/out <path to video file>" << std::endl;
		return -1;
	}

	// Frame for video capture
	cv::Mat frame;
	// Open video to capture
	cv::VideoCapture vidcap(argv[1]);
	// The filename for updating
	char temp_vid[10];
	// The command string
	char cmd[512];
	// VideoCapture fps
	int fps = vidcap.get(cv::CAP_PROP_FPS);

	// Switching index to update the background
	int i = 0;

	// Get the current working directory
	char cwd[256];
	getcwd(cwd, sizeof(cwd));

	// Loop through video
	while (1) {
		// Read the video
		vidcap >> frame;
		i = (++i) % 2;

		std::cout << "hello" << std::endl;

		if (frame.empty()) {
			// Reset if video is done
			vidcap.set(cv::CAP_PROP_POS_AVI_RATIO, 0);
		} else {
			// Write the frame to video
			std::sprintf(temp_vid, "flip%d.jpg", i);
			cv::imwrite(temp_vid, frame);

			// Update the background
			std::sprintf(cmd, "osascript -e 'tell app \"Finder\" to set desktop picture to POSIX file \"%s/%s\"'", cwd, temp_vid);
			system(cmd);
		}
	}

	return 0;
}
