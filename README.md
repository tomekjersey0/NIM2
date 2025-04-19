# NIM2

> The multiplayer NIM game that had to be made.

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

Long ago, I played Twenty-One with Leah Cannard. She beat me many times. Each loss only fueled my obsession — how could I win?

Eventually, I caved and searched for the strategy: **go second and say multiples of four.** The game was solved. But while searching, I stumbled across something else.

A new game.

At first, I thought little of it. But something about its structure, its mechanics, its *vibe*... pulled me back. I studied it, practiced it, mastered it. I played with friends, strangers, family. I needed more.

But online? **Nothing.**

So I decided: *If no one else will make the multiplayer version, I will.*

And that game?

It goes by the name of:

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

- Test windows with selectable focus
- Easy window management system
- Switchable `INTERACTING` and `MOVING` modes (WIP)
- `RipplePrint` objects (color, looping)
- `RippleLists` & `RippleItems` (vertical & horizontal support)

---

## 🚧 Planned Features

- Online multiplayer  
- Simple download & play experience  
- Likely peer-to-peer hosting (no one's cheating in NIM anyway)

---

## 🧱 Building with CMake

### Prerequisites

- CMake
- MinGW (with `g++`)
- `cmake` and `g++.exe` in your `PATH`

### Build & Run

From the project root:

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
./build/NIM2.exe
```
For a release version
```bash
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/NIM2.exe
```
To clean the build
```bash
rmdir /S /Q build   # Windows
rm -rf build         # Linux/macOS
```
## 🐛 Debugging (Windows)
