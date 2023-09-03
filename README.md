# miniRT
Thanks [Linuswidmer](https://github.com/linuswidmer) for the collaboration on this project!

**Raytracing** is an old - yet still very common method - rendering algorithm to generate digital images. Raytracing is more expensive in computation the the “Rasterization” method,but it produces a much higher degree of visual realism.

The goal of this project was to implement a ray tracing algorithm in C (with a minimum of external functions)! The main goal of **miniRT** is the implementation of any mathematics or physic formulas, necessary for the tracing.

The following images are generated by this program:

![too_many_spheres](https://github.com/flo-12/miniRT/assets/119588327/f0aa7c97-8ad2-45e6-a517-d5c50e6d216b)


## Learning goals
- Understand representations and transformations of 3D scenes in computer graphics
- Calculation of intersection between vectors and 3D-objects (spheres, planes, cylinders, ...).
- How to translate the above points into pure C-code
- And of course **how to collaborate** on a project and split workload in an efficient way!

Core features of this raytracer are:
- Render spheres, planes, cylinders and cones with any orienation and position in space
- Have a variable viewpoint, view orientation as well as field of view
- Combining ambient and diffuse light sources with different colors and phong effect

Allowed external functions / libraries:
- open, close, read, write, printf, malloc, free, perror, strerror, exit
- All functions of the math library (-lm man man 3 math)
- All functions of the MinilibX - graphical library provided from 42 (see submodule)
- Libft - own library with basic functions such as calloc, strncpm, etc. (see submodule)

_As usual: All heap allocated memory space must be properly freed. No leaks
will be tolerated._

# Usage
*Note that the program is written with Linux. Other operating systems were not tested.*

## Installing and Compiling
1) Clone the repository and its submodule by ``` git clone --recursive <project SSH/URL> ```
2) direct to the cloned folder ```<folder_name>```
3) ```make``` (automatically compile the libft and MiniLibX)

*Check the MiniLibX ReadMe in case of problems with the library.*

*NOTE:* by default the program compiles with the extras of cones, multiple light sources, colored light and phong effect. To disable the extras, set DBONUS in the path variable (```export DBONUS=0```). Additional debug values will be printed in the prompt after setting ```export DPARSER=1``` and ```export DRENDER=1``` (don't forget to re-compile!!!)

## Execution
The proram will read the input for the scene from a file in ```.rt``` format. The ```*/scenes/valid/``` folder contains some example scenes.
* Example: ```./miniRT ./scenes/valid/eval_sheet_pillars.rt```

## Scene Format
Rules for scene format
Every scene must contain at least a **Viewpoint (C)**, an **ambient lighting (A)** and one or more diffuse **light sources (L)**:
- Identifier (C) ; coordinates (x,y,z) ; orientation vector (x,y,z) [-1..1] ; field of view (deg) [1..179]
- Identifier (A) ;                       intensity ([0..1])                 ; colors (r,g,b) [0..255]
- Identifier (L) ; coordinates (x,y,z) ; intensity ([0..1])                 ; colors (r,g,b) [0..255]

Additionally the Scene can contain **Objects** such as sphere (sp), plane (pl), cylinder (cy) and cone (co)
- Identifier (sp) ; center (x,y,z) ; diameter ; color (r,g,b) [0..255]
- Identifier (pl) ; coordinates (x,y,z) ; orientation vector (x,y,z) orthogonal to plane [-1..1] ; color (r,g,b) [0..255]
- Identifier (cy) ; center (x,y,z) ; orientation vector (x,y,z) [-1..1] ; diameter ; height ; color (r,g,b) [0..255]
- Identifier (co) ; coordinates (x,y,z) of vertex) ; orientation vector (x,y,z) [-1..1] ; opening angle (deg) [1..179] ; color (r,g,b) [0..255]

Given the above rules we can define a Scene:
``` 
C   0,5,-15   0,0,1   80
A                     0.2    90,90,255
L   0,6,-10           1     255,255,255


pl  1,-1.5,10   0,1,0             255,255,255
sp  9,0.0,0.0           3.6       0,255,0
cy  -7,1.5,0    1,0,0   4     6   0,255,255
co  3,7,0       0,-1,0  23        255,0,0

```
which renders to
![scene with cone sphere and cylinder](images/cyliner_cone_sphere.png)

// not necessary maybe ?
To enable colored diffuse light sources add .. to the environment variables
``` export ... ```

# Sources
Realizing this project requires a deeper understanding of the raytracing algorithm as well as some literacy in linear algebra. The following list is a recommendation of sources for anyone who wants to know more about the topic:
| Topic								| Link                                                        	|
|----------------------------------:|:--------------------------------------------------------------|
| Linear Algebra					| [3Blue1Browns Playlist on Linear Algebra](https://www.youtube.com/watch?v=kjBOesZCoqc&list=PL0-GT3co4r2y2YErbmuJw2L5tW4Ew2O5B) |
| Raytracing technique				| [Scratchapixel](https://www.scratchapixel.com/index.html), [Computer Graphics From Scratch](https://www.gabrielgambetta.com/computer-graphics-from-scratch/)|
| Diffuse and Specular Light| [Diffuse Light](https://www.tomdalling.com/blog/modern-opengl/explaining-homogenous-coordinates-and-projective-geometry/) , [Blinn-Phong Model](https://learnopengl.com/Advanced-Lighting/Advanced-Lighting)|
|Cone |[What is a cone???](https://mathworld.wolfram.com/Cone.html), [Cone - Ray intersection](https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/) |
|Sphere | [Sphere - Ray intersection](https://www.cl.cam.ac.uk/teaching/1718/AdvGraph/1.\ Ray\ Tracing\ -\ All\ the\ Maths.pdf) |

# Fancy pictures
The following pictures were rendered with the program:
| | |
|-----------------------------|--------------------------|
|![snowscene](https://github.com/flo-12/miniRT/assets/119588327/e1d2fecc-a86b-4aa0-8c8b-c6bedfd80732) | ![cyliner_cone_sphere](https://github.com/flo-12/miniRT/assets/119588327/876e2b9f-caac-49f1-a094-1c952ebaa796) |
|![basic_cy_sp rt](https://github.com/flo-12/miniRT/assets/119588327/c1a0925b-d74d-474b-b080-32b59991e245) | ![some_spheres](https://github.com/flo-12/miniRT/assets/119588327/21152c30-84f9-4bd2-8895-18e28e0d4396) |
|![eval_sheet_pillars](https://github.com/flo-12/miniRT/assets/119588327/4fa2129b-55f5-4e06-bb10-03eb72375396) | ![double_cone_sphere](https://github.com/flo-12/miniRT/assets/119588327/481d99c9-9804-4196-ad72-9e48e971ad8b) |

