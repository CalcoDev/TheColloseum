# The Colloseum - Input System

A small section describing how to use the input system. This is temporary, until
the entire code will be documented via Doxygen.

## Table of Contents

- [Description](#description)
  - [Structure](#structure)
- [How to Use](#how-to-use)
  - [Creating the Data File](#creating-the-data-file)
  - [Using the File in Code](#using-the-file-in-code)
    - [Includes](#includes)
    - [Initialization](#initialization)
    - [Updating / Polling Input](#updating--polling-input)
    - [Using the Input](#using-the-input)
    - [Cleaning Up](#cleaning-up)

## Description

The provided input system aims to create an easy way to create and map different
input schemes and actions, abstracting platform / input handling specific needs,
allowing you to focus on just the semantics of your actions.

### Structure

For now, you should just
[check the source code](https://github.com/CalcoDev/TheColloseum/blob/main/src/input/input.h)
.

<!-- TODO(calco): Add structure docs. -->

## How to Use

### Creating the Data File

Inside the `assets/data` directory, create a `.toml` file which will hold the input data.

```bash
cd ./assets/data;
touch input.toml;
```

Start by defining the `Input Map`

```toml
[input_map]
name = "global_input_map"
```

Continue by defining the general input schemes you will use. These can represent
different input sources, such as keyboard & mouse, controller or steering wheel.

```toml
[[input_map.schemes]]
name = "mouse_keyboard"

[[input_map.schemes]]
name = "controller"
```

</br>
<strong>WARNING: So far, only keyboard support has been added. For example's
sake we will pretend controller also works.</strong>
</br>

The actual input data will be stored inside each context. You can think of a
context as a logical part of your game, for example UI menu inputs and InGame
inputs, thus preventing useless checks and polls.

```toml
[[input_map.contexts]]
name = "ingame"

[[input_map.contexts]]
name = "ui-mode"
```

With each context defined, it is time to add their respective actions. For more
information on the specifics of actions, check out the
[source code](https://github.com/CalcoDev/TheColloseum/blob/main/src/input/input.h)
or the [descripton](#description).

Here are a few sample actions:

```toml
# Create a fire action which would trigger when the user presses or releases the
# left mouse button, or while the user holds the Z key.
[[input_map.contexts.actions]]
name = "fire"
type = "button"

[[input_map.contexts.actions.controls]]
key = "MouseLeft"
schemes = ["mouse_keyboard"]
modifiers = ["pressed", "released"]

[[input_map.contexts.actions.controls]]
key = "Z"
modifiers = ["held"]
schemes = ["mouse_keyboard"]
```

```toml
# Create an axis input for horizontal movement
[[input_map.contexts.actions]]
name = "move_x"
type = "range_1d"

[[input_map.contexts.actions.controls]]
positive_key = "D"
negative_key = "A"
schemes = ["mouse_keyboard"]

[[input_map.contexts.actions.controls]]
positive_key = "RightArrow"
negative_key = "LeftArrow"
schemes = ["mouse_keyboard"]
```

### Using the file in code

Using the file in the code is pretty straightforward.

#### Includes

```c
#include "input/input.h"
```

#### Initialization

```c
// Including Memory utlities for Arena creation
#include "base/base_memory.h"

// Including OSPath and OSMem utilities from the OS layer
#include "os/os.h"

// ...

// Initialization area
M_BaseMemory memory = OS_BaseMemory();
Arena arena;
ArenaInit(&arena, &memory, Megabytes(1));

// Get the absolute path to the previously created data file.
String8 path = OS_PathRelative(
    &arena, OS_PathExecutableDir(&arena), Str8Lit("./assets/data/input.toml")
);

// Load the input map
I_InputMap input_map = {0};
I_InputMapInit(&input_map, &arena, path);
```

#### Updating / Polling Input

```c
OS_WindowPollEvents();
I_InputMapUpdate(&input_map);
```

<strong>
WARNING: `I_InputMapUpdate()`, under the hood, uses the `OS_Input` layer for 
checking whether actions were triggered or not. This means that, while you can
call it independently of `OS_WindowPollEvents()`, it will still always use the
latest input data the window received.
</br>
This will be worked on in a future patch.</strong>

#### Using The Input

Going forth with the [previously defined actions](#creating-the-data-file), we
can get access to them as follows:

```c
I_InputMapContextAction* fire_action;
if (I_InputMapActionTryGet(&input_map, "ingame", "fire", &fire_action))
{
    // The "fire" action was found, and you can now use it to do and check
    // whatever is necessary.

    // Since "fire" is a button action, you can access its value via the union
    // fire_action->value.button.value      - value based on the [modifiers]
    // fire_action->value.button.pressed    - was any control pressed
    // fire_action->value.button.released   - was any control released
    // fire_action->value.button.held       - is any control held
}

I_InputMapContextAction* move_x_action;
if (I_InputMapActionTryGet(&input_map, "ingame", "move_x", &move_x_action))
{
    // The "move_x" action was found, and you can now use it to do and check
    // whatever is necessary.

    // Since "move_x" is a range1d action, you can access its value via the union
    // fire_action->value.button.value      - value between -1 and 1
}
```

#### Cleaning Up

Everything automatically gets cleaned up when the arena gets freed!

```c
ArenaRelease(&arena);
```
