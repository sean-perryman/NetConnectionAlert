# Network Connection Alert

I created this project because I need to use a mobile hotspot for my network connection, and those things are not terribly reliable. Often times I'll need to reset my network connection or the device itself to get back online.

In my line of work (remote technical support agent), and specifically my shift (5pm - 12am PST), there are often long periods with no activity.  While my screen does auto refresh, I might be reading a book or watching TV or something waiting for a ticket to come in. My only indicator if my network connection is down was when the auto-refreshing ticket page would error out without the internet connection.

This program will monitor a remote web address every two seconds, and after a few successive failures it will turn the normally green indicator red and start beeping every two seconds while the failure is happening. Once this condition is corrected, the visual indicator returns to green and the beep stops.

The program relies on SDL2, SDL2_Image, SDL2_Audio, and cURL. I installed each of these on my Mac with Homebrew, and launched/linked them from their installed locations. Here is the clang command I would use to compile this:

clang main.cpp -L/usr/local/Cellar/sdl2/2.0.3/lib \
		-L/usr/local/Cellar/sdl2_image/2.0.1_1/lib \
		-L/usr/local/Cellar/sdl2_mixer/2.0.1/lib \
		-L/usr/local/opt/curl/lib \
		-lSDL2 -lSDL2_mixer -lSDL2_image -lcurl -lc++

If you'd like to add anything to this, feel free!
