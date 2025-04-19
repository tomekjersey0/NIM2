# NIM2

---

## 🎮 How to Play

1. Go to **[Releases](https://github.com/tomekjersey0/NIM2/releases)**  
2. Download the latest `.exe`  
3. Run it!

---

## 🎛 Controls

- `hjkl` or arrow keys — move  
- `Enter` — select  
- `Escape` — deselect  
- `+/-` — resize screen  
- `q` — quit  

---

## 📜 Lore

###### Long ago, I played twenty-one with Leah Cannard. She beat me many times, with each attempted game and loss, my grit growing stronger on its mission to discover how on earth I was supposed to win. After some time, I finally broke down and looked up the strategy for winning so frustratingly often. Quite simply, it was always to go second and say multiples of four; the game was solved. Upon searching for this game, of twenty-one, I stumbled upon a different game.
 ###### I didn't think much about this game, but the thought of its puzzling pieces intrigued me. Days later, I returned to the article I first spotted it on, and sought to learn the art of this game. So I did. I practiced long and hard, and before long nobody could live up to me in my mastery of the game. I played every one I could: went out at night to meet people I didn't know; played on call with people I've barely met; and showed the game to my family, and my closest friends. But after a while, it wasn't enough; I needed more. So I set to the internet once again to find any sort of multiplayer version of the game I could find - There was none. And so my task became clear, and it arose: I must create the multiplayer version, for there is none, and there must be.
 ###### What is the name of this wondrous game, you may ask? <br>It goes by the name of:

## ✨ NIM2

> Why "2"?  
> The 0th Nim was a test (no `curses`).  
> The 1st was too tied to the 0th.  
> So now... comes NIM2.

---

## ❓ What is this?

**NIM** – The coolest game ever.  

---

## 🛠️ Current Features

So far, not much, but I'll add them to this list as the project goes on
 * Test windows, with selectable windows that can be switched between
 * Super easy (and only getting easier) window management system
 * Windows can be switched between INTERACTING and MOVING modes (function of which to be implemented)
 * RipplePrint objects, with color and looping
 * RippleLists and RippleItems, which support horizontal and vertical lists of ripples (selectability not yet implemented)

---

## 🚧 Planned Features

From when I was looking online, there didn't seem to be any functional multiplayer online versions of NIM for people to play,
 so my goal is to eventually make it possible to easily download this game as an app (probably just on computers for now),
 and play with someone else on the internet. Will it be player hosted? Most likely, as long as I figure out a good way to do that.
 (No ones gonna cheat in Nim of all things, anyway. )

---

## 🧱 Building with CMake

### Prerequisites

- CMake
- MinGW (with `g++`)
- `cmake` and `g++.exe` in your `PATH`
- vcpkg

### Install vcpkg

#### On Windows:
1. Clone the vcpkg repository:
   ```bash
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   ```
2. Bootstrap vcpkg
```bash
bootstrap-vcpkg.bat
```
3. Add vcpkg to your system `PATH` (optional):
- Add the path to the `vcpkg` executable (e.g., `C:/vcpkg`) to your system's `PATH.`

#### On Linux:
Don't use vcpkg as it's seems to have trouble on linux. Instead install ncurses natively:
1. Install `ncurses`:
```bash
sudo apt install libncurses5-dev libncursesw5-dev
```

<hr>

### Build & Run
From the project root:

#### Windows
```bash
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build build
```
For a release version:
```bash
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build build --config Release
```

To clean the build:
```bash
rmdir /S /Q build   # Windows
rm -rf build         # Linux/macOS
```
<hr>

### 🐛 Debugging (Windows)

Set Up
1. Install MSYS2
2. Update Repeatedly:
```bash
pacman -Syu
```
3. Install gdb:
```bash
pacman -S mingw-w64-x86_64-gdb
```
4. Ensure the `.vscode` folder is up to date, then press `F5` to debug.