if [ ! -d "./build" ]; 
then
    mkdir "build";
fi

cd "./build";
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_GENERATOR_PLATFORM=x64 ..;

if cmake --build .; then
    echo "Cmake build successful."
else
    echo "Cmake build failed."
    exit 1
fi

# TODO(calco): Do the build differently for each compiler etc.
# This will do for now.
cd "..";
if [ ! -d "./build/Debug/assets" ];
then
    mkdir "./build/Debug/assets";
fi

rm -rf ./build/Debug/assets/*;
cp -r ./assets/. ./build/Debug/assets;