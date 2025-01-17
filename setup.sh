export MSYS_NO_PATHCONV=1

cd ev3dev-c/source/ev3/

make
sudo make install
make shared
sudo make shared-install