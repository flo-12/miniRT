# miniRT

Raytracing is an old - yet still very common method - for rendering algorithms that generate digital images.

The goal of this project was to get an introduction into the ray tracing technique. This involved understanding how 3d scenes can be represented and generated onto a 2d screen. Furthermore it required a deeper mathematical understanding of linear algebra to compute intersections with objects and calculate their corresponding illumination. And of course how to translate the logic into a C program which is limited to very basic external functions. 
The following images are generated by this program:

/// add amazing rendering images

Core features of this raytracer are:
- Render spheres, planes and cylinders with any orienation and position in space
- Have a variable viewpoint, view orientation as well as field of view
- Combining ambient, diffuse (maybe even specular) light sources with different colors
- (Using threads to render images faster)

# Usage
*Note that the program is written with Linux. Other operating systems were not tested.*

## Installing and Compiling
1) Clone the repository and its submodule by ``` git clone --recursive ... ```
2) direct to the cloned folder ```<folder_name>```
3) ```make``` (automatically compile the libft and MiniLibX)

*Check the MiniLibX ReadMe in case of problems with the library.*

## Execution
The proram will read the input for the scene from a file in .rt format. The scenes/valid/ folder contains some example scenes.
* Example: ```./miniRT J ./scenes/valid/...rt```

To enable colored diffuse light sources add .. to the environment variables
``` export ... ```

# Sources
Realizing this project requires a deeper understanding of the raytracing algorithm as well as some literacy in linear algebra. The following list is a recommendation of sources for anyone who wants to know more about the topic:
| Topic								| Link                                                        	|
|----------------------------------:|:--------------------------------------------------------------|
| Linear Algebra					| [3Blue1Browns Playlist on Linear Algebra](https://www.youtube.com/watch?v=kjBOesZCoqc&list=PL0-GT3co4r2y2YErbmuJw2L5tW4Ew2O5B) |
| Raytracing technique				| - [Scratchapixel](https://www.scratchapixel.com/index.html)		
									  - [Computer Graphics From Scratch](https://www.gabrielgambetta.com/computer-graphics-from-scratch/)]																	|
