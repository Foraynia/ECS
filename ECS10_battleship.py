#this program is a one player version of battleship that allows the user play against an AI.
#there are different AIs and the board, ship sizes is variable. 
import sys
import random

def make_board(width, height): #this function create an empty board
    board = [] #initialize 
    for row in range(0, height): #create each row and append it to the empty list
        row = ["*"] * width
        board.append(row)
    return board#return a list of lists

def display_board(board, width):#this function diaplay the board (of user or AI)
    for col_num in range(0, width): # print the coloum number for each coloum
        print("", col_num, end = "")
    print()

    for row_num, row in enumerate(board):#print each line with row number in front of it
        print(row_num, " ".join(row))
        
        
def game_over(board_of_user, board_of_AI, board, width):#test if a game is over
    #return to the two functions
    return user_win(board_of_AI, board, board_of_user, width) or AI_win(board_of_user, board, width)


def AI_win(board_of_user, board, width):#test if the AI wins the game
    amount = 0 #initialize
    for row in board_of_user: #testing every piece on the board
        for piece in row:
            if (piece != "X" and
                piece != "O" and
                piece != "*"):
                amount += 1 #if there is a ship, then update value

    if amount > 0: #when there is still any ship, then AI not win
        return False 
    else: #if no ship on user's board, then display the board and result. 
        print("Scanning Board")
        display_board(board, width)
        print("\nMy Board")
        display_board(board_of_user, width)
        print("The AI wins.")
        return True

def user_win(board_of_AI, board, board_of_user, width):#test if the user wins the game
    amount = 0#initialize
    for row in board_of_AI:#testing every piece on the board
        for piece in row:
            if (piece != "X" and
                piece != "O" and
                piece != "*"):
                amount += 1#if there is a ship, then update value

    if amount > 0:#when there is still any ship, then user not win
        return False
    else:#if no ship on AI's board, then display the board and result 
        print("Scanning Board")
        display_board(board, width)
        print("\nMy Board")
        display_board(board_of_user, width)
        print("You win!") 
        return True


def place_ships_on_board(file, board_of_user, width, height):#this function place ships on user's board
    with open(file.strip()) as locations:#open the file contains the ships
        location = locations.readlines()#read all the lines in the file
    locations.close()#close the file
    length_of_boats = {}#initialize
    for line in location:#loop over each line in the contents
        line = line.split()#split them 
        symbol = line[0]#the first element is the symbol
        if int(line[1])<int(line[3]):#these steps use to find the staring/ending row/colume
            start_row = int(line[1])#in order to avoid the player put his ships from right to left
            end_row = int(line[3])#or bottom to top
            if int(line[2])< int(line[4]):#I use them to detemine which is starting point
                start_col = int(line[2])#and which is the ending one
                end_col = int(line[4])
            else: 
                start_col = int(line[4])
                end_col = int(line[2])
        else: 
            start_row = int(line[1])
            end_row = int(line[3])
            if int(line[2])< int(line[4]):
                start_col = int(line[2])
                end_col = int(line[4])
            else: 
                start_col = int(line[4])
                end_col = int(line[2])

        for piece in range(0, len(length_of_boats)+1):#check if any symbol is appeared before
            if symbol in length_of_boats:#if so, then display result and quit the gmae
                print("Error symbol %s is already in use. Terminating game" %symbol)
                sys.exit(0)           

        if symbol == "x" or symbol == "X" or symbol == "o" or symbol =="O" or symbol == "*":
            #check if the ships have invalid symbol, if so, display result and quit
            print("Error %s is not a valid symbol for a ship. Terminating game." %symbol)
            sys.exit(0)

        if end_col > width or end_row > height or start_col<0 or start_row<0:
            #check if the ships are placed out side the board
            print("Error %s is placed outside of the board. Terminating game." %symbol)
            sys.exit(0)#if so, display result and quit

        if start_row != end_row and start_col != end_col:
            #check if the ships are placed diagonally
            print("Ships cannot be placed diagonally. Terminating game.")
            sys.exit(0)

        if start_row == end_row: #the ship is placed horizontally
            for piece in range(int(start_col), int(end_col+1)):
                if board_of_user[start_row][piece] != "*":#if there is already a ship on that spot
                    print("There is already a ship at location %d, %d. Terminating game." %(start_row, piece))
                    sys.exit(0)#display result and quit

                board_of_user[start_row][piece] = symbol #if no, then change the user's board
                length_of_boat = int(end_col) - int(start_col) + 1 #calculate how the boat is
                length_of_boats[symbol] = length_of_boat#update the name and length of the boat
 
        elif start_col == end_col:#the ship is placed horizontally
            for piece in range(start_row, end_row+1):
                if board_of_user[piece][start_col] != "*":#check if the spot is taken already
                    print("There is already a ship at location %sd, %d. Terminating game." %(start_row, piece))
                    sys.exit(0)
                
                board_of_user[piece][start_col] = symbol#if not, change the board
                length_of_boat = int(end_row) - int(start_row) + 1
                length_of_boats[symbol] = length_of_boat#and update the name and length of the boat
 
    return length_of_boats #return the dictionary contains the length and name of all boats


