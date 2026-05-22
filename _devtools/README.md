*This project has been created as part of the 42 curriculum by <ibrouin-> <mickzhan>*

## Description

The purpose of the project is to learn how we made the first fps (First person shooter) game with principe of raycasting
It will improve our skill in these areas: windows, colors, events, fill shapes, etc.

You can test the first game here : http://users.atw.hu/wolf3d/

Also Iona made a Notion of how raycasting works for the curious one

https://decisive-rise-4fb.notion.site/Cub3D-355e78575df5806a810beb4949024ad2

## Instructions

Launtch the game with the command "./cub3D" after that you use a map

You have some map in the root of the project there is a file map

Except for the map, each element must begin with its type identifier (composed
by one or two characters), followed by its specific information in a strict order:
∗ North texture:
NO "/path_to_the_north_texture"
· identifier: NO
· path to the north texture
∗ South texture:
SO "/path_to_the_south_texture"
· identifier: SO
· path to the south texture
∗ West texture:
WE "/path_to_the_west_texture"
· identifier: WE
· path to the west texture
∗ East texture:
EA "/path_to_the_east_texture"
· identifier: EA
· path to the east texture
∗ Floor color:
F 220,100,0
· identifier: F
· R,G,B colors in range [0,255]: 0, 255, 255
Ceiling color:
C 225,30,0
· identifier: C
· R,G,B colors in range [0,255]: 0, 255, 255

If any misconfiguration of any kind is encountered in the file, the program
must exit properly and return "Error\n" followed by an explicit error message
of your choice.

make : to compile everything
make clean : to clear .o
make fclean : to clear all
make re : to clear all and compile again (for the .h)
make val : to check leak in minishell (you have to change de PATH to your own name to use it)
make libft : to compile libft alone

## Resources

https://hackmd.io/@nszl/H1LXByIE2#introduction
https://medium.com/@elmehdielgarouaz/from-flat-to-fantastic-how-cub3ds-ray-casting-engine-transforms-2d-into-3d-647ff2f7fd4f
https://www.youtube.com/watch?v=eOCQfxRQ2pY
https://nathaan.me/projects/cub3d
https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html
https://github.com/iciamyplant/Cub3d-Linux
https://lodev.org/cgtutor/raycasting.html
https://www.youtube.com/watch?v=gID_FKfncZI
https://mintlify.wiki/ibon-ira/Cub3d/reference/architecture
http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=ray#0
https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
https://wynnliam.github.io/raycaster/news/tutorial/2019/03/23/raycaster-part-01.html
https://www.geeksforgeeks.org/computer-graphics/dda-line-generation-algorithm-computer-graphics/

For the textures
https://ismailassil.medium.com/ray-casting-c-8bfae2c2fc13

couleurs
https://blog.openreplay.com/fr/rgb-vers-hex/

Sprites
https://lodev.org/cgtutor/raycasting3.html

Autre 
https://lodev.org/cgtutor/raycasting4.html
