A real-time OpenCV C++ application that turns a printed marker into a goalkeeper controller. The camera detects the marker, maps its center position to a glove on screen, and the player moves the marker to catch falling balls. Each successful save increments the score. Press ESC in the camera window to quit.



The program runs on windows using the MSVC compiler.



The program requires an OpenCV download, version 4 preferably, a standard C++ toolchain found on for example the Visual Studio Code application, a cmake download, a git download(for easy installation of OpenCV) and finally a vcpkg download.



Commands:

Check for vcpkg installation: $env:VCPKG\_ROOT="$env:USERPROFILE\\vcpkg"

&#x09;			\& "$env:VCPKG\_ROOT\\vcpkg.exe" version

Configure for vcpkg: cmake -S . -B build `

&#x09;		-DCMAKE\_TOOLCHAIN\_FILE="$env:VCPKG\_ROOT\\scripts\\buildsystems\\vcpkg.cmake"

Build and Run: cmake --build build --config Debug

.\\build\\Debug\\camera\_grab.exe



The project requires a printer out copy or a picture of opencvs marker number 25. Low lighting is perferred when running the project as the conditions for recognizing the marker are strict.



To reproduce the demonstration shown during the presentation, make sure all four corners of the marker are visible in the camera popout and direct the markers center to the bottom of the screen and catch the balls moving down. The balls will only be catchable when reaching 85% of the way down.

