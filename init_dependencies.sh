SCRIPT_DIR=$(dirname "$0")

pushd $SCRIPT_DIR

echo "Refreshing submodules"

#Make sure submodules are initialised
git submodule deinit -f --all
if ! git submodule update --init --recursive; then
    echo "Error: could not pull submodules, are you connected to the internet?"
    exit
fi

cd dependencies

echo "Installing opencv"

cd opencv

mkdir build

cd build

OPENCV_BUILD_DIR="`pwd`"

cmake -DCMAKE_INSTALL_PREFIX=$OPENCV_BUILD_DIR ..

make -j 8
make install -j 8

popd
