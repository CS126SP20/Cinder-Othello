# Development

---

 - **04/19/20** Set up sqlite3 and sqlite_modern_cpp libraries with project
   - [x] Still need to update schemas and test query entering data

 - **04/20/20** Updated schema for database and got queries working

 - **04/21/20** Add method to print text to Cinder screen
   - [x] Need to figure out how to display an image on to the screen; 
   currently getting errors
   
 - **04/22/20** Got game board png to become visible on the screen and 
 learned how to display circles for the game
    - [x] Need to figure out how to place circles at certain spots on the board
    when the player clicks
    
 - **04/23/2020** Created a 2D vector to represent the board state and
 populated it with blank strings initially to represent empty tiles
    - [x] Need to figure out how to have pieces display when the user clicks
    a certain tile; have figured out the logic for this, now I need to
    implement
    - [x] Need to clean up my code and make sure I'm modularizing as I go
    
 - **04/24/2020** Got white and black pieces to show up on the tile 
 that was clicked by the user. I also added music to the game 
 that plays non-stop. Have some pieces flipping, but the algorithm 
 is still in the development stage.
    - [x] Getting a random bug where the whole screen turns black for 
    some reason; need to find the bug and fix.
    - [x] Need to work on flipping the pieces to make the game more playable
    - [x] Need to have somewhere to display the user score and winner
    
 - **04/25/2020** Fixed the bug of screen turning all black. Got 
 the tile flipping algorithm fully implemented. Also added method
 to calculate the player scores.
    - [x] Need to try to modularize the tile flipping 
    algorithm into methods to make the code more readable and clean
    - [x] Next step is to add a method that checks for valid moves
    and allows the user to see what those valid moves are
    - [x] Look into creating a Logic class, if necessary
    - [x] Need to look into how I want to display scores, whose turn
    it is, etc.
    
 - **04/26/2020** Added method to check for valid move and player
 can only place pieces where the move is valid.
    - [x] I want to next display pieces on the board that are valid moves 
    for the user
    
 - **04/27/2020** Successfully added method to display valid moves for 
 users. Added functionality so that if there are no valid moves, the 
 turn becomes the other player's.
    - [x] Need to add method to check for game over and add winner to 
    SQL database
    - [x] Need to add a panel on the side to display scores and other
    information
    - [x] Add sound when player moves
    - Need to start updating the README
    - [x] Need to start making code testable
    - [x] Add reset functionality
    
 - **04/28/2020** Added method to check for game over and add
 whether black or white player won to the sql database, as well
 as score. Added a panel on the side of the game to display score
 and messages to users. Added sound effects for placing a piece
 and for game over. Added reset button and method.
    - [] Add documentation in header files for methods
 
 - **04/30/2020** Added documentation for methods in myapp. Created 
 logic.cc and logic.h for logical methods that would be easier to
 use in their own file and can be tested. Reset functionality 
 fully working.
    - [] Update README.md
    - [x] Add PROPOSAL.md
    - [] Add more unit tests and create a helper method to make them 
    easier to read
    - [] Add more comments throughout code, where necessary
 
 - **05/01/2020** Added PROPOSAL.md to project. Improved README.md
    - [] Migrate appropriate methods from my_app.cc to logic.cc
    and then add any changes to parameters, if necessary
    
 - **05/02/2020** 
    
 
    