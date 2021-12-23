# 🤼 Corewar

🧗🏻 Corewar is the last project of the algorithmic specialization in 42 (just before the first internship).

🎮 It was inspired by a [programming game](https://en.wikipedia.org/wiki/Core_War) created in 1984.

📌 [Subject](https://github.com/marielisepicard/42corewar/blob/main/corewar.en.pdf)

## The goal of Corewar is to:

- 💫 **Code an Assembler**: a program that will traduce a champion file (an assembly language) to a bytecode language (that will be readable by the Corewar program)

- 🖥 **Create a Virtual Machine**: this is where the game takes place. More concretely, it's a box of 64 x 64 bytes of memory. 

- 🦸🏼 **Load Champions into the Virtual Machine:** a champion is one of the player of Coreware and is basically a stack of instructions (saying what the player will "do" inside the virtual machine). 

## 🦸 Champion:

A champion is a corewar player. 

It has a name (it can have a moto as well, but it's optional) and it has a list of instructions. 

The instruction will be executed during the game and excellent instructions can make a player win. Multiple [Corewar Championships](https://www.youtube.com/watch?v=R-OkYyzp-DI) have been organized in 42. 

At the beginning of a game, each player takes place on the memory board. A player is represented by its stack of instructions. 

<img src="https://raw.githubusercontent.com/marielisepicard/42corewar/main/assets/player.png?token=AWE4BMTIH67RZR7UJSY3OI3BYBTLI" width=80% height=80%>


## 🕹 Process:

A process is an **instruction** we gave to the virtual machine. There are **16 possible instructions**. Each of them is represented by an hexadecimal number. 

An instruction will basically **write new instructions on the memory board** (and therefore extend a player territory), **clone itself** (and therefore multiply the number of instructions a player can make at each round). 

**Here are some examples:**

- fork -> write a new process on the memory board
- zjmp → make a "jump" to another place of the game board
- st → write a value on the game board
- live → allow a process to say alive.

An instruction is executed when it's read by a cursor, the moving parts with inverted color. Cursors are read from the game board. Each player has one cursor at the beginning of a game. The game advances as the cursors read the instructions stored in the VM. If they end up on a faulty command or a blank memory, it moves to the next byte.

## To summarize: 

1) We, Human beings, write a champion

<img src="https://raw.githubusercontent.com/marielisepicard/42corewar/main/assets/Goku.png?token=AWE4BMVJ5477OZ5BYPCFLSTBYBTPM" width=80% height=80%>

2) The assembler will traduce it to bytecode 

<img src="https://github.com/marielisepicard/42corewar/blob/main/assets/Assembler.gif?raw=true" width=80% height=80%>

3) We charge champions into the virtual machine (a 64x64 bytecodes memory board) 

<img src="https://raw.githubusercontent.com/marielisepicard/42corewar/main/assets/Arena.png?token=AWE4BMUNYVLOY3Q76SW7S7LBYBTRG" width=80% height=80%>

4) We run corewar and the fight between champions starts. Each player can execute their instruction and try to conquer the memory board to be the last survivor.

<img src="https://github.com/marielisepicard/42corewar/blob/main/assets/Fight.gif?raw=true" width=80% height=80%>


## 🏆 How can we win a game?

- **Round**: a game is composed of multiple rounds (or cycles). At each round, each player can read an instruction and therefore execute a process.
- **Lives**: If a cursor read a life from the game board, it adds a life to the linked player (a life is one of the possible instruction)
- **Cycle to die**: it determines how many time the players can execute their instructions.

The winner of a corewar game is the last champion that has been reported as alive (which is one of the 16 instructions).
The VM regularly check if each player has been reported as alive by a process. 
If a player hasn't been reported as alive, it is eliminated.

**This is a simplified way to explain how the game works. The best way to understand is to run the program and see it in real-time**

## ⌨️ usage:

### Get a champion

`make`

Choose players from `players` folder and traduce a player in bytecode language with `./asm <playername.s>` command

### Launch a game 

usage: `./corewar [-dump N -v N -c | -ncurse] [[-n number] champion1.cor] ...`

```       -dump N : Dumps memory after N cycles then exits
        -v N    : Verbosity levels, can be added together to enable several
                        - 0 : Show only essentials
                        - 1 : Show lives
                        - 2 : Show cycles
                        - 4 : Show operations (Params are NOT litteral ...)
                        - 8 : Show deaths
                        - 16 : Show PC movements (Except for jumps)
        -c      : Color, shows verbose with colors

        -ncurse : Ncurses output mode
```
For instance, if you want to see the game, you need to use "-ncurse" option:

`./corewar -ncurse -n 2 ./players/Gagnant.cor ./players/mortel.cor`

## Credits

This project has been made by
@agelloz
@ekelkel
@manki
@mpicard

Players in the `players` folder were made by students for the Corewar Championship and are shared by 42 as ressources.
