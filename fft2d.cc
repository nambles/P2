// Distributed two-dimensional Discrete FFT transform
// Edward Lee

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>


#include "Complex.h"
#include "InputImage.h"

constexpr unsigned int NUMTHREADS = 4;

using namespace std;

//undergrad students can assume NUMTHREADS will evenly divide the number of rows in tested images
//graduate students should assume NUMTHREADS will not always evenly divide the number of rows in tested images.
// I will test with a different image than the one given



void Transform1D(Complex* h, int w, Complex* H)
{
    // Implement a simple 1-d DFT using the double summation equation
    // given in the assignment handout.  h is the time-domain input
    // data, w is the width (N), and H is the output array.
}



void Transform2D(const char* inputFN)
{
	// Do the 2D transform here.
	// 1) Use the InputImage object to read in the Tower.txt file and
	//    find the width/height of the input image.
	// 2) Create a vector of complex objects of size width * height to hold
	//    values calculated
	// 3) Do the individual 1D transforms on the rows assigned to each thread
	// 4) Force each thread to wait until all threads have completed their row calculations
	//    prior to starting column calculations
	// 5) Perform column calculations
	// 6) Wait for all column calculations to complete
	// 7) Use SaveImageData() to output the final results
	InputImage image(inputFN);
	// Create the helper object for reading the image
	// Step (1) in the comments is the line above.
	// Your code here, steps 2-7
    vector<Complex> ComplexVector (image.GetWidth() * image.GetHeight());
    vector<thread> ThreadVector(NUMTHREADS);
    Complex* inputSequence = image.GetImageData();
    Complex* OutputSequence = image.GetImageData();
    Complex* SectionedSequence;
    int ElementsPerSection = (image.GetWidth() * image.GetHeight()) / NUMTHREADS;
    for (int i = 0; i < NUMTHREADS; i++)
    {
        for (int j = 0; j < ElementsPerSection; j++)
        {
            SectionedSequence[j] = inputSequence[i*ElementsPerSection + j];
        }
        ThreadVector.push_back(std::thread(Transform1D(SectionedSequence, image.GetWidth(),  )));
    }









}

int main(int argc, char** argv)
{
	string fn("../Tower.txt"); // default file name
	if (argc > 1) fn = string(argv[1]);  // if name specified on cmd line
	Transform2D(fn.c_str()); // Perform the transform.
}



