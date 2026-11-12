# Embedded Systems for Complete Beginners

Theory, worked examples and field tips from Days 1 and 2 (Arduino in Tinkercad, heading to ESP32)

By Melito · November 12, 2026

## 1. What is an embedded system?

An embedded system is a **tiny computer hidden inside a device, built to do one job**. Your microwave, a washing machine, a car's window controller and a TV remote all have one. You never type on them. They just sense, think and act.

| Step | What it means | Example |
| --- | --- | --- |
| **Input** | The device senses something | A button press, a temperature reading |
| **Code** | The brain decides what to do | If the button is pressed, then... |
| **Output** | The device acts | An LED lights, a buzzer beeps, a motor turns |

Every project you will ever build is some version of **Input, then Code, then Output**.

The brain is a small chip called a **microcontroller**. A board like the **Arduino Uno** puts that chip on a board with **pins** (metal sockets along the edges) so you can connect wires to it. The **ESP32** is a more powerful board with WiFi and Bluetooth built in. It is your main track in the 30-day plan.

## 2. Electricity in five ideas

You do not need physics to start. Think of **water in pipes**.

| Idea | Water picture | In your circuit |
| --- | --- | --- |
| **Voltage (V)** | Water pressure | The push from the Arduino pin (5 V on an Uno, 3.3 V on an ESP32) |
| **Current (A or mA)** | How much water flows | How much electricity moves through the LED |
| **Resistance (Ω)** | A narrow pipe | A resistor squeezes the flow down |
| **Ground (GND)** | The drain at the bottom | Where the electricity returns to |
| **Circuit** | A closed loop of pipe | The full path: pin, parts, back to GND |

### Rule 1: electricity only flows in a complete loop

If any link is missing (a loose wire, a part across a gap, no ground), nothing happens. This is the cause of most 'it does nothing' problems.

### Rule 2: too much current destroys parts, so use a resistor

An LED has almost no resistance of its own. Without a resistor it pulls far too much current and burns out. A resistor limits the flow.

**Ohm's law** (the one formula worth knowing): `Current = Voltage / Resistance`

Worked example, a red LED on a 5 V pin with a 220 Ω resistor:

- The LED itself uses about 2 V, which leaves 3 V across the resistor.
- Current = 3 / 220 = about 0.0136 A, which is **about 14 mA**. That is safe, because an LED's limit is around 20 mA.

Now the same circuit with a tiny resistor, or with the resistor bypassed. The current shoots past 40 mA, and Tinkercad warns you (you saw exactly this: 40.9 mA, then a burst icon). With 8 LEDs that is over 300 mA, more than an Arduino pin set can supply.

### Digital means only two states

| Value | Meaning | Voltage |
| --- | --- | --- |
| `HIGH` | On | 5 V (3.3 V on ESP32) |
| `LOW` | Off | 0 V |

## 3. The hardware parts

### The breadboard

A breadboard lets you build circuits without soldering. What matters is **which holes are connected inside**:

```
Top rail   (-) o o o o o o   all holes in one row are connected
           (+) o o o o o o   (use for GND and power)

Rows A-E:   each numbered strip of 5 holes is connected

  ======== the middle gap: the two halves are NOT connected ========

Rows F-J:   each numbered strip of 5 holes is connected

Bottom rail (-) o o o o o o
           (+) o o o o o o
```

**The big lesson of Day 2:** a resistor with **both legs in the same strip** does nothing, because current takes the shortcut through the strip. Put it **across the gap**, one leg in row E and one in row F, so its two ends are in different, unconnected strips.

### The LED

- **Long leg = anode (+)**: connects toward the Arduino pin side.
- **Short leg = cathode (-)**: connects toward GND.
- Backwards means no light. It is not damaged, just dark.

### The correct LED path (one LED)

```
Arduino pin -> wire -> bottom strip -> RESISTOR (across the gap)
            -> top strip -> LED long leg -> LED short leg
            -> GND rail -> wire -> Arduino GND pin
```

That is one complete loop. Every LED needs its own resistor and its own pin, and they all share the same GND rail.

### Button and buzzer (Day 3 preview)

- **Pushbutton:** connects two points only while pressed. The clean way to wire it is one leg to a pin and the other leg to GND, and use `INPUT_PULLUP` in code.
- **Buzzer:** an **active** buzzer beeps when you set its pin `HIGH`. A **passive** buzzer needs `tone()` to choose the pitch.

## 4. Code basics

### 4.1 Every Arduino program has two parts

```cpp
void setup()
{
  // runs ONCE when the board starts: prepare things here
}

void loop()
{
  // runs OVER AND OVER forever: the main action goes here
}
```

### 4.2 The grammar rules (a missing symbol is the commonest error)

| Rule | Example |
| --- | --- |
| Every instruction ends with `;` | `delay(500);` |
| Every `(` needs a `)` | `digitalWrite(2, HIGH);` |
| Every `{` needs a `}` | around `setup`, `loop`, `for` |
| Spelling and capitals matter | `digitalWrite` works, `digitalwrite` fails |
| `//` starts a comment the computer ignores | `// wait half a second` |

