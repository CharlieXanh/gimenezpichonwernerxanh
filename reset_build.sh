#Remake and redo build rep
rm -r build
mkdir build
cd build/
cmake ..
make all
cd ..
