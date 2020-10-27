# SFML_Space-Shooter-Game

A simple 2d space shooter game created by C++ and SFML(Simple and Fast Multimedia Library)

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

## Table of Contents

- [Background](#Background)
- [Exhibition](#Exhibition)
- [Install](#install)
- [Ideas](#Ideas)
- [Structure](#Structure)
- [Maintainers](#Maintainers)
- [License](#license)

## Background

3D render engines that are nowdays used in games. I write a very simple 3d render engine demo so that it will really help me understand some fundamental principles which are also used for modern render engines.

Through making this render engine, I learn about orthographic projection, simple triangle rasterization, z-buffering, flat shading and subdividing a tetrahedron to a sphere.

## Exhibition

Needs to be updated...

## Install

I Use C++ language and CLion (an IDE) under Windows 10 environment for this project.

[CLion Download](https://www.jetbrains.com/clion/download/#section=windows)<br>

## Ideas

Needs to be updated...

## Structure

The whole project in Unity contains two main folders, **Assets** folder and **Package** folder.

Under **src** folder, there are altogether **4** `java` classes:

1. `Vertex` class represents a position in 3d space.

2. `Triangle` class represents a triangle binding three vertices  together and stores its color.

3. `Matrix3` class represents a 3D Matrix which will help us do matrix-matrix and vector-matrix multiplications.

4. `DemoViewer` class is our main entrance of the render program, most of processes are made here.

## Maintainers

[@Yunxiang-Li](https://github.com/Yunxiang-Li).

## License

[MIT license](https://github.com/Yunxiang-Li/Simple-3D-Render-Engine/blob/main/LICENSE)
