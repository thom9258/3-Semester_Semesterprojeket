#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>  
#define M_PI 3.1415926535

float goertzel_mag(int numSamples, int TARGET_FREQ, unsigned int SAMPLING_RATE, const sf::Int16* data) {
	int k, i;
	float floatnumSamples;
	float omega, sine, cosine, coeff, q0, q1, q2, magnitude, real, imag;

	float scalingFactor = numSamples / 2.0;

	floatnumSamples = (float)numSamples;
	k = (int)(0.5 + ((floatnumSamples * TARGET_FREQ) / SAMPLING_RATE));
	omega = (2.0 * M_PI * k) / floatnumSamples;
	sine = sin(omega);
	cosine = cos(omega);
	coeff = 2.0 * cosine;
	q0 = 0;
	q1 = 0;
	q2 = 0;

	for (i = 0; i < numSamples; i++) {
		q0 = coeff * q1 - q2 + data[i];
		q2 = q1;
		q1 = q0;
	}
	real = (q1 - q2 * cosine) / scalingFactor;
	imag = (q2 * sine) / scalingFactor;

	magnitude = sqrtf(pow(real, 2) + pow(imag, 2));
	
	return magnitude;
}

int record()
{
	//Definition of DTMF tones
	std::vector<int> EN = { 1209, 697 };
	std::vector<int> TO = { 1336, 697 };
	std::vector<int> TRE = { 1477, 697 };
	std::vector<int> A = { 1633, 697 };
	std::vector<int> FIRE = { 1209, 770 };
	std::vector<int> FEM = { 1336, 770 };
	std::vector<int> SEKS = { 1477, 770 };
	std::vector<int> B = { 1633, 770 };
	std::vector<int> SYV = { 1209, 852 };
	std::vector<int> OTTE = { 1336, 852 };
	std::vector<int> NI = { 1477, 852 };
	std::vector<int> C = { 1633, 852 };
	std::vector<int> STJERNE = { 1209, 941 };
	std::vector<int> NUL = { 1336, 941 };
	std::vector<int> HAVELAAGE = { 1447, 941 };
	std::vector<int> D = { 1633, 941 };

	//Check if recorder is available
	if (!sf::SoundBufferRecorder::isAvailable())
	{
		std::cerr << "Recorder not available!" << std::endl;
	}
	sf::SoundBufferRecorder recorder;

	//Open window
	sf::RenderWindow window(sf::VideoMode(200, 100), "Chat");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}

			//Press ESC to close window
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
				break;
			}

			//Press R to start recording
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				std::cout << "recording started" << std::endl;
				recorder.start();
			}

			//Press S to stop recording and save a .ogg sound file of recorded data
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				std::cout << "recording ended" << std::endl;
				recorder.stop();
				const sf::SoundBuffer& buffer = recorder.getBuffer();
				buffer.saveToFile("lyd.ogg");
			}	

			//Press A to analyze the recorded data using Goertzler algorithm
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				std::cout << "Analyzing" << std::endl;
				const sf::SoundBuffer& buffer = recorder.getBuffer();
				unsigned int SAMPLE_RATE = recorder.getSampleRate();
				const sf::Int16* samples = buffer.getSamples();
				std::size_t count = buffer.getSampleCount();
				
				int DTMFfreq[] = {697, 770, 852, 941, 1209, 1336, 1477, 1633};
				float magnitudes[8], magnitudes2[8];

				for (int i = 0; i < 8; i++) {
					std::cout << "Frequency:" << DTMFfreq[i] << ":" << " ";
					std::cout << "Goertzel mag:" << goertzel_mag(count, DTMFfreq[i], SAMPLE_RATE, samples) << std::endl;
					magnitudes[i] = goertzel_mag(count, DTMFfreq[i], SAMPLE_RATE, samples);
					magnitudes2[i] = goertzel_mag(count, DTMFfreq[i], SAMPLE_RATE, samples);

				}

				std::sort(magnitudes, magnitudes + 8);

				//This outputs the sorted magnitudes lowest to highest (DEBUGGING)
				//for (int i = 0; i < 8; i++) {
				//	std::cout << magnitudes[i] << ", ";
				//}
				//std::cout << std::endl;
				
				//We only want the two highest magnitudes so here we define them as max1 and max2
				float max1, max2;
				max1 = magnitudes[6];
				max2 = magnitudes[7];

				//Here we find the positions of the highest magnitudes 
				int pos1, pos2;
				for (int i = 0; i < 8; i++) {
					if (magnitudes2[i] == max1) {
						pos1 = i;
					}
					if (magnitudes2[i] == max2) {
						pos2 = i;
					}
				}

				//Here we make a sorted array of the corresponding DTMF frequency from the position of the highest magnitudes
				int sortFreq[] = { DTMFfreq[pos2], DTMFfreq[pos1] };
				std::sort(sortFreq, sortFreq + 2);
				//std::reverse(sortFreq, sortFreq + 2);

				//Error message if DTMF tone wasn't recognized
			/*	if(!sortFreq[1]<=1209){
					std::cerr << "Error: Could not recognize DTMF" << std::endl;
					break;
				}*/

				//Debugging
				//std::cout << "SKAL VAERE HOEJ " << sortFreq[1] << std::endl;
				//std::cout << "SKAL VAERE LAV " << sortFreq[0] << std::endl;

				//Now we check the first frequency in the DTMF tone to see which column it is in
				int x1 = 0, x2 = 0, x3 = 0;
				switch (sortFreq[1]) {
				case 1209:
					x1 = 0b00;
					break;	
				case 1336:
					x1 = 0b01;
					break;
				case 1477:
					x1 = 0b10;
					break;
				case 1633:
					x1 = 0b11;
					break;
				}

				//Now we check the second frequency in the DTMF tone to see which row it is in
				switch (sortFreq[0]) {
				case 697:
					x2 = 0b00;
					break;
				case 770:
					x2 = 0b01;
					break;
				case 852:
					x2 = 0b10;
					break;
				case 941:
					x2 = 0b11;
					break;
				}

				//Now we've identified which tone it is - we convert it into a nipple
				x2 = x2 << 2;
				x3 = x2 | x1;

				//This outputs the corresponding number to which DTMF symbol was recognised
				std::cout << x3 << std::endl;
			}
		}
	}
	return 0;
}

int main() {

	std::thread t1(record);

	t1.join();

	return 0;
}
