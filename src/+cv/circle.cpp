/**
 * @file circle.cpp
 * @brief mex interface for circle
 * @author Kota Yamaguchi
 * @date 2012
 */
#include "mexopencv.hpp"
using namespace std;
using namespace cv;

/**
 * Main entry called from Matlab
 * @param nlhs number of left-hand-side arguments
 * @param plhs pointers to mxArrays in the left-hand-side
 * @param nrhs number of right-hand-side arguments
 * @param prhs pointers to mxArrays in the right-hand-side
 */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] )
{
    // Check the number of arguments
    if (nrhs<3 || (nrhs%2)!=1 || nlhs>1)
        mexErrMsgIdAndTxt("mexopencv:error","Wrong number of arguments");

    // Argument vector
    vector<MxArray> rhs(prhs,prhs+nrhs);
    
    // Option processing
    Mat img = rhs[0].toMat();    int radius = rhs[2].toInt();
    Scalar color;
    int thickness=1;
    int lineType=8;
    int shift=0;
    for (int i=3; i<nrhs; i+=2) {
        string key = rhs[i].toString();
        if (key=="Color")
            color = rhs[i+1].toScalar();
        else if (key=="Thickness")
            thickness = rhs[i+1].toInt();
        else if (key=="LineType")
            lineType = (rhs[i+1].isChar()) ?
                LineType[rhs[i+1].toString()] : rhs[i+1].toInt();
        else if (key=="Shift")
            shift = rhs[i+1].toInt();
        else
            mexErrMsgIdAndTxt("mexopencv:error","Unrecognized option");
    }


    if (rhs[1].cols() != 2) 
        mexErrMsgIdAndTxt("mexopencv:error","Points should be two columns matrix");

    mwSize ii = rhs[1].rows();
    for (mwSize i = 0; 
        i < rhs[1].rows(); 
        i = i + 1, ii = ii + 1) 
    {
        // indexing must have been row-major
        Point center = Point(rhs[1].at<int>(i), rhs[1].at<int>(ii));
        // Execute function
        circle(img, center, radius, color, thickness, lineType, shift);
    }
    plhs[0] = MxArray(img);
}
