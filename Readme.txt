IDs :  
========================
+ Yonatan Csasznik - 208259077  
+ Tal Ziv - 3153356794  
+ Itay Merires - 315434001  

Bonus features:  
========================
+ "Hall Of Fame" : 
The Hall of Fame, a leaderboard showcasing top players and their achievements, that can be accessed from the main menu. It records the highest scores along with the player's name, the time they took to play, and the difficulty level they played on.
Every time you finish a game, if your score is among the top, it gets saved in the Hall of Fame. This way, you can see how you stack up against other players and strive to beat the best scores. The Hall of Fame adds an exciting competitive element, encouraging you to improve your performance and achieve higher rankings.
important ! we supply a prefilled hall of fame - we recommand to also delete "hof.bin" from the directory to reset the scoreboard.

+ Bonus Life :
The Bonus life feature rewards players with an extra life for every 15 points earned, factoring in score deductions. For example, if a player scores 13 points and loses 3, they must earn 5 more points to reach the next multiple of 15.
If a player has the maximum 3 lives, extra lives are queued and awarded when a life is lost, making it seem like lives didn’t decrease. Bonus lives are granted at every 15-point increment, adjusted for lost points, encouraging players to maintain steady progress.


Score formula :
========================
+ +2 for killing enemy
+ +10 for savig pauline
+ +20 for completing the game
+ +2 for every heart left at the end of the game
+ -5 for every live lost


Screens validation :
========================
We provide six different screens (three more than required):

First 3: "Legal" Screens
These represent valid game states, showcasing features like:
- Different border characters (wall and non-wall).
- Missing legends or invalid legend positions.
- Invalid characters or multiple non-plural entities.
- Donkey Kong adjacent to the border.
- Screen isn't 80 * 25 chars.
  etc.

Last 3: "Not Legal" Screens
These handle error cases such as:
- Failure to open the file.
- Missing Pauline instance.
- Missing Mario instance.

Additionally, in the levels menu, you can "roll" through all screens in the directory matching the regex. There’s no limit to the number of screens the game can handle.


Notice :
========================
+ The hit range of the hammer is 2 chars as allowed by amir in the forum.
+ Attached amir's approvel of bonus features and 3 people assignemt
+ Corrections from Exercise 1 submission: return to the menu at the end of the game, change the enums to enum class.
