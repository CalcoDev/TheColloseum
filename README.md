<div align="center">
  <img src="./.github/assets/icon.svg" alt="Logo" width="50" height="50" />
  <h1>The Colloseum</h1>
  <p>
    A small C codebase / game engine combo, made from scratch with 0* external 
    dependencies, made for game or app developers who love making things from 
    the bottom up and learning low level programming.
  </p>

  <p>
    <a href="">
      <img src="https://img.shields.io/github/last-commit/CalcoDev/TheColloseum" alt="last update" />
    </a>
    <a href="https://github.com/CalcoDev/TheColloseum/network/members">
      <img src="https://img.shields.io/github/forks/CalcoDev/TheColloseum" alt="forks" />
    </a>
    <a href="https://github.com/CalcoDev/TheColloseum/stargazers">
      <img src="https://img.shields.io/github/stars/CalcoDev/TheColloseum" alt="stars" />
    </a>
    <a href="https://github.com/CalcoDev/TheColloseum/issues/">
      <img src="https://img.shields.io/github/issues/CalcoDev/TheColloseum" alt="open issues" />
    </a>
    <a href="https://github.com/CalcoDev/TheColloseum/blob/master/LICENSE">
      <img src="https://img.shields.io/github/license/CalcoDev/TheColloseum.svg" alt="license" />
    </a>
  </p>
</div>

## :notebook_with_decorative_cover: Table of Contents

- [About the Project](#star-2-about-the-project)
  - [Description](#description)
  - [Tech Stack](#tech-stack)
  - [Features](#features)
- [How to Use](#grey_question-how-to-use)
  - [Building](#building)
  - [Code Docs](#code-docs)
- [Roadmap](#roadmap)
- [License](#warning-license)
- [Credits](#gem-credits)

## :star2: About The Project

### Description

The primary motivation behind this project was to get a **better grasp of \
graphics programming, game engine architecture, and the C language as a whole**,
and also make a complete, easy to use, albeit highly opinionated framework / engine\* for
anyone to make their games or apps with.

This project was designed trying to follow
[Handmade Hero's](https://handmadehero.org/), or the
[Hidden Grove's](https://www.rfleury.com/) philosophy of building something from
nothing, with **minimal libraries and tools**.

### Tech Stack

The plan is to support any rendering framework and any operating systems,
however, for now, rendering features are implemented mostly for Windows and
OpenGL.

### Features

- **Base Layer**
  - **Context Handling**</br>
    Getting information about the current OS, compiler and processor architecture.
  - **Logging**</br>
    Basic logging functionality, provided through macros for now.
  - **Memory Management**</br>
    Mememory management via static arenas.
  - **Data Types**
    - **Renamed Primitives**
    - **Strings**
    - **Hashmaps**
  - **Math**
    - **2D 3D 4D Vectors**
    - **3x3 4x4 Matrices**
    - **Quaternions**
- **OS Layer**
  - **File IO**</br>
    'CRUD' operations with files, directories and general content.
  - **Path Utilities**</br>
    (windows :skull:)
  - **Time Utilities**
- **Render Layer**
  - **Camera**
    - Perspective Camera
    - Ortographic Camera
  - ... more rendering things, mostly specific to OpenGL for now.
- **Draw Layer**
  - TOOD(calco): Start draw layer abstractions.

## :grey_question: How to Use

In all honesty, if your goal is learning more about low level programming, I
would recommend **making your own codebase**, and maybe use this as inspiration /
help whenever you need it.

### Building

#### Prerequisites

This project uses **CMake as a build tool**, with Visual STudio 2022 generators on Windows. Other generators **_should work_**, but if not, feel free to [open an issue](https://github.com/CalcoDev/TheColloseum/issues) :thumbsup: .

##### DISCLAIMER

For those on Windows, due to troubles of getting vcvarsall on windows added to path automatically, you have to **manually add the path to your C libraries in CMakeLists.txt**.

Example path: `C:/Program\ Files\ (x86)/Windows\ Kits/10/Lib/10.0.19041.0/um/x64/`

#### Actually Building

Inside the root folder create a `build` directory, then, from within the newly created directory run:

```bash
cmake ..        # Specify any other settings you want
cmake --build . # Specify any other settings you want
```

##### WARNING

For now, this **does not copy the `assets` folder to the generated executables location**.

### Code Docs

Will be auto-generated via [Doxygen](https://www.doxygen.nl/) in a later version, but considering the project is still under heavy development and hasn't even reached version 0.1, **documentation is non existent**.

## :compass: Roadmap

The roadmap can be seen [here](https://trello.com/b/4EGSeAVS), on Trello!

## :warning: License

Distributed under the MIT License. See LICENSE for more information.

## :gem: Credits

As I have already mentioned, the main inspirations behind this project are:

- Casey Muratori's [Handmade Hero](https://handmadehero.org/)
- Ryan Fleury's [Hidden Grove](https://www.rfleury.com/)

Alongside them, other great codebases which were used as inspiration and help include:

- Pixel Rifts' [C Codebase](https://github.com/PixelRifts/c-codebase)
- Mr. 4th Programming's [Youtube Videos](https://www.youtube.com/@Mr4thProgramming/videos)
- Randy's [Resources Page](https://github.com/bigrando420/resources/wiki)
- All of Ryan Fleury's [blog posts](https://www.rfleury.com/), can't link them all but they are highly valuable.
