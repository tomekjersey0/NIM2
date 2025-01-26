###### Long ago, I played twenty-one with Leah Cannard. She beat me many times, with each attempted game and loss, my grit growing stronger on its mission to discover how on earth I was supposed to win. After some time, I finally broke down and looked up the strategy for winning so frustratingly often. Quite simply, it was always to go second and say multiples of four; the game was solved. Upon searching for this game, of twenty-one, I stumbled upon a different game.
###### I didn't think much about this game, but the thought of its puzzling pieces intrigued me. Days later, I returned to the article I first spotted it on, and sought to learn the art of this game. So I did. I practiced long and hard, and before long nobody could live up to me in my mastery of the game. I played every one I could: went out at night to meet people I didn't know; played on call with people I've barely met; and showed the game to my family, and my closest friends. But after a while, it wasn't enough; I needed more. So I set to the internet once again to find any sort of multiplayer version of the game I could find - There was none. And so my task became clear, and it arose: I must create the multiplayer version, for there is none, and there must be.
###### What is the name of this wondrous game, you may ask? <br>It goes by the name of:

# NIM2

###### But why, 2? The 0th Nim was just a test and didn't use curses anyway, whilst the 1st Nim was too based on the 0th so it would be very difficult for me to develop. <br> So became, NIM2.

### What is this?

Nim, the coolest game ever.

<hr>

### What are the features?

So far, not much, but I'll add them to this list as the project goes on
* Test windows, with selectable windows that can be switched between
* Super easy (and only getting easier) window management system
* Windows can be switched between INTERACTING and MOVING modes (function of which to be implemented)
* RipplePrint objects, with color and looping
* RippleLists and RippleItems, which support horizontal and vertical lists of ripples (selectability not yet implemented)

<hr>

### What are some of the planned features or possible goal / scope for this project?

From when I was looking online, there didn't seem to be any functional multiplayer online versions of NIM for people to play,
so my goal is to eventually make it possible to easily download this game as an app (probably just on computers for now),
and play with someone else on the internet. Will it be player hosted? Most likely, as long as I figure out a good way to do that.
(No ones gonna cheat in Nim of all things, anyway. )

<hr>

### Advice for debugging

If you wanna debug, you're gonna need gdb for that, so get MSYS2, update it to the max with `pacman -Syu`,
and install gdb. Make sure MSYS is fully updated, so be sure to run `pacman -Syu` a couple of times. Once its updated,
run `pacman -S mingw-w64-x86_64-gdb` to install gdb onto your device. Now you can debug in vscode, bruh! (Make sure **not** to run `pacman -S gdb` as that would download the completely wrong version, and not only will it not work with this **launch.json**, it also won't even work in general. So do **NOT** run that command.)
<br><br>
Mate, then everything should realistically be perfect, leave the repo as it is, don't touch the .vscode folder, and get cracking.
<br><br>
Just make sure you've got the PDCurses libraries compiled and in the right
MinGW folders, and have MinGW in your PATH.
<br><br>
To Debug, press F5 in vscode, and everything should work automatically. If I (or you, which could probably be me), find any issues 
with the process, I'll add the workarounds here

<hr>

### Advice for running the program

Do I look like some 'running c++ files guru' to you? Come on mate, either install make with chocolatey and run 'make' in this directory, or go learn a thing or to about the harsh realities of learning things using your own time and effort in this world. Piss off!
* `make build` to build...
* `make run` to run...
* `make [all]` to do it all!
<br><br>

Before you do that however, you'll most certainly need go download `g++` from `mingw`, and the `pdcurses` library to your system.
<br>
* To get `mingw` and `g++`, just search for it on the internet, and install it on your computer.
* To get `pdcurses`, clone the repo from github at <a href="https://github.com/wmcbrine/PDCurses">https://github.com/wmcbrine/PDCurses</a>, enter the *wincon* folder, do what is said to you in the *README.md*, and move the compiled `pducrses.a` file into the lib folder of your `mingw` installation, and copy `curses.h` from the folder above inside of your curses clone into the include directory (of `mingw`).
* Make sure `mingw` is on your system PATH, by adding to it the path to the include, and bin directories, inside your environment variables settings.
* `mingw` likes its library files to start with the prefix `lib`, so you might want to covert the name of the .a file to `libpdcurses.a` before trying to use it.
* After all this, running make to compile the source code should be nice and easy and doable

Good Luck





