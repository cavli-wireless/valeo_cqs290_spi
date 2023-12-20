- [Compile The Application](#compile-the-application)
  - [1. Standalone Build](#1-standalone-build)
  - [2. Build with Android](#2-build-with-android)
- [How to add init service](#how-to-add-init-service)
  - [1. Prepare your C application](#1-prepare-your-c-application)
  - [2. Add C applications and init service to device makefile](#2-add-c-applications-and-init-service-to-device-makefile)
  - [3. Add cavli-hello service to target init rc](#3-add-cavli-hello-service-to-target-init-rc)
  - [4. Add Selinux permission for cavli-hello](#4-add-selinux-permission-for-cavli-hello)
  - [5. Compile Android OS](#5-compile-android-os)
  - [6. Flash images via fastboot](#6-flash-images-via-fastboot)
  - [7. Tes cavli-hello application in development](#7-tes-cavli-hello-application-in-development)

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


# How to add init service

## 1. Prepare your C application
- Compile your *c application* and get the binary
- Example your *c application* is: ```cavli-hello``` and put it at ```device/qcom/bengal_2w/cavli-hello```
- Create the new file with the below content, and put it at ```device/qcom/bengal_2w/cavli-hello.rc```

```
service cavli-hello /vendor/bin/cavli-hello
    class core animation
    seclabel u:r:init:s0
    user root
    group root
    task_profiles HighPerformance
```

## 2. Add C applications and init service to device makefile

- Add below to file ```device/qcom/bengal_2w/bengal_2w.mk```

```mk
PRODUCT_COPY_FILES += \
    device/qcom/bengal_2w/cavli-hello:$(TARGET_COPY_OUT_VENDOR)/bin/cavli-hello \
    device/qcom/bengal_2w/cavli-hello.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/cavli-hello.rc
```

## 3. Add cavli-hello service to target init rc
- Open file ```device/qcom/bengal_2w/init.target.rc``` and add below content

```
 on early-fs
    start cavli-hello
```

## 4. Add Selinux permission for cavli-hello

- Add below content to file ```device/qcom/sepolicy/generic/private/file_contexts```

```
/vendor/bin/cavli-hello             u:object_r:cavli-hello_exec:s0
```

- Create new file ```device/qcom/sepolicy/generic/private/cavli-hello.te```

```
type cavli-hello, domain;
type cavli-hello_exec, vendor_file_type, exec_type, file_type;

init_daemon_domain(cavli-hello);
```

- Add below content to file ```device/qcom/sepolicy/generic/private/service.te```

```
type cavli-hello_service,                 service_manager_type;
```

- Add below content to file ```device/qcom/sepolicy/generic/private/service_contexts```

```
cavli-hello     u:object_r:cavli-hello_service:s0
```

## 5. Compile Android OS
- Build ```bengal_2w```

```sh
cd $WORK_SPACE/cqs290/bengal_2w
./build_bengal_2w.sh
```

- Build ```qssi``` and generate *super.img*

```sh
cd $WORK_SPACE/cqs290/qssi_12
./build_qssi.sh
./generate_super.sh
```

## 6. Flash images via fastboot

```sh
cd $WORK_SPACE/cqs290/bengal_2w
fastboot flash abl out/target/product/bengal_2w/abl_ecc.elf
fastboot flash boot out/target/product/bengal_2w/boot.img
fastboot flash dtbo out/target/product/bengal_2w/dtbo.img
fastboot flash metadata out/target/product/bengal_2w/metadata.img
fastboot flash persist out/target/product/bengal_2w/persist.img
fastboot flash recovery out/target/product/bengal_2w/recovery.img
fastboot flash super out/target/product/bengal_2w/super.img
fastboot flash userdata out/target/product/bengal_2w/userdata.img
fastboot flash vbmeta out/target/product/bengal_2w/vbmeta.img
fastboot flash vbmeta_system out/target/product/bengal_2w/vbmeta_system.img
fastboot erase misc
```

## 7. Tes cavli-hello application in development

- This step only needs to be done once.

```sh
adb root
adb disable-verity
adb root
```

- This step must be done every time the board reboots.

```sh
adb root
adb remount
```

- Push *cavli-hello* to the board to debug

```sh
adb push cavli-hello /vendor/bin/cavli-hello
```

- Run test *cavli-hello*

```sh
adb shell cavli-hello
```
