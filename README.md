# My Own Zork Game

----------------------------------------------------------------
Author: Pau Casas Garcia

E-mail: pacasasgar@gmail.com  

Repository: https://github.com/Pacasasgar/myOwnZork-game

License: GNU General Public License v3.0

----------------------------------------------------------------

Introduction
-------------
This 'test' has been a challenge for me. In 7 working days, I learnt C++ using online courses and adapted a base code into my own version of Zork game. I searched specifically for C++ pointers and C++ Object Oriented Programming sintax, which differs from my knowledge and experience with JAVA. It was easier after that to understand the base code structure given in the test: https://github.com/d0n3val/zork

After playing original Zork (http://textadventures.co.uk/games/view/5zyoqrsugeopel3ffhz_vq/zork) and playing the above base code, I understood all the differences. I had room to improve and modify the game as I wish in the time given. I started by fixing some bugs, like commands that were not working as expected and text styles. Then I thought my own scenario of different rooms, items and creatures and my own history.

I really enjoyed this experience and even learnt a LOT in just 7 days, considering that I also had to work during the day. I would have liked to implement more and more mechanics in the game but my knowledge and time were limited. However, I end up doing a version fixing all the bugs I encountered in my way and totally playable.

Game
-------
In my game you incarnate a Bounty Hunter adventurer in a medieval fantasy world. An evil Necromancer is walking around using dark magic and you must stop him. The objective of the game is to find, attack and defeat the Necromancer without dying. During your game session you will find items and enemies, some of them optionals, that will reward you and make you stronger with better weapons and armour. There are 6 playable rooms connected with 5 exits in total among them (one exit at a time between two rooms).

Guide - How to play
--------------------
In this game, the player is always standing in a 'Room'. You are the player so the game waits for your next command in order to move on. Here is a list of all the commands (actions) that are understood by the game (not case sensitive):

-'look' or 'l' --> You can look pretty much every entity in the game (Rooms, Exits, Creatures, Items and Yourself). Using 'look' alone will trigger the actual's room (name + description). Using 'look me' will also describe yourself. Most common usage is to look other things. TIP: Try to look everything the first time you play as you may find important information or just some jokes. Examples of 'look [+ name]: 'look shortsword', 'look zombie', 'look north'...

-'north' or 'n' --> If your actual room has an exit northside, you will move to the room connected with that exit.

-'south' or 's' --> If your actual room has an exit southside, you will move to the room connected with that exit.

-'west' or 'w' --> If your actual room has an exit westside, you will move to the room connected with that exit.

-'east' or 'e' --> If your actual room has an exit eastside, you will move to the room connected with that exit.

-'down' or 'd' --> If your actual room has an exit downside, you will move to the room connected with that exit.

-'up' or 'u' --> If your actual room has an exit upperside, you will move to the room connected with that exit.

-'stats' --> You can check your actual hit points, damage and protection with this command.

-'inventory' --> It shows the list of every item you are holding with yourself.

-'go' --> By itself it does nothing. It needs to be followed by a direction, but it works same way as the direction commands mentioned above. If your actual room has an exit on the direction mentioned, you will GO to the room connected with that exit. Example: 'go north'.

-'take' or 'pick' --> Is there an item on the floor? Maybe an item inside another item? this action is also very important. You can take pretty much every time you could find. It does not work by itself, you have to specify the name of the item you want to take and also the container if it is inside something. Examples: 'take shortsword', 'take manor-key from locket'. It will not work if your specified item is not there or you do not have it in the inventory.

-'drop' or 'put' --> It works exactly the same as 'take' but does the opposite. You can drop items to the floor or inside other items. Examples: 'drop locket', 'drop paper into mailbox'. Again, there must exist an item with the specified name exactly.

-'equip' or 'eq' --> It only works followed by an item name tagged as WEAPON or ARMOUR. You equip that item. It must be in your inventory or in the room. Example: 'equip shortsword'.

-'unequip' or 'uneq' --> It works exactly the same as 'equip' but does the opposite. You can unequip items that you are actually wearing. It does not count if the item is in your inventory, it has to be EQUIPED. Example: 'unequip shortsword'.

-'examine' or 'ex' --> By itself it does nothing. It needs to be followed by a CREATURE. It does not work on other Entities (items, rooms, exits...), just creatures. It gives information about a creature standing in the same room as yours. You can check its stats and items. Example: 'examine wolf'.

-'attack' or 'at' --> You need to specify a target after an attack command. It needs to be a target standing in the same room as yours. You will then fight the target and the target will fight you. It will continue until someone dies or you move out the room quickly. Example 'attack skeleton'.

-'loot' or 'lt' --> It works exactly the same as 'take' but you need to specify a dead creature's corpse instead an item. It will pick up all the items that was being holded by the creature. This command is only used after you win a fight against a creature or if you find a dead corpse. Example: 'loot wolf'.

-'unlock' or 'unlk' --> This action requires more specific details. It must be followed by a destination and with the item that works as the key for that Exit to be unlocked. Always use four words with this action. Example: 'unlock north with manor-key', 'unlock down with square-key'. Note that destinations are always directions and not names. 'unlock manor with manor-key' will not work, because 'manor' is the room's name and you need the EXIT's destination (north, up, down, east...). 

-'lock' or 'lk' --> It works exactly the same as 'unlock' but does the opposite. You also need to specify which Exit (direction) you want to lock followed by the corresponding key. Using an incorrect key will not lock or unlock any exit. Example: 'lock south with keystone'.

A good tip is to investigate everything before fighting and try to understand how is the map structure. Understanding which rooms are connected by which Exits is very important. Then you can make a mental map of the place. Next section will help you to pass the game by showing you the exact commands required to win (if randomness helps you in the fights!).


Guide - How to beat the game
----------------------------
To win the game you need to defeat the Necromancer, who is in the Vault. To access the vault, you need the Vault's key dropped by the Skeleton. The shortest way to do that is using these exact commands:

-go north

-go west

-take manor-key from locket

-go east

-unlock north with manor-key

-go north

-attack skeleton

-loot skeleton

-go south

-go west

-unlock down with vault-key

-go down

-attack necromancer

13 commands in 'theory' is the shortest way to win. However it will be pretty difficult to beat the game this way. You will definitely lose your fights against the 'Skeleton' (step 7) or 'Necromancer' (step 13) using only you bare hands and no armour. By doing more steps in the process, you can ensure your victory by starting a game using these commands:

-go north

-go west

-take manor-key from locket

-go east

-unlock north with manor-key

-go north

-take broadsword

-equip broadsword

-go south

-go east

-attack wolf

-loot wolf

-equip armour

-go west

-go north

-attack skeleton

-loot skeleton

-go south

-go west

-unlock down with vault-key

-go down

-attack necromancer

This time we used 22 commands in total, but you will pretty much beat the game every time. We added some steps to equip a better weapon, defeat an optional enemy (wolf) that loots a leather armour and quip it too. Now we have damage and resistance enough to defeat the Skeleton (to get the Vault's key) and the Necromancer (who is in the Vault). The combat has a bit of RNG (randomness) but you need to be very unlucky to lose again this time.

Conclusion
-----------
I hope you enjoyed the game! I really loved learning C++ by doing this Zork's adaptation. New mechanics and difficulties may arrive in the future. Good adventures, heroes!
