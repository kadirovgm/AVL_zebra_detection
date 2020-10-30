#include <iostream>
#include "AVL.h"
#include "STD.h"

using namespace std;
using namespace avl;
using namespace atl;

int main()
{
    avl::Image image_in; //input
    avl::Image image_wb; //wb
    avl::Image image_thresh; //after thresholding
    avl::Image image_smooth; //after gauss smooth

    //Kernel method
    //In machine learning, kernel methods are a class of algorithms for pattern analysis,
    //whose best known member is the support vector machine (SVM).
    int diagKernelRadiusX = 1;
    int diagKernelRadiusY = 1;

    //load image in.jpg
    avl::LoadImage("in.jpg", 0, image_in);
    //Creates a monochromatic image by averaging the input image channels.
    avl::AverageChannels(image_in, atl::NIL, image_wb);
    avl::SaveImageToJpeg(image_wb, "out_wb.jpg", 100, 0);

    //Transforms each pixel value to maximum or minimum depending on whether they belong to the specified range
    avl::ThresholdImage(image_wb, atl::NIL, 200.0f, atl::NIL, 50.0f, image_thresh);
    avl::SaveImageToJpeg(image_thresh, "out_thresh.jpg", 100, 0);

    //Gauss smooth
    avl::SmoothImage_Gauss(image_thresh, atl::NIL, 1.2f, atl::NIL, 2.0f, image_smooth, diagKernelRadiusX,diagKernelRadiusY );
    avl::SaveImageToJpeg(image_smooth, "out_smooth.jpg", 100, 0);

    //end

    return 0;
}

