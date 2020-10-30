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
    avl::LoadImage("in2.jpg", 0, image_in);
    avl::AverageChannels(image_in, atl::NIL, image_wb);
    avl::SaveImageToJpeg(image_wb, "out_wb.jpg", 100, 0);
    avl::ThresholdImage(image_wb, atl::NIL, 120.0f, atl::NIL, 0.0f, image_thresh);
    avl::SaveImageToJpeg(image_thresh, "out_thresh.jpg", 100, 0);

    return 0;
}

