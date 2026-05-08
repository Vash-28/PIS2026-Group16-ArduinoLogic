# Clash of Olympus - Arduino Game Logic

A custom Arduino-powered interactive tabletop game inspired by Greek mythology, combining physical gameplay, embedded systems, LEDs, LCD displays, sound feedback, and real-time game logic.

This repository contains the complete Arduino logic powering **Clash of Olympus**, a mythology-themed competitive strategy game designed for children aged 5–8 as part of the DES206 Prototyping Interactive Systems end-semester project.

---

# Team Members

* Mayank Yadav (2024343)
* Shanthini Muralidhar (2024520)
* Urvashi Gupta (2024593)

---

# Game Overview

Players battle as champions chosen by the gods:

* ⚡ Zeus
* 🌊 Poseidon
* 🔥 Hades

The game is based on a mythology-themed variation of Rock-Paper-Scissors where:

* Zeus defeats Hades
* Hades defeats Poseidon
* Poseidon defeats Zeus

Players damage each other’s temples after every victory, while special powers and LED indicators create a dynamic gameplay experience.

---

# Features

## Arduino-Based Real-Time Game Logic

* Input handling through physical buttons
* Round resolution using conditional game logic
* Temple health management
* Win/loss detection
* Automatic game reset

---

## Interactive Hardware Feedback

* LCD displays for custom player messages
* LED indicators for powerups
* Buzzer sound effects
* Real-time response to gameplay events

---

# Athena’s Favour Mechanic

Winning 2 consecutive rounds activates:

## ⚡ Athena’s Favour

Special effects include:

* Restoring player temple health on victory
* Blocking damage on defeat
* LED powerup indication
* Special LCD notifications
* Dedicated sound feedback

---

# Hardware Components

| Component            | Purpose                           |
| -------------------- | --------------------------------- |
| Arduino Uno          | Main controller                   |
| Push Buttons         | Zeus / Poseidon / Hades selection |
| LEDs                 | Athena’s Favour indicators        |
| LCD Screens          | Player messages & game feedback   |
| Buzzer               | Sound effects                     |
| MDF Laser Cut Panels | Physical game structure           |

---

# Core Game Logic

## Round Resolution

```cpp id="9t9epq"
int getResult(int p1,int p2){

 if(p1==p2)return 0;

 if((p1==1&&p2==2)||(p1==0&&p2==1)||(p1==2&&p2==0))return 1;

 return -1;

}
```

Determines:

* Victory
* Defeat
* Draw

based on player choices.

---

# Features Implemented in Code

## Input Handling

* Detects physical button presses
* Prevents repeated selection
* Supports simultaneous two-player interaction

---

## Temple Health System

* Tracks health for both players
* Updates health dynamically after rounds
* Handles victory conditions

---

## Powerup System

* Consecutive win tracking
* Athena’s Favour activation
* Temporary gameplay modifications

---

## LCD Feedback

Displays:

* Victory/Defeat
* Draw
* Powerup activation
* Game over
* Restart prompts

---

## Sound Effects

Different sounds for:

* Button clicks
* Wins/Losses
* Powerup activation
* Clashes

---

## Automatic Reset

Resets:

* Player health
* Powerup states
* Streak counters
* Player choices

after game completion.

---

# Circuit Design

The Arduino system integrates:

* Dual player button systems
* LCD displays via I2C
* LEDs
* Buzzer output
* Shared grounding and power

The circuit architecture is shown in the project documentation. 

---

# Project Inspiration

The game draws inspiration from:

* Greek mythology
* Divine elemental conflicts
* Modern mythology adaptations such as Percy Jackson

while adapting the mechanics into a child-friendly interactive physical game.

---

# Materials & Fabrication

## Physical Prototype

* MDF laser-cut structures
* Engraved temple artwork
* Hand-painted components
* Custom button layouts

---

# Technologies Used

* Arduino C/C++
* Arduino Uno
* Embedded Systems Programming
* LCD I2C Communication
* Digital Input/Output
* Embedded Game Logic

---

# Gameplay Flow

```text id="tkzjqx"
Player Input
      ↓
Button Detection
      ↓
Round Resolution
      ↓
Temple Health Update
      ↓
Powerup Check
      ↓
LCD + Sound Feedback
      ↓
Game End / Restart
```

---

# Learning Outcomes

* Embedded systems programming
* Real-time interactive systems
* Physical computing
* Arduino-based game design
* Hardware-software integration
* User-centered interaction design
* Rapid prototyping

---

# Future Improvements

* OLED animations
* Central animated temple display
* Improved lighting effects
* Advanced sound system
* Multiplayer expansion
* More mythology-based powers

---

# Demo & Prototype

The final prototype was demonstrated during the DES206 project showcase and received highly positive feedback for:

* Gameplay immersion
* Physical interaction
* Mythology-inspired design
* Visual aesthetics
* Competitive mechanics

