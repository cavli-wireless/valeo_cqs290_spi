# Compile The Application
## 1. Standalone Build

- Run *cross_compile.sh* shell script

```sh
./cross_compile.sh
```

## 2. Build with Android

- Copy/Clone the sample application to *android_source/external*
directory

```sh
cd android_source
source build/envsetup.sh
lunch qssi-userdebug
make cavli-hello
```
