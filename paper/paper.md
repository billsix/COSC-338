## Final Paper

Due by the end of the semester.

### Purpose

Read/modify/create a graphics program, or tutorial, and write a paper
on what you learned, did, or tried to do but were unsuccessful.  
Please also submit source if you wrote/modified code.
I estimate a 3 page minimum paper per student.

I expect each student to find something they want to learn more about or to do,
and to be self directed toward an objective of their choice, whether it is 
reading to learn a new graphics concept, reading to understand how an
implementation works, or writing/modifying code for some decided objective.
Take a look at all of the ideas below, or choose something else.  For the tutorials listed below,
I recommend looking at the objectives and see if anything looks interesting
to you.  For the codes below, I recommend compiling and running many of projects,
see anything you'd like to learn about or change.  

With that said, you don't have to stick to one project.  You can try some, do well,
or do poorly, and change projects of study, but document it all.  If you worked on
something for 4-8 hours, were unable to complete what you wanted to do, you need
to write that down and why, and what you learned not to do.  
Because if you don't document it, I don't know that you did
it.  Being unsuccessful at a thing or two is good, it means you stretched yourself.
Towards a self-directed objective, failure to achieve the objective can still
be a valuable experience and should be documented and learned from.  
I never learned anything of value
from a game of chess in which I won, only those in which I lost.

When you start working on something, I'm available via email/slack to help with
questions.  I expect some people to have difficulty with C, for instance; but 
document what you learned.


### Project ideas (in order of perceived difficulty).

#### Study "Code the Classics"

Language: Python

Codebase: https://github.com/billsix/Code-the-Classics .  (Original source,
https://github.com/Wireframe-Magazine/Code-the-Classics)  I modified
it to have a requirements.txt file so that visual studio can run
it unmodified, you just need to set the startup project.


There is an book for sale covering these classic games, which
have been written in Python using PyGameZero.  Study the code, all of which is
in 2D.  Study collision detection, imaging, usage of transparency, input.
Study the data structures used and why.
Compare and constrast PyGameZero with glfw and glut.


#### Study a simple implementation of Minecraft in Python.

Language - Python

OpenGL 2.0 

https://github.com/billsix/Minecraft (the Python version, based off of 
https://github.com/fogleman/Minecraft). I updated it for Visual Studio 2019, and modern Python.

Compare and constrast how the windowing/input libraries work compared to what you've seen.
Figure out how the data structures are rendered.  (How are the blocks represented in data structures??)
How do they do texturing?  Do they use lighting? If not, can you add it in based off of something
that you've seen in the class?  

Perhaps change lighting around so that there is 
next to minimal ambient light, and make a spot light to act as a flashlight. (the blue
book covers how to do this.)  Maybe change
how movement works when you fly (flying is done by pressing tab),  by making the height
stay constant when you move, regardless of the viewer's orientation.  Maybe add mipmapping
in to make the graphics look better from far away when moving. (This would probably involve breaking
the one texture into multiple textures).  Maybe add in controller support (although,
this is not GLFW, it's pyglet, so I don't know how it would work).  Maybe port the Minecraft in Python
code from pyglets to using python's bindings of glfw. 

Maybe, more challengingly, upgrade the codebase to OpenGL 3.3 Core Profile.


#### Read a series of OpenGL tutorials and write about what you learned

I've found that reading intro material which was written by different
authors helps me to futher my understanding of fundamentals.

In particular, either study something not covered in class, or discuss
how their explanations differed/compared to mine, and what you learned 
in the process.

##### http://opengl-tutorial.org

Language: C

Code: My branch with fixes regarding camera management on Linux https://github.com/billsix/ogl

##### http://learnopengl.com

Language: C++

Code: https://github.com/JoeyDeVries/LearnOpenGL

#### Study the implementation of the perspective demo

Language - Python

OpenGL 3.3 Core Profile

https://github.com/billsix/modelviewprojection/blob/master/mvpVisualization/demoPerspective.py

In particular, how does the code warp the frustum to help explain perspective/ortho?

https://github.com/billsix/modelviewprojection/blob/master/mvpVisualization/frustum.vert

(You'd need to study more than just that one thing, understand how all of it works.)

#### Study tinyrender or tiny raytracer

https://github.com/ssloy/tinyrenderer/wiki

In tiny renderer (https://github.com/ssloy/tinyrenderer), how are triangle actually filled in screen space?  Our 
class reduced a set of vertices to NDC, but OpenGL itself fills
the polygons in.  There's a lot of other good material there.  Study something
and write about what you learned.

In tiny raytracer (https://github.com/ssloy/tinyraytracer/wiki), what did you learn?
We never covered raytracing in class other than mention the name.  This involves
a bit of math, more than we covered in class.

#### Upgrade a program from OpenGL2 to OpenGL3.3 core profile.

Language - C++ (for OpenGL Blue book), Python for my modelviewprojection demos.

The pyramid example in Ch8 of the BlueBook would be an excellent one to do,
as it involves simple transformations, simple geometry, lighting, and texturing. 
C++ should not be an issue.


#### Study the implementation of Minecraft in C.

Language - C

OpenGL 3.3 Core Profile (no fixed function code; shader based, which we will cover
soon)

https://github.com/billsix/Craft , modified from https://github.com/fogleman/Craft
to use core profile, and to be easily compiled with Visual Studio 2019 (via 
VS2019's cmake integration)

Same questions as the python one above (among others, movement, controller
support, etc).  But also, how to do the shader's work?  

How does fog work,
now that the shader has complete control over the fog?  What equations does the shader
use, and how do they compare to the equations written in the first half of the opengl 
superbible v4 book?  How does the author use matricies?  Are they in a matrix stack?


#### Study the McNopper demos

Language - C

OpenGL Core Profile (no fixed function code; shader based, which we will cover
soon)

There are a ton of cool demos here, many of which are quite advanced.  One of the 
demos shows a cool water effect, one does order-independent blending.  There's
a lot of cool stuff there to study.

  