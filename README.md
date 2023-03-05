# mdPAlib (previously dPAlib)
ModernDebloatedProgrammer'sArsenalLibrary (previously dPAlib). yes, longest name ever.<br><br>

mdPAlib is a PAlib fork that has less bloat, it is much faster, much smaller, and *works on modern devkitarm*. It should be a drop in replacement for PAlib but just remember that if your proyect uses some features that were removed because they were "bloat" then it won't work<br><br>

# Installation guide
Download all the devkitPro nds tools.<br>
Download the latest version. pick from the releases or from the main code.<br>
Extract the folder and rename it to PAlib, put it inside the devkitPro folder (it increases compatibility)<br>
Compile the stupid lib, do make clean and then make.<br>
you got yourself a broken lib.<br>

# Stuff removed:
Mode7<br>
PA_Reco<br>
PA_Graffity<br>
All 8bit or 16bit functions (text and backgrounds)<br>
WiFi<br>
JPEG loading functions.<br>
Any external input exept for the DS pad. (GHControlers, Motion controls)<br>
PA_Gifs
