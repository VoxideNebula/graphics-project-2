# graphics-project-2

*Dana Parker, Troy Oster, Ben Bushnell, and Michael Seeley*

Repository for project 2 of MSU's CSCI 441 Graphics class.

## Description
This program is a ray tracer that supports Phong shading and reflections.

**Feature 1**: We chose to implement reflections. Each reflection takes into account the phong shading of the reflected object. We also accounted for nested reflections, so each reflection not only depicts the reflected object, but also the reflections on the reflected object, and so on.

**Feature 2** We ran out of time and couldn't manage to implement Feature 2.

## Build
1. Within `csci441-graphics-project-2/`, go into the `src` directory via `cd src`
2. Within `src/` run `mkdir build`
3. Enter the `build` directory via `cd build`
4. Run `cmake ..`
5. Build the project by entering `make`
6. Run the executable binary by entering `./proj02`

## Viewing the Rendered Image
1. Build and run the project using the above instructions.
2. Open the `ray_traced.bmp` bitmap image file located in the `/build` folder

## Sources
https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
