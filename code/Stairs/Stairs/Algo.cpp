#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    //-----------------get image file-------------------
    CommandLineParser parser(argc, argv, "{@input | stair_00.jpg | input image}");
    Mat img = imread(samples::findFile(parser.get<String>("@input")));
    
    if (img.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }


    imshow("Original", img);

    //--------------Apply Gaussian blur to get good results-------------
    GaussianBlur(img, img, Size(5, 5), 0, 0);

    imshow("Gaussian blur", img);

    Mat canny_img, res_img, Hough_img;

    //--------------Apply Canny filter to detect the edges--------------
    Canny(img, canny_img, 80, 240, 3);

    cvtColor(canny_img, res_img, cv::COLOR_GRAY2BGR);
    cvtColor(canny_img, Hough_img, cv::COLOR_GRAY2BGR);

    imshow("Canny filter", canny_img);

    vector<int> lines_y;
    vector<Vec4i> lines;

    //--------------Apply Hough filter to detect the lines-------------- 
    HoughLinesP(canny_img, lines, 1, CV_PI / 180, 30, 40, 5);

    for (size_t i = 1; i < lines.size(); i++)
    {
        //-------------Removal of vertical HoughLines----------------
        if (abs(lines[i][1] - lines[i][3]) < 20)
        {
            Vec4i l = lines[i];
            line(Hough_img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, cv::LINE_AA);
        }
    }

    imshow("Hough filter", Hough_img);


    //--------------algorithm approach--------------
    Vec4i l = lines[0];
    line(res_img, Point(0, l[1]), Point(img.cols, l[1]), Scalar(0, 0, 255), 3, cv::LINE_AA);
    lines_y.push_back(l[1]);

    bool check = true;
    int stair_counter = 1;

    for (size_t i = 1; i < lines.size(); i++)
    {
        //-------------Removal of vertical HoughLines----------------
        if (abs(lines[i][1] - lines[i][3]) < 23) {

            Vec4i l = lines[i];
            for (int m : lines_y)
            {
                if (abs(m - l[1]) < 20)
                    check = false;

            }
            if (check == true)
            {
                line(res_img, Point(0, l[1]), Point(img.cols, l[1]), Scalar(0, 0, 255), 3, cv::LINE_AA);
                lines_y.push_back(l[1]);
                stair_counter++;
            }
            check = true;

        }

    }

    putText(res_img, "c:" + to_string(stair_counter), Point(40, 60), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 255, 0), 2);
    
    imshow("detected lines", res_img);
    
    waitKey(0);
    return 0;
}
