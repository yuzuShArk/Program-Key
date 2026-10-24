# Some Ideas about Program-Key

## Some background

"Program-Key" is a small individual project used to practice:

- hardware design
- firmware design
- how to use git
- using Linux terminal

## Specs about the Keyboard

- input method: touch to make input
- keyboard layout: QWERTY
- MCU: Raspberry Pi Pico (ESP32 or other MCUs are still in consideration
- output method: USB HID

## Initial Idea

For making prototype of the keyboard, I plan to use Raspberry Pi
Pico to control the keyboard. The "key" itself is more like a
touch sensor rather than a traditional mechanical switch key, so
I am going to use MPR121 and copper tape as the first version of
the key. As for HID... I actually have no thoughts on what to do
about that thing lol.

My goal for the first phase of the project:

- explore Raspberry Pi Pico
- test if the non mechanical key idea really works

## Dev log

### 2026/10/20

Today, I made quite some progress. Wrote the one header for key-mapping and one
for key event. Also, good news is that Pico MCU arrived. Thank god or else I'm
getting so bored.  
  
- Problems and Solutions:  
If I don't use the key event header to manage event, the return value from the
capacitance sensor will only have to value of "True" or "False",
like shown below:  

```text
return value:
false -> true -> true -> true -> false

but what the keyboard needs:
no event -> KeyDown -> no event -> no event -> KeyUp
```

So, hopefully the key event method will solve the problem. I haven't tested
it yet though...  
  
About update():  
Upon calling `update(electrode_id, touched)` , the program needs to do the
following steps:  

1. check keymap (if this electrode has corresponding key linked to it)
2. read old key state (KeyUp or KeyDown)
3. compare old state and new state (change if new state and old state is different)
4. update key state

### 2026/10/22

update() function now detects multiple electrodes at the same time.  
  
Start working at actually implementing c++ code to Pico MCU.

### 2026/10/23

#### Problem(1): Clang keeps prompting: "Warning: can't find `<cstdint`"

Successfully flashed firmware into Pico, but somehow clang has problem recognizing
things like `'std'` or `"keyboard.hpp"`... I make sure to check `compile_commands.json`
though, but that didn't help. WHY?

### 2026/10/24

Why does Clang keep telling me that it couldn't find `<cstdint>` but I can still
COMPILE and the `.uf2` file WORKS?????  
  
UPDATE!!! Turns out that this is a classical `compiler & clang not in sync` problem
In the root directory of the program, there is `./src/main.cpp ./src/keyboard.cpp
./src/keymap.cpp` and their corresponding `include files`.  
Originally, `g++` is used when compiling the code in `./src`. However, when compiling
the code in `./firmware`, it uses a different compiler
called `arm-none-eabi-g++`.  
**Clang DOES NOT know where the "Header Search Path" of the ARM compiler is.**  
Thus, when it comes to analyzing the code `./firmware/main.cpp`, it just simply
prompts that it can't find things like `<cstdint>` or such.  

#### Solution(1): Adjust nvim clang getting

Just simply use `--query-driver` in nvim .config files: `clangd.lua`, this argument
will allow clang to search the compiler so that it can acquire its
**Header Search Path**.  
The code is provided below:

```lua
return {
  "neovim/nvim-lspconfig",
  opts = {
    servers = {
      clangd = {
        cmd = {
          "clangd",
          "--query-driver=/usr/sbin/arm-none-eabi-*",
        },
      },
    },
  },
}
```

<p align="center">~~~ End of Solution ~~~</p>
