# Tic-tac-toe

Straightforward tic-tac-toe mini-project made in C++ for educational purposes, particularly to practice vectors. 

In the first attempt, the "AI's" turn of the game was determined by randomly generating a position and then checking
that position against existing ones, and if a match was found, the duplicate would be deleted and the program
was told to generate a new position anew. It seemed that it would generate the same position dozen or hundreds of times, 
causing a "lag" in the program. Remedied this by changing the design: the "AI" is given a selection of possible positions
which are all already non-duplicated by virtue of in that list. This list is modified based on the user's input and the previous
"AI" turn. On the "AI's" turn then, it would randomly select on a list of non-duplicates, skipping the previously required
checking function and having to "brute" randomize numbers until a non-duplicate is found. 

Ideas for future development:
Create some kind of motivation for the "AI" turn that would "motivate" it to seek our three rows, columns or diagonals. 
