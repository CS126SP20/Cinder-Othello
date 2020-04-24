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
    
 - **04/24/2020** Got white piece to show up on the tile that was clicked
 by the user, but it does not stay at that tile when another tile is clicked.
 I also added music to the game that plays non-stop.
    - Need to figure out issues when I try to change the color of pieces
    to black (the whole screen becomes black)