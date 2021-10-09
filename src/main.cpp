#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char* argv[]) {
	// Check if correct usage
	if (argc != 2) {
		std::cout << "Usage: bin/out <path to video file>" << std::endl;
		return -1;
	}

	// Frame for video capture
	cv::Mat frame;
	// Open video to capture
	cv::VideoCapture vidcap(argv[1]);
	// The filename for updating
	char temp_vid[20];
	// The command string
	char cmd[512];
	// VideoCapture fps
	int fps = vidcap.get(cv::CAP_PROP_FPS);

	// Switching index to update the background
	int i = 0;
	int framelen = 0;

	// Get the current working directory
	char cwd[256];
	getcwd(cwd, sizeof(cwd));

	// Create video frame folder
	system("mkdir -p flips; cd flips");

	// Loop through video
	std::cout << "Flattening video...";
	while (1) {
		// Read the video
		vidcap >> frame;
		i++;
		framelen++;

		if (frame.empty()) {
			break;
		} else {
			// Write the frame to video
			std::sprintf(temp_vid, "flips/flip%d.jpg", i);
			cv::imwrite(temp_vid, frame);
		}
	}

	std::cout << "\rFinished flattening video." << std::endl;
	std::cout << "Starting animation." << std::endl;

	i = 0;
	while (1) {
		i = (++i) % framelen;
		// Update the background
		std::sprintf(temp_vid, "flip%d.jpg", i);
		std::sprintf(cmd, "osascript -e 'tell app \"Finder\" to set desktop picture to POSIX file \"%s/flips/%s\"'", cwd, temp_vid);
		system(cmd);
	}

	return 0;
}
