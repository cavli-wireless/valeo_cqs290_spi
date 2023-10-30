# Download NDK

if [[ ! -d android-ndk-r26b ]]
then
wget https://dl.google.com/android/repository/android-ndk-r26b-linux.zip
unzip android-ndk-r26b-linux.zip
fi

# Only choose one of these, depending on your build machine...
export TOOLCHAIN=android-ndk-r26b/toolchains/llvm/prebuilt/linux-x86_64

# Only choose one of these, depending on your device...
export TARGET=aarch64-linux-android

# Set this to your minSdkVersion.
export API=26

# Build.
make \
    CC=$TOOLCHAIN/bin/$TARGET$API-clang \
    AR=$TOOLCHAIN/bin/llvm-ar \
    RANLIB=$TOOLCHAIN/bin/llvm-ranlib \
