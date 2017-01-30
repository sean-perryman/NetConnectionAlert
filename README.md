# Network Connection Alert

I created this project because I need to use a mobile hotspot for my network connection, and those things are not terribly reliable. Often times I'll need to reset my network connection or the device itself to get back online.

In my line of work (remote technical support agent), and specifically my shift (5pm - 12am PST), there are often long periods with no activity.  While my screen does auto refresh, I might be reading a book or watching TV or something waiting for a ticket to come in. My only indicator if my network connection is down was when the auto-refreshing ticket page would error out without the internet connection.

This program will monitor a remote web address every two seconds, and after a few successive failures it will turn the normally green indicator red and start beeping every two seconds while the failure is happening. Once this condition is corrected, the visual indicator returns to green and the beep stops. 
