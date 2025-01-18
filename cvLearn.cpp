#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <bitset>
#include <vector>
#include <string>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/img_hash.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
namespace fs = filesystem;
using namespace cv;
using namespace cv::img_hash;
using namespace cv::ml;

void extract_frames(string file, long max_frame, long frame_interval) {
    Mat frame;
    VideoCapture vidcap = VideoCapture(file);
    long time_frame = 0;

    while (time_frame < max_frame) {
        vidcap.set(CAP_PROP_POS_MSEC, time_frame);
        
        bool success = vidcap.read(frame);
        if (!success) {
            cout << "Acabou" << endl;
            break;
        }
   

        imwrite("./images/frame-" + to_string(time_frame) + ".jpg", frame);
        time_frame += frame_interval;
    }
}

void worsen_resolution(Mat image, const float factor, const string name) {
    Mat out; 
    resize(image, out, Size(), factor, factor, INTER_LANCZOS4);
    imwrite(name, out);
}

vector<string> listdir(const string& directoryPath) {
    vector<string> filePaths;
    try {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry.status()))
                filePaths.push_back(fs::absolute(entry.path()).string());
        }
    } catch (const fs::filesystem_error& e) {
        cerr << e.what() << endl;
    }

    return filePaths;
}


void show_hash(const string path) {
    // AverageHash
    // BlockMeanHash
    // ColorMomentHash
    // ImgHashBase
    // MarrHildrethHash
    // PHash
    // RadialVarianceHash
    // vector<string> files = listdir(path);
    
    Ptr<PHash> phasher = PHash::create();
    Mat hash; 
    // for (const auto& file : files) {
        Mat imagem = imread(path, IMREAD_COLOR);
        phasher->compute(imagem, hash);


        for (int i = 0; i < hash.cols; ++i) {
            cout << static_cast<int>(hash.at<uchar>(0, i)) << endl;
        }
        cout << endl;

        // To hex
        stringstream hexString;
        for (int i = 0; i < hash.cols; ++i) {
            hexString << hex << setw(2) << setfill('0') 
                    << static_cast<int>(hash.at<uchar>(0, i));
        }

        // Exibir o hash em hexadecimal
        string hex = hexString.str();
        cout << "PHash Hexadecimal: " << hex << endl;

        // Hex to Long
        unsigned long long decimalValue = stoull(hex, nullptr, 16);
        cout << "PHash Decimal: " << decimalValue << endl;
    // }
}

void show_image(Mat image) {
    namedWindow("Minha Imagem", WINDOW_NORMAL);
    resizeWindow("Minha Imagem", 600,600);

    imshow("Minha Imagem", image);
    waitKey(0);
}


// Function to extract ORB features from an image
Mat extractORBFeatures(const Mat& image) {
    Ptr<ORB> orb = ORB::create();
    vector<KeyPoint> keypoints;
    Mat descriptors;
    orb->detectAndCompute(image, noArray(), keypoints, descriptors);
    return descriptors;
}

int main(int argc, char** argv) {
    string path = "img.jpg";
    cout << "Bonk" << endl;
    // extract_frames(path, 10000000000, 700);


    show_hash(argv[1]);

    
}
