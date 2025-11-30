# Terminal Escape Game (C)

🎮 **Description**  
This is a terminal-based game where the player, represented by `O`, must reach the exit `E` without being caught by guards (`>`, `<`, `^`, `v`). Walls (`#`) block movement, and guards can see the player in straight lines.

---

## 🕹️ How to Play

- Player character: `O`  
- Guard characters: `>`, `<`, `^`, `v`  
- Walls: `#`  
- Exit: `E`  

### Controls
- `W` → Up  
- `A` → Left  
- `S` → Down  
- `D` → Right  
- `Q` → Quit the game  

⚠️ If you enter a guard's line of sight or step on a guard, the game ends.

---

## 💻 Compile and Run

1. Save the file as `real_oyun.c`  
2. Compile in terminal or command prompt:  

```bash
gcc real_oyun.c -o real_oyun
To run the game:
./real_oyun
