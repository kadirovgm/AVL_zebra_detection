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
    avl::Image image_interpol;
    avl::Image image_threshhold;
    avl::Image image_canny;
    avl::Image image_empty;
    avl::Region reg_1;
    Array<Path> arr;


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
    //avl::SmoothImage_Gauss(image_thresh, atl::NIL, 1.2f, atl::NIL, 2.0f, image_smooth, diagKernelRadiusX,diagKernelRadiusY );
    //avl::SaveImageToJpeg(image_smooth, "out_smooth.jpg", 100, 0);

    //Approximation of the gaussian filter, which can be faster for large kernels.
    avl::SmoothImage_Deriche(image_thresh, atl::NIL, 1.0f, atl::NIL, image_smooth);
    avl::SaveImageToJpeg(image_smooth, "out_smooth.jpg", 100, 0);

    //avl::ImageLocalMaxima(image_smooth, atl::NIL, 0, atl::NIL, atl::NIL, 1.0f, atl::NIL,atl::NIL);
    //avl::SaveImageToJpeg(image_smooth, "out_localmax.jpg", 100, 0);

    //interpolates two images linearly pixel by pixel.
    avl::LerpImages(image_thresh, image_smooth, atl::NIL, 0.5f, image_interpol);
    avl::SaveImageToJpeg(image_interpol, "out_interpol.jpg", 100, 0);

    //canny edge detection
    avl::DetectEdges(image_smooth, atl::NIL, EdgeFilter::Type::Canny, 2.0f, atl::NIL, 15.0f, 5.0f, 0.0f, 1, image_canny,  image_empty);
    avl::SaveImageToJpeg(image_canny, "out_canny.jpg", 100, 0);

    //image to region
    avl::ThresholdToRegion(image_canny, atl::NIL, 128.0f, atl::NIL, 0.0f, reg_1);

    //region contours
    avl::RegionContours(reg_1, RegionContourMode::Type::PixelEdges, RegionConnectivity::Type::EightDirections, arr);

    Pixel red;
    red.Set(245, 16, 16, 0);

    DrawingStyle draw;
    for(auto path : arr)
    {
        avl::Rectangle2D rect; // draw rectangle pryamougolnik
        avl::PathBoundingRectangle(path, BoundingRectangleFeature::Type::MinimalArea, 0.0f, RectangleOrientation::Type::Horizontal, rect, atl::NIL, atl::NIL, atl::NIL);
        if(rect.width>200 && rect.width <370 && rect.height>25)
        {
            avl::DrawRectangle(image_in, rect, atl::NIL, red, draw);//Pixel green green.Set
        }

    }
    avl::SaveImageToJpeg(image_in, "out_out.jpg", 100, 0); //??

    // next draw segment to painting lines of zebra
    //Line2D line;

    //avl::FitLineToPoints_LTE(arr, atl::NIL, 3, atl::NIL,line , atl::NIL, atl::NIL, 5);

    return 0;
}

