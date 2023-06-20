# SnakeGame
This project is the final project of Kookmin Univ. Department of Software cpp course.

**0. Setup**  
- In this project, TUI (Text User Interface) was applied using _‘ncurses’_ as an external library.
- We installed it using the `brew install ncurses` command according to the development environment _Mac OS_.
- The <ncurses.h> header file is read through the #include directive.


**1. Map**  
- The map space in which the game will be played consists of a space where the main character, _Snake_, can work, _Wall_, _Immune Wall_, _Snake's head and tail_, _Growth Item_ and _Poison Item_, and _Gate A_ and _B_.
- The 21*21 size Gameboard is implemented by statically allocating a two-dimensional array map through a char type data type.
- I set '3' and '4', respectively, '5' and '6' for Growth/Poison Item, and '7' for Gate A/B. It has been implemented to update some of the components of the map screen at regular intervals.


**2. Snake**  
- Snake appeared by setting the initial location on the map.
- Head coordinates are set to x, y coordinates, and body coordinates are managed and updated through _vector_.
- By dividing the snake's movement direction and the user's key input value into the number of cases, the x and y values that correspond to the values input to the snake's head are set to be continuously updated.
- By complying with some rules, the game ends when the _game over conditions_ are met.
- Also implemented and followed the rules below.
    - The direction key is input by the _user_, and if there is no input, it moves only in the existing direction.
    - Keys in the same direction as the direction you are going are ignored, and if you press the opposite key, _the game ends_.


**3. Item**  
- We also implemented two types of Items that change the Snake's size.
- _Snake_ and _Item_ have an interaction that affects the Snake's size, and was implemented in compliance with the following rules.
    - When Snake and Item _collide_, Snake, the subject of the game, acquires the Item.
    - When eating a Growth Item, Snake's size _increases_ by 1.
    - If you eat a Poison Item, the size of Snake _decreases_ by 1.
    - At regular intervals, an item appears in _a random space_ where Snake is not located. (At this time, the existing item disappears and a new item is created in a different location, and the number of items appearing at the same time is limited to 3.)
    - On the screen, it is implemented so that two Items can be _distinguished_ by different colors or symbols.
- These Items are set to be _randomly_ generated in an empty space(‘0’).
- In addition, _only 3 items_ can appear on the map at the same time, 2 Growth Items and 1 Poison Item.


**4. Gate**  
The Gate is implemented as appearing at an _arbitrary coordinate_ on the Wall (‘1’). In a similar way to the item implemented in step 3, the rand function was used to place the gate at an irregular, but map data, position of 1. When the snake passes through the gate, the gate disappears, and the coordinates of gates A and B are stored and managed in a vector.


**5. Score/Mission**  
The scoreboard above the gameboard displays the size of the current snake, the maximum length of the snake, the number of acquired items, and the number of gate passages. On the mission board, the given mission is displayed for each stage so that you can check the achievement on the right side of the board. Both the Scoreboard and Missionboard declared a new Window to distinguish them.


**6.**
