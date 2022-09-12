# DurakPCGame
This project was created as a coursework on C++ (particularly, OOP) in 2021, but only recently I got acquainted with such a great technology as GitHub. Still, it's 100% my work, so I decided that later is better than never - and pushed it right here.

## So, what is it?
Durak,  Duren', or, as it should be translated, "A fool", is a popular card game in Ukraine and some other Eastern European countries.
The rules are quite simple. Here they are, modified to User-vs-Computer version of the game, which I have developed (and if You forget the rules, You can easily find them in Rules section of the Start Menu): 
- At the start the deck is shuffled, the Trump is chosen and You and Your opponent (Computer) get 6 cards from the deck. They lay in line in front of You, in Your "hand".
- You can't see the opponent's cards unless they're on the board, "in game".
- The game consists of rounds. After every round if You lack some cards to 6, You get some from the deck.
- During each round someone (you or Computer, by turns) chooses cards to attack (up to 4 of the same nominal - f.e., if you have 4 Aces, it's allowed to use all of them in Your attack simultaneously or attack with any number of Aces from 1 to 3) and the opponent has to defend with cards of the same suit and higher nominal, or use a Trump card
- In my version, to choose the particular card You can type its position in your "hand" (numbered from left to right)
- If the player doesn't have appropriate cards to defend, he takes everything on board in his "hand".
- The one who doesn't have any cards when the deck is over is the winner.
And after the end of the game You return to the main menu.

Simple, right? :)

My cousin taught me this game when I was five, so I believe You, a GitHub user, will definitely figure this out.

To make the game even more interesting I've created 3 difficulty levels: Your opponent can be Dummy, CleverForever or even Megamind. They are differ on the ability/frequency of going against the "logic" and taking "impulsive" decisions - f.e. wasting the most powerful cards they have. 

But sometimes in the middle of an exciting game battle it becomes too hard to recall even how to choose a card to attack. For this purpose there is a text assistant at the bottom of the game desk, which reminds You what to do.

## Game interface
Here are some screenshots from the game:

### Main menu
![main menu](https://user-images.githubusercontent.com/99298961/189718690-e33527aa-52bb-4d83-a634-80c7877800ca.jpg)

### Rules section
![new rules](https://user-images.githubusercontent.com/99298961/189718772-7703bc26-393d-4bce-8fe7-43bfb2cff5c3.jpg)

### Setting the difficulty level
![Opponent](https://user-images.githubusercontent.com/99298961/189719798-dc8973e9-88ef-4f5f-b182-b30a00cecd4f.jpg)

### Round gameplay
![Гра початок](https://user-images.githubusercontent.com/99298961/189721232-d65db8bd-3eda-4ceb-bc14-2a845af8aae9.jpg)
![Opponent Dummy](https://user-images.githubusercontent.com/99298961/189719963-9e468fc2-d95a-4083-9f73-1707019aa989.jpg)

### Messages about the end of the game
![Комп'ютер виграв](https://user-images.githubusercontent.com/99298961/189723619-e048df6d-510d-4789-a4b6-3dc19f825e47.jpg)

![Користувач виграв](https://user-images.githubusercontent.com/99298961/189721417-dff3d540-67f9-411b-bb2b-5926ab348bb4.jpg)

![Нічия](https://user-images.githubusercontent.com/99298961/189721449-e0cd05d3-480c-4529-a7ee-005a04c0308f.jpg)

##Key points of creation
I used these libraries to create the game: windows.h, conio.h, time.h and STL

Here is the class diagram of my project (in UML):
![image](https://user-images.githubusercontent.com/99298961/189722819-20e9833c-882d-4f0c-a783-6e1a4e1aef93.png)

And here is the block diagram:
![image](https://user-images.githubusercontent.com/99298961/189723088-99ae132e-2211-487f-a0eb-e976648087ea.png)

### Hope You've enjoyed my project!


