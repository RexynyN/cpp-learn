#include <iostream>
#include <filesystem>

#include <opencv2/opencv.hpp>


using namespace std; 
namespace fs = filesystem; 
using namespace cv;

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



int main (int argc, char** argv) {
    if (argc < 3) {
        cout << "É necessário os argumentos <PATH> <MAX-FRAMES>" << endl;
    }




    
}


