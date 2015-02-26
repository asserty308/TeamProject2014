TeamProject2014
=================

AlphaStrike is a top down arena space shooter for two to four players over a local network or the internet.
To test the game, please follow these steps:

1) Start the server located in "TeamProject2014/Project/Binaries/Server" and complete the following prompts. 
   Recommended Settings are:
   
   Port:        8888
   
   Tickrate:    16
   
   Playercount: value from 2 to 4
   
   Round limit: odd number from 3 to 31
   
   mapID:       1
   

2) Start a client located in "TeamProject2014/Project/Binaries/Client". Press Enter and proceed.
  Choose a name and the serverport you gave to the server. If you want to play on one machine,
  choose 127.0.0.1 as Server IP, or else, the IP of the Machine the server runs on. At last,
  choose a client port and press enter.
  
3) Repeate step 2) with different (!) client ports each time until the number of connecting clients
   is equal to the playercount you specified when starting the server. The game will automatically
   start. 
   
4) To end the game either press crtl-c in the server or play the match until someone wins. Enjoy!
