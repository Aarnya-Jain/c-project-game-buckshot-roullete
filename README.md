----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Buckshot Roulette: A Text-Based Thrill

Buckshot Roulette is a suspense-driven, text-based game inspired by Russian Roulette. Players compete against an AI opponent, Mr. Z, through multiple rounds, using resources like lives, bullets, and power-ups strategically to survive. Between rounds, mini-games offer chances to earn rewards.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Game Structure

                                   oooooooooo.  ooooo     ooo   .oooooo.   oooo    oooo  .oooooo..o ooooo   ooooo   .oooooo.   ooooooooooooo     
                                   `888'   `Y8b `888'     `8'  d8P'  `Y8b  `888   .8P'  d8P'    `Y8 `888'   `888'  d8P'  `Y8b  8'   888   `8     
                                   888     888  888       8  888           888  d8'    Y88bo.       888     888  888      888      888          
                                   888oooo888'  888       8  888           88888[       `"Y8888o.   888ooooo888  888      888      888          
                                   888    `88b  888       8  888           888`88b.         `"Y88b  888     888  888      888      888          
                                   888    .88P  `88.    .8'  `88b    ooo   888  `88b.  oo     .d8P  888     888  `88b    d88'      888          
                                   o888bood8P'     `YbodP'     `Y8bood8P'  o888o  o888o 8""88888P'  o888o   o888o  `Y8bood8P'      o888o         
                                                                                                              
                                                                                                              
                                                                                                              
                                   ooooooooo.     .oooooo.   ooooo     ooo ooooo        ooooo        oooooooooooo ooooooooooooo oooooooooooo
                                   `888   `Y88.  d8P'  `Y8b  `888'     `8' `888'        `888'        `888'     `8 8'   888   `8 `888'     `8
                                   888   .d88' 888      888  888       8   888          888          888              888       888        
                                   888ooo88P'  888      888  888       8   888          888          888oooo8         888       888oooo8   
                                   888`88b.    888      888  888       8   888          888          888    "         888       888    "   
                                   888  `88b.  `88b    d88'  `88.    .8'   888       o  888       o  888       o      888       888       o
                                   o888o  o888o  `Y8bood8P'     `YbodP'    o888ooooood8 o888ooooood8 o888ooooood8     o888o     o888ooooood8                                   

Inventory: Tracks player resources, including lives, power-ups, and money, managed through the Inventory structure.

Mini-Games: Includes Number Guessing, Wire Diffusion, and High-Low Cards, with varying risk and reward levels to help players build their resources.

Shooting Mechanic: A six-chamber gun with randomized bullet placement adds suspense, and power-ups like skip turn and guaranteed shot influence the outcome.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Key Functions

printmp(): Displays file content, used for text-based messages.

stats(): Shows current stats for both the player and Mr. Z.

minigame(): Lets players choose and play mini-games.

shoot1(): Manages shooting actions, determining if a bullet is fired.

givePowerUps(): Awards power-ups each round.

gameloop(): Core loop handling rounds, shooting, and win/loss conditions.

---------------------------------------------------------------------------------------------------------------------------------------------------

Randomization

Random elements like bullet placement and mini-game outcomes add unpredictability, enhancing replayability.

---------------------------------------------------------------------------------------------------------------------------------------------------

Feel free to fork this project and expand upon it. If you make interesting additions, please consider submitting a pull request!

------------------------------------------------------------------------------------------------------------------------------------------------------