def valid_place(direction, row_num, col_num, height, width, length, board_of_AI):
    #this function check if the random choosen number can be used
    if direction =="vert":
        for row in range(row_num, row_num+length):
            if board_of_AI[row][col_num] != "*": #when something is on that spot, then it's not valid
                return False
        else:
            return True
    if direction =="horz":
        for col in range(col_num, col_num+length):#not valid if not a empty spot
            if board_of_AI[row_num][col] != "*":
                return False
        else:#if the spots are valid, return True
            return True
    

def place_ships_on_AI_board(length_of_boats, board_of_AI, height, width):
    #this function place ships on AI's board
    for boat in sorted(length_of_boats):#put ship in sorted order
        length = length_of_boats[boat]#get the ship size and name
        direction = random.choice(['vert', 'horz'])#choose a direction
        if direction == "vert":
            row_num = random.randint(0, height-length)#choose a row and col number
            col_num = random.randint(0, width-1)
        else:
            row_num = random.randint(0, height-1)
            col_num = random.randint(0, width - length)


        while not valid_place(direction, row_num, col_num, height, width, length, board_of_AI):
            #when the places are not valid, then use random to choose spots again
            length = length_of_boats[boat]
            direction = random.choice(['vert', 'horz'])
            if direction == "vert":
                row_num = random.randint(0, height-length)
                col_num = random.randint(0, width-1)
            else:
                row_num = random.randint(0, height-1)
                col_num = random.randint(0, width - length)

                
        if direction == "vert":#when direction is vertical
            for row in range(row_num, row_num + length):#change everything from the starting number
                board_of_AI[row][col_num] = boat#to the end of the boats on the board
            print("Placing ship from %d,%d to %d,%d." %(row_num, col_num, row_num+length-1, col_num))#display it
        elif direction == "horz":#when the direction is horizaontal
            for col in range(col_num, col_num+length):#place the ships on the board
                board_of_AI[row_num][col] = boat
            print("Placing ship from %d,%d to %d,%d." %(row_num, col_num, row_num, col_num+length-1))
        
    return board_of_AI#return the AI's board
    
def valid_location(place, height, width, board):#this function check if the user's location is valid
    if len(place) != 2:#the length has to be 2
        return False
    elif not place[0].isdigit() or not place[1].isdigit():#the input shoud be numbers
        return False
    elif int(place[0]) > height-1 or int(place[1]) > width-1:#the input shoud be inside the board
        return False
    elif board[int(place[0])][int(place[1])] != "*":#the spot has not been played before
        print("You hace already place something here.")
        return False
    else:
        return True
    


