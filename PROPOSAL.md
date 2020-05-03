# C++ Othello

Author: Kaahan Motwani

---

For my project, I plan on creating the board game Othello, 
also known as Reversi. I played this game often growing up, 
and thought it would be interesting to see if I could make 
it in C++ using Cinder. Although my only experience with Cinder 
has been the Snake project, I hope to leverage the graphics 
features in Cinder to set up my Othello board's graphics. 
I think creating a game like this will be challenging due to 
the game being moderately complex, but a good learning 
experience for me. I'm also excited to learn more about 
Cinder and improve my general C++ skills. As of right now, 
I plan on using [SQLite](https://www.sqlite.org/index.html) 
as an external library in addition to Cinder for my project. 
I plan on using this to store the winners of the games. 

For the first week of development, I plan on setting up 
the graphics of the game. Specifically I would want to use 
Cinder to create the Othello board and populate it with the 
starting white and black pieces (circles). Another thing 
I would like to be able to implement in the first week is 
to learn and implement an onClick method so that the user 
can place a piece by clicking on the board. One player 
would be black and the other would be white.
In the second week, I plan on starting more of 
the logic of the game. Specifically, I want to be able to 
check when a game is over and someone has won or tied 
(when the entire board has filled) and also be able to flip pieces. 
I also plan to use SQLite here to store the winners. 
I anticipate the flipping of the pieces being somewhat challenging, 
as white pieces may have to be replaced with black pieces and 
vice versa, depending on the user's move. After implementing this, 
I should have a playable game. In the third week of development, 
I hope to check for valid moves and show the user what a valid move 
is, since sometimes it is difficult to tell what a valid move is. 
This is going to be a challenging step in the project. 

Some stretch goals would be to have reset functionality, users
seeing the effects of their moves when they hover over a move,
high-level graphics, and lastly an AI to play against the user, 
although these would only be if I finish early. 
For reset functionality, I would reset the game and allow 
players to play again. For hovering over functionality,
I would need to figure out how to get the mouse's position
at any given time in Cinder. I could also try to improve my UI design 
if I get time, such as a start menu that gives the game a more 
appealing look. The AI would be a smart player that would attempt 
to use optimal Othello strategy to beat the user.