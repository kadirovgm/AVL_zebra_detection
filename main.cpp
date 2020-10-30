#include <iostream>
#include "AVL.h"

using namespace std;
using namespace avl;
using namespace atl;

int main()
{
    avl::Image image_in;
    avl::Image image_wb;
    avl::Image image_thresh;
    //load image in.jpg
    avl::LoadImage("in.jpg", 0, image_in);
    //Creates a monochromatic image by averaging the input image channels.
    avl::AverageChannels(image_in, atl::NIL, image_wb);
    //save wb image to jpg
    avl::SaveImageToJpeg(image_wb, "out_wb.jpg", 100, 0);
    //Transforms each pixel value to maximum or minimum depending on whether they belong to the specified range
    avl::ThresholdImage(image_wb, atl::NIL, 200.0f, atl::NIL, 50.0f, image_thresh); //
    //save threshhold image to jpg
    avl::SaveImageToJpeg(image_thresh, "out_thresh.jpg", 100, 0);

    return 0;
}

