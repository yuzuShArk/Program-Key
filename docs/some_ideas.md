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
- MCU: Raspberry Pi Pico 2 (ESP32 or other MCUs are still in consideration
- output method: USB HID

## Initial Idea

For making prototype of the keyboard, I plan to use Raspberry Pi
Pico 2 to control the keyboard. The "key" itself is more like a
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
