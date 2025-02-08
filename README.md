## How to Play!
* Go to Releases and click on the latest one
* Scroll Down and download the exe
* Runit

## Controls
* hjkl or left down up and right arrow keys to move
* Enter to select
* Escape to deselect
* +/- to resize the screen
* q to quit

#### Lore
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

## Debugging

Best to use gdb (GNU Debugger)

### Set Up
1. Install MSYS2
2. Update Repeatedly
```
pacman -Syu
```
3. Install gdb
```
pacman -S mingw-w64-x86_64-gdb
```
4. Ensure the .vscode folder it up to date, F5 to use

<hr>

## Usage

### Prerequisites
* make
* mingw g++
* C:\PathToBinFolderOfYourMakeInstallation\ in your path
* C:\MinGW\bin (or wherever mingw/bin is on your device) in your path


### Execution / Development
make commands include:
* `make build` compiles a dll dependant executable
* `make run` compiles and runs a new debug version
* `make clean` deletes all exeutables and removes all previously compiled objs
* `make all` combines clean, build and run
* `make release` compiles self contained optimized executable

To run with:
    Git-bash -> `make -f Makefile [command]`
    Powershell -> `make -f Makefile-ps [command]`

**All external libraries required by the program are already included in this project**

Good Luck