### 4.3 Variables: named boxes that hold a value

```cpp
int ledPin = 2;          // a box called ledPin holding the number 2
const int STEP_MS = 300; // const means it never changes
```

Naming your pins means you change the wiring in **one place** instead of hunting through the code.

### 4.4 Arrays: a numbered list

```cpp
int led[] = {2, 3, 4, 5, 6, 7, 8, 9};
```

| `led[0]` | `led[1]` | `led[2]` | ... | `led[7]` |
| --- | --- | --- | --- | --- |
| 2 | 3 | 4 | ... | 9 |

**Counting starts at 0, not 1.** For 8 items the numbers run 0 to 7.

### 4.5 The `for` loop: repeat something

```cpp
for (int i = 0; i < 8; i++)
{
  digitalWrite(led[i], HIGH);
}
```

Read it as three parts inside the brackets:

1. `int i = 0` : start a counter at 0.
2. `i < 8` : keep going while the counter is less than 8.
3. `i++` : after each round, add 1.

So it runs 8 times, with `i` taking the values 0, 1, 2 ... 7.

### 4.6 `if` and `else`: make decisions

```cpp
if (digitalRead(buttonPin) == LOW)   // is the button pressed?
{
  digitalWrite(ledPin, HIGH);
}
else
{
  digitalWrite(ledPin, LOW);
}
```

Watch out: `=` **stores** a value, while `==` **compares** two values.

### 4.7 Functions: named commands

A function is a **named command that does one job**. The details inside the brackets are its **arguments**.

You can also write your own, so you never repeat yourself:

```cpp
void setAll(int state)
{
  for (int i = 0; i < 8; i++) digitalWrite(led[i], state);
}
// now setAll(HIGH) lights everything and setAll(LOW) turns everything off
```

## 5. The commands you have met (and are about to meet)

| Function | Arguments | What it does |
| --- | --- | --- |
| `pinMode(pin, mode)` | pin, `OUTPUT` / `INPUT` / `INPUT_PULLUP` | Sets the pin's job. Call once, in `setup()` |
| `digitalWrite(pin, value)` | pin, `HIGH` / `LOW` | Turns a pin on or off |
| `digitalRead(pin)` | pin | Reads a pin and returns `HIGH` or `LOW` |
| `delay(ms)` | milliseconds | Waits. 1000 ms = 1 second |
| `tone(pin, hz)` | pin, pitch | Plays a note on a buzzer |
| `noTone(pin)` | pin | Stops the sound |
| `Serial.begin(speed)` | e.g. 9600 | Opens the link to your computer (in `setup()`) |
| `Serial.println(x)` | text or number | Prints a line to the Serial Monitor |
| `analogRead(pin)` | analog pin | Reads a sensor, giving 0 to 1023 |
| `analogWrite(pin, v)` | pin, 0 to 255 | Dims an LED |

**The pairing to remember:** `pinMode` decides the pin's job (once). `digitalWrite` or `digitalRead` uses it (as often as you like).

### Why `delay` is needed

The Arduino executes millions of lines per second. Without a pause, it would flip LEDs on and off thousands of times a second, and your eyes would see them dimly lit all the time. `delay(700)` freezes the pattern for 0.7 seconds so you can see it.

## 6. Worked examples

Assume 8 LEDs on pins 2 to 9 through resistors.

### 6.1 Blink all 8

```cpp
int led[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup()
{
  for (int i = 0; i < 8; i++) pinMode(led[i], OUTPUT);
}

void loop()
{
  for (int i = 0; i < 8; i++) digitalWrite(led[i], HIGH);
  delay(500);
  for (int i = 0; i < 8; i++) digitalWrite(led[i], LOW);
  delay(500);
}
```

### 6.2 First 4 on, last 4 off, then swap

The trick is the counting range. `i = 0` to `i < 4` covers the first half, and `i = 4` to `i < 8` covers the second half. Turn one half on and the other off, delay, then swap.

### 6.3 Chaser: one LED at a time

```cpp
void loop()
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(led[i], HIGH);   // this one ON
    delay(200);
    digitalWrite(led[i], LOW);    // OFF before moving on
  }
}
```

### 6.4 Back-and-forth (ping-pong)

Go forward 0 to 7, then backward 6 down to 1. Skipping the two end LEDs on the way back stops them from lighting twice in a row.

### 6.5 Do something only 10 times

`setup()` runs once and `loop()` runs forever. To repeat something a fixed number of times, put a `for` loop (counting 0 to 9) inside `setup()` and leave `loop()` empty.

### 6.6 Shrinking pattern from both ends

The **mirror** of LED `i` is `N - 1 - i`. To turn off both ends moving inward, switch off `led[s]` and `led[N - 1 - s]` in each step. With an odd N the middle LED is last. With an even N you can end with two LEDs. (Removing pairs never changes odd or even, so 9 LEDs cannot end with two.)

### 6.7 A button controls an LED (preview)

```cpp
const int buttonPin = 4;
const int ledPin = 2;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);   // button between pin and GND
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if (digitalRead(buttonPin) == LOW)  // LOW means pressed
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);
}
```

