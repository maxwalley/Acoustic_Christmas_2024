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

echo "Installing wiiuse"

cd wiiuse

mkdir build

cd build

WIIUSE_BUILD_DIR="`pwd`"

cmake .. -DCMAKE_INSTALL_PREFIX=$WIIUSE_BUILD_DIR -DCMAKE_BUILD_TYPE=Release

make wiiuse

popd
