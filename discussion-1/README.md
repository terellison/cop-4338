Please, do the following steps:

1. Write a C function that prints out "Hello World!\n". Your function doesn't get any input parameters and doesn't return any values. Choose a reasonable identifier for your function.

2. Write another C function that prints out "Goodbye World!\n". Your function doesn't get any input parameters and doesn't return any values. Choose a reasonable identifier for your function.

3. Write a main function that
    - first, calls the first function,
    - second, calls the second function
    - and finally returns 0.

4. Create a directory in the ocelot machine called discussion1 (you can use WinSCP or CyberDock to do so, see Accessing your files off campus Links to an external site.for more details). Create and place the following four files in it:
    - hello.c that contains the function you made in Step 1.
    - bye.c that contains the function you made in Step 2.
    - main.c that contains the function you made in Step 3.
    - main.h that contains the declaration of functions stored in hello.c and bye.c
    - makefile or Makefile that organizes the compilation process of your program and construct an executable called "greetings". Use video lecture #0 of Module 2 for help.

5. Use cd command in ocelot to navigate to "discussion1" directory. Then, use make command to compile and generate the executable of your program.

6. Run your program by typing "./greetings" and see the result.

7. Take a snapshot of your terminal showing that commands "make" and "./greetings" work properly.

8. Post the content of "hello.c", "bye.c", "main.c", "main.h", and makefile on Canvas under this discussion forum. Also, post the snapshot you took in Step 7 under the same forum.

9. Compare your solution with your classmates' post under this discussion.

<b>Hint</b>: Watch the following video for help:

[![](https://img.youtube.com/vi/JOwHegJwjbA/0.jpg)](https://www.youtube.com/watch?v=JOwHegJwjbA)