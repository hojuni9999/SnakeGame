# SnakeGame
This project is the final project of Kookmin Univ. Department of Software cpp course.

**0. Setup**

In this project, TUI (Text User Interface) was applied using _‘ncurses’_ as an external library. We installed it using the `brew install ncurses` command according to the development environment _Mac OS_. The <ncurses.h> header file is read through the #include directive.

  
**1. Map**

The map space in which the game will be played consists of a space where the main character, _Snake_, can work, _Wall_, _Immune Wall_, _Snake's head and tail_, _Growth Item_ and _Poison Item_, and _Gate A_ and _B_. The 21*21 size Gameboard is implemented by statically allocating a two-dimensional array map through a char type data type. I set '3' and '4', respectively, '5' and '6' for Growth/Poison Item, and '7' for Gate A/B. It has been implemented to update some of the components of the map screen at regular intervals.


**2. Snake**

**3. Item**

**4. Gate**

**5. Score**

**6.**
