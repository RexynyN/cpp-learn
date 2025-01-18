sudo apt-get update
sudo apt-get install build-essential cmake unzip pkg-config
sudo apt-get install libjpeg-dev libpng-dev libtiff-dev ffmpeg
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libxvidcore-dev libx264-dev
sudo apt-get install libgtk-3-dev
sudo apt-get install libatlas-base-dev gfortran
cd ~

git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git

#Repare que 4.6.0 é a versão da opencv que será utilizada. Você pode #escrever a versão que melhor te atender, mas lembre-se de que #opencv e opencv contrib devem estar na mesma versão :)
cd opencv && git checkout 4.6.0 && cd ..
cd opencv_contrib && git checkout 4.6.0 && cd ..
cd ~/opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
 -D CMAKE_INSTALL_PREFIX=/usr/local \
 -D INSTALL_PYTHON_EXAMPLES=OFF \
 -D INSTALL_C_EXAMPLES=ON \
 -D OPENCV_ENABLE_NONFREE=ON \
 -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
 -D BUILD_EXAMPLES=ON ..
make -j4
sudo make install