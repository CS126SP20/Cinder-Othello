# Development

---

 - **04/19/20** Set up sqlite3 and sqlite_modern_cpp libraries with project
   - Still need to update schemas and test query entering data

 - **04/20/20** Updated schema for database and got queries working

 - **04/21/20** Add method to print text to Cinder screen
   - Need to figure out how to display an image on to the screen; 
   currently getting errors
   
 - **04/22/20** Got game board png to become visible on the screen and 
 learned how to display circles for the game.
    - Need to figure out how to place circles at certain spots on the board
    when the player clicks
    
 - **04/23/2020** Created a 2D vector to represent the board state and
 populated it with blank strings initially to represent empty tiles
    - Need to figure out how to have pieces display when the user clicks
    a certain tile; have figured out the logic for this, now I need to
    implement
    - Need to clean up my code and make sure I'm modularizing as I go
    
 - **04/24/2020** Got white and black pieces to show up on the tile 
 that was clicked by the user. I also added music to the game 
 that plays non-stop. 
    - Getting a random bug where the whole screen turns black for 
    some reason; need to find the bug and fix.
    - Need to work on flipping the pieces to make the game more playable
    - Need to have somewhere to display the user score and winner
    
 - **04/25/2020** Fixed the bug of screen turning all black. Have
 some pieces flipping, but the algorithm is still in the 
 development stage.
    - Need to try to implement the algorithm that appropriately
    flips pieces; maybe try to modularize into methods based on
    direction (vertical, horizontal, diagonal)