def battle_ship():#thie is the main function of the game
    seed = input("Enter the seed: ")#ask for a seed value
    while not seed.strip("-").isdigit():#if it is not valid, ask for a new one
        seed = input("Enter the seed: ")
        
    width = input("Enter the width of the board: ")#ask for a width of board
    while (not width.isdigit()) or (not int(width) >0):#ask for a new one if not valid
        width = input("Enter the width of the board: ")
        
    height = input("Enter the height of the board: ")#ask for a height of the board
    while (not height.isdigit()) or (not int(height)>0):#ask for a new one if not valid
        height = input("Enter the height of the board: ")

    width = int(width)#change them to integers
    height = int(height)
        
    file = input("Enter the name of the file containing your ship placements: ")#ask for a file name
    
    print("Choose your AI. \n1. Random \n2. Smart \n3. Cheater")#print the options
    choice = input("Your choice: ")#and ask for a choice
    while (not choice.isdigit()) or (not 1<= int(choice)<=3):#if the choice is not valid
        print("Choose your AI. \n1. Random \n2. Smart \n3. Cheater")#ask for a new one
        choice = input("Your choice: ")

    random.seed(int(seed))#use the seed before any other random call
    
    board = make_board(width, height)#make a board that displayed AI's board on screen
    board_of_user = make_board(width, height)#create boards for user and AI
    board_of_AI = make_board(width, height)
    length_of_boats = place_ships_on_board(file, board_of_user, width, height)#place ships on both boards
    place_ships_on_AI_board(length_of_boats, board_of_AI, height, width)

    
    positions_of_user_ship = []#initialize
    for y, row in enumerate(board_of_user):#append all spots that contain the user's ship
        for x, piece in enumerate(row):#this is for the cheater AI
            if piece != "*":
                positions_of_user_ship.append([y, x])
                

    list_of_positions = []#initialize
    list_of_place = []
    for row in range(0, height):#append every possible spot that AI can aim
        for col in range(0, width):
            list_of_positions.append([row, col])

    turn = random.randint(0, 1)#choose the turn 
    while not game_over(board_of_user, board_of_AI, board, width):#when the game is not over
        
        if turn == 0:#0 means user's turn
            print("Scanning Board")#display boards
            display_board(board, width)
            print("\nMy Board")
            display_board(board_of_user, width)
        
            place = input("Enter row and column to fire on separated by a space: ")#get a place to fire from user
            place = place.split()
            while not valid_location(place, height, width, board):#if the place is not valid, ask for a new one
                place = input("Enter row and column to fire on separated by a space: ")
                place = place.split()

            row = int(place[0])#make the input integers
            col = int(place[1])


            if board_of_AI[row][col] == "*":#if AI's board doesnt have a ship on the spot
                board_of_AI[row][col] = "O"#then update the boards that displayed and also the hidden AI's board
                board[row][col] = "O"
                print("Miss!")
            else:#if ther is a ship on AI's board on that spot
                symbol = board_of_AI[row][col]
                board_of_AI[row][col] = "X"#then update the boards
                board[row][col] = "X"
                amount = 0#initialize
                for row in board_of_AI:#if a ship is completely sunk, display the result
                    for piece in row:
                        if piece == symbol:
                            amount += 1#it means a ship is not completely sunk
                if amount == 0:
                    print("You sunk my %s" %symbol)
                if amount != 0:#if not, then display Hit!
                    print("Hit!")
            turn = (turn+1)%2#update turn


        elif turn == 1:#1 means AI's turn
            if choice == "1":#normal AI choice
                place = random.choice(list_of_positions)#choose a position from the list we created before
                list_of_positions.remove(place)#and remove it from the list
                row = int(place[0])#get row and col number 
                col = int(place[1])
                print("The AI fires at location (%d, %d)" %(row, col))#display it

                if board_of_user[row][col] == "*":#if no ship on user's board on this spot
                    board_of_user[row][col] = "O"#display result and update board
                    print("Miss!")
                else:#if there is a ship on it
                    symbol = board_of_user[row][col]
                    board_of_user[row][col] = "X"#then update the board
                    amount = 0
                    for row in board_of_user:#check if the ship is completely sunk
                        for piece in row:
                            if piece == symbol:
                                amount += 1
                    if amount == 0:#display the result
                        print("You sunk my %s" %symbol)
                    if amount != 0:
                        print("Hit!")

            elif choice == "2":#Smarter AI
                if list_of_place == []:#if there is no more spots need to be check (Hunt mode)
                    place = random.choice(list_of_positions)#chose a position 
                    list_of_positions.remove(place)#and remove it from the list
                    row = int(place[0])
                    col = int(place[1])
                    print("The AI fires at location (%d, %d)" %(row, col))
                   
                if list_of_place != []:#if it is on the Destroy mode
                    place = list_of_place[0]#then chose the first spot on the list
                    if place in list_of_positions:#if the position is on list
                        list_of_positions.remove(place)#remove it
                    list_of_place.remove(place)#remove it from both list
                    row = place[0]
                    col = place[1]
                    print("The AI fires at location (%d, %d)" %(row, col))


                if board_of_user[row][col] =="*":#if miss, then update board
                    board_of_user[row][col] = "O"
                    print("Miss!")
                else:#if hit, goes to destroy mode
                    symbol = board_of_user[row][col]
                    board_of_user[row][col] = "X"#append possible spots(above, below, to the left/right) into the list
                    #the spots have to be inside the board, and not fired yet in order to add it to the list
                    if (row-1>=0) and (board_of_user[row-1][col] !="X") and (board_of_user[row-1][col] !="O") and ([row-1, col] not in list_of_place):
                        list_of_place.append([row-1,col])
                    if row+1<height and board_of_user[row+1][col] !="X" and board_of_user[row+1][col] !="O" and [row+1, col] not in list_of_place:
                        list_of_place.append([row+1,col])
                    if col-1>=0 and board_of_user[row][col-1] !="X" and board_of_user[row][col-1] !="O" and [row, col-1] not in list_of_place:
                        list_of_place.append([row,col-1])
                    if col+1< width and board_of_user[row][col+1] !="X" and board_of_user[row][col+1] !="O" and [row, col+1] not in list_of_place:
                        list_of_place.append([row,col+1])
                    amount = 0
                    for row in board_of_user:
                        for piece in row:
                            if piece == symbol:
                                amount += 1
                    if amount == 0:# if ship is completely sunk, then display reult
                        print("You sunk my %s" %symbol)
                    if amount != 0:#if not, display Hit!
                        print("Hit!")


            elif choice == "3":#Cheater AI
                place = positions_of_user_ship[0]#AI has all the spot where contains a ship
                positions_of_user_ship.remove(place)#remove the place
                row = int(place[0])
                col = int(place[1])
                print("The AI fires at location (%d, %d)" %(row, col))

                if board_of_user[row][col] == "*":#display result if miss
                    board_of_user[row][col] = "O"
                    print("Miss!")
                else:#display result if hit a ship
                    symbol = board_of_user[row][col]
                    board_of_user[row][col] = "X"
                    amount = 0
                    for row in board_of_user:
                        for piece in row:
                            if piece == symbol:
                                amount += 1
                    if amount == 0:
                        print("You sunk my %s" %symbol)
                    if amount != 0:
                        print("Hit!")
       

            turn = (turn+1)%2#update the turn 



battle_ship()#run the whole program 
