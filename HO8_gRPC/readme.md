#Terminal (Ctrl+`)


## Cloned/Moved
1. Linking the vcpkg folder to VS

cd vcpkg

./bootstrap-vcpkg.bat

./vcpkg integrate install



## First time install or No vcpkg folder found
1. Creating vcpkg subfolder

git clone https://github.com/microsoft/vcpkg

cd vcpkg


2. Connecting VS to Vcpkg installations

./bootstrap-vcpkg.bat

./vcpkg integrate install


3. Installing new packages to vcpkg directory
#### [For HO8]

./vcpkg install grpc

#### [For HO7]

./vcpkg install glfw3:x64-windows

./vcpkg install imgui[core,glfw-binding,opengl3-binding]:x64-windows




4. Restart VS & Add to dependencies:
#### [For HO7]

opengl32.lib

glfw3dll.lib