With `INPUT_PULLUP`, the pin rests at `HIGH` and drops to `LOW` when the button connects it to GND.

## 7. The debugging playbook

There are two kinds of problems, and they need different tools.

### 7.1 The code will not compile (the red error box)

Read the message as `line:column: error: ...` and go to that line. Also check the line **above**, because a missing symbol is sometimes reported one line late.

| Message | Usual meaning |
| --- | --- |
| `expected ')' before ';' token` | You forgot a closing bracket on that line |
| `'x' was not declared in this scope` | You used a name that was never defined above it (a deleted variable or array, or a typo) |
| `expected ';' before ...` | A semicolon is missing at the end of the line before |
| Duplicate `setup` or `loop` | You pasted new code on top of old code without clearing it first |

### 7.2 The code runs but the circuit does nothing

Check in this order:

1. **Is there a complete loop** back to GND?
2. **Are the parts connected through the gap correctly?** Resistor across the gap, never both legs in one strip.
3. **LED the right way round?** Long leg toward the pin.
4. **Do the pin numbers in the code match the wires?** This catches many beginners.
5. **Did you call `pinMode(pin, OUTPUT)`?**
6. **Warnings:** hover over parts in Tinkercad. A message like 'current through the LED is 40.9 mA' tells you exactly what is wrong.

### 7.3 The method that works every time

- **Isolate:** shrink the problem to one LED and a three-line program.
- **Change one thing at a time**, then test.
- **Print to see:** `Serial.println(value)` shows what the program is really doing.
- **Explain it out loud** step by step. You will often hear the mistake as you say it.

## 8. Saving your work with Git

The daily routine is four commands (type them rather than pasting, because pasting can add hidden characters in Git Bash):

```
cd embedded-learning
git add .
git commit -m "what you built today"
git push
```

- Commit **each time something works**, with a message that says what you did.
- Use clear file names with no spaces, such as `03_chaser.ino`.
- The repo is public. **Never commit passwords, WiFi details or API keys.**
- `git status` shows what changed. `git log --oneline` shows your history.

## 9. Gold tips

1. **Build the smallest thing first.** One LED, then eight. One feature, then two.
2. **Change one thing at a time.** If it breaks, you know what caused it.
3. **Predict before you run.** Write down what you think will happen. When you are wrong, that is where the learning happens.
4. **Draw it on paper first.** A pencil sketch of the circuit and of the LED pattern catches most mistakes before they cost you time.
5. **Name your pins and numbers** (`ledPin`, `STEP_MS`) instead of typing bare numbers.
6. **Write comments for your future self.** In a month you will not remember why a line is there.
7. **Type code, do not paste it,** while you are learning. Your fingers learn the grammar.
8. **Read errors from the top** and trust the line number.
9. **Building teaches more than watching.** The plan gives 65 minutes to building for this reason. Finish each lesson with something you made.
10. **Rebuild from memory.** Close the video and recreate the circuit and the code. If you can, you own the skill.
11. **Commit often,** small and clear. It protects your work and builds a record you can show others.
12. **Test the simulation with extreme values.** Try `delay(5)` or `delay(2000)` to see what a number really controls.
13. **Keep secrets out of code.** Put them in a separate file that is not committed.
14. **Consistency beats intensity.** Two focused hours every day beat one heroic weekend.

## 10. Glossary

| Term | Plain meaning |
| --- | --- |
| **Microcontroller** | The small chip that runs your code |
| **Pin / GPIO** | A metal socket on the board you can switch on or off, or read |
| **Sketch** | An Arduino program (a `.ino` file) |
| **Compile** | Translating your code into something the chip understands. Errors show up here |
| **Upload** | Sending the compiled program onto the board |
| **Variable** | A named box holding a value |
| **Array** | A numbered list of values, counted from 0 |
| **Function** | A named command that does one job |
| **Argument** | A detail you hand to a function inside its brackets |
| **Anode / Cathode** | The positive (long) and negative (short) legs of an LED |
| **GND** | Ground, where current returns to |
| **Short circuit** | An unintended path that lets too much current flow |
| **Commit** | A saved snapshot of your files in Git |
| **Repo** | The project folder Git keeps track of |

## 11. Moving to the ESP32

Everything above carries over: `pinMode`, `digitalWrite`, `digitalRead`, `delay`, arrays, loops and the circuit rules. These things change:

- **Logic is 3.3 V, not 5 V.** Check part ratings before connecting anything.
- **Pin names are GPIO numbers,** and a few pins are input-only or have special boot roles, so check a pinout diagram before wiring.
- **Serial speed** is usually `Serial.begin(115200)`.
- **WiFi and Bluetooth are built in,** which is what makes the Week 3 goal (a sensor node that sends data out) possible.
- **The board is wide,** so it can cover breadboard holes you meant to use.

Tinkercad does not have an ESP32. Use real hardware or an ESP32 simulator such as Wokwi when you get there.

**Next steps:** buzzer and switch lessons (16 to 21), then serial printing (22 to 27), then the LCD and the temperature sensor.
