# NIM2
###### The 0th Nim was just a test, and the 1st Nim was too based on the 0th, that I could never make any progress on it

### What is this?

Nim, the coolest game ever.

### What are the features?

So far, not much, but I'll add them to this list as the project goes on
* Test windows, with selectable (which highlight) windows that can be switched between
* Super easy window management system

### What are some of the planned features or possible goal / scope for this project?

From when I was looking online, there didn't seem to be any functional multiplayer online versions of NIM for people to play,
so my goal is to eventually make it possible to easily download this game as an app (probably just on computers for now),
and play with someone else on the internet. Will it be player hosted? Most likely, as long as I figure out a good way to do that.
(No ones gonna cheat in Nim of all things, anyway. )

<hr>

### Advice for debugging

If you wanna debug, you're gonna need gdb for that, so get MSYS2, update it to the max with `pacman -Syu`,
and install gdb. If that's tricky to do off the top of your head, look it up with AI or the internet.
<br>
Mate, then everything should realistically be perfect, leave the repo as it is, don't touch the .vscode folder, and get cracking.
<br>
Just make sure you've got the PDCurses libraries compiled and in the right
MinGW folders, and have MinGW in your PATH.
<br>
To Debug, press F5 in vscode, and everything should work automatically. If I (or you, which could probably be me), find any issues 
with the process, I'll add the workarounds here

### Advice for running the program

Do I look like some 'running c++ files guru' to you? Come on mate, either install make with chocolatey and run 'make' in this directory, or go learn a thing or to about the harsh realities of learning things using your own time and effort in this world. Piss off!
* `make build` to build...
* `make run` to run...
* `make [all]` to do it all!
<br>
Good Luck





