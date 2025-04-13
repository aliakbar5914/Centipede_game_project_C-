# Centipede Arcade Game (C++ & SFML)

A simplified recreation of the classic **Centipede** arcade game, built using **C++** and the **SFML** graphics library. This project brings the retro gameplay to life with modern programming techniques and visuals.

---

## Gameplay Overview

- Control a **fighter** at the bottom of the screen.
- Shoot down a **multi-segmented centipede** coming from the top.
- Avoid or destroy **mushrooms** blocking your path.
- Survive attacks from **poisonous mushrooms**, **scorpions**, and **other enemies** (if bonus features implemented).
- Advance through levels with **increasing difficulty**.

---

## Features Implemented

- Player movement within a bounded area (arrow keys).
- Bullet firing using the Spacebar.
- Collision detection:
  - Bullets vs. Centipede
  - Bullets vs. Mushrooms
  - Player vs. Enemies
- Centipede behavior:
  - Movement, splitting, color-changing heads.
- Mushrooms:
  - Spawned at random locations.
  - Require two shots to destroy.
- Poisonous mushrooms:
  - Appear in player area after specific events.
  - Kill the player on contact.
- **Scoring System:**
  - +1 Point: Destroy mushroom
  - +10 Points: Destroy centipede body
  - +20 Points: Destroy centipede head
-  Level progression:
  - Faster enemies and different head colors as difficulty increases.

---

## Additional Mechanics

- Game over on contact with centipede or poisonous mushrooms.
- Centipede speed doubles in each new level.
- Mushrooms affect centipede descent speed and direction.

---

## Technologies Used

- **C++**
- **SFML (Simple and Fast Multimedia Library)**
- **Modular Functions**
- **Procedural & Event-based Programming**

---

