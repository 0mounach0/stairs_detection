# Stairs detection

 - Group number : 9 

 - Group members :

|   Fullname       |   Num_etu    |            email                |
|------------------|--------------|---------------------------------|
|   Mouad MOUNACH  |   21907590   |      me.mounach@gmail.com       |
|   Manil MASDOUA  |   21911531   |     masdoua.manil@gmail.com     |
|   Bilal RABIA    |   21911527   |      rabiabily@gmail.com        |


 - Project description de la base de données : ./DescriptionBaseDonnees.doc

First problem will come accross: Houghline transform will give you many lines. To get the available lines, I eliminate the lines whose y-axis values are close to each other. I decided this threshold by considering the minimum distance between two stairs.

Note: To work on an image which is taken by vertical(90 degree) to stairs will give more better results.

Here are these steps, results, and code:

 - Apply GauusianBlur to blur the image. The reason of GauusianBlur choosing instead of the others I believe that GaussianBlur has a good combination with houghline transform.
 - Apply Canny Edge detection.
 - Convert image to BGR format.
 - Apply HoughLinesP and find all possible lines
 - Apply the algorithm approach which is explained above.
 - Get the results.


