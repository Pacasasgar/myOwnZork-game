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
