#BELEN, Alarcon Ace | 2018-04736

#Initializes board
board = [[u'\xb7', u'\xb7', u'\xb7'], [u'\xb7', u'\xb7', u'\xb7'], [u'\xb7', u'\xb7', u'\xb7']]

def printBoard():
    """
    Displays the content of the board
    """
    print ('\n') 
    print (u'\xb7', u'\xb7', u'\xb7', u'\xb7', u'\xb7', u'\xb7')
    print (u'\xb7', u'\xb7', 0, 1, 2, u'\xb7')
    print (u'\xb7', 0, board[0][0], board[0][1], board[0][2], u'\xb7')
    print (u'\xb7', 1, board[1][0], board[1][1], board[1][2], u'\xb7')
    print (u'\xb7', 2, board[2][0], board[2][1], board[2][2], u'\xb7')
    print (u'\xb7', u'\xb7', u'\xb7', u'\xb7', u'\xb7', u'\xb7', '\n')

def emptyBoard():
    """
    Replaces content of the board with a non whitespace character
    """
    global board
    board = [[u'\xb7', u'\xb7', u'\xb7'], [u'\xb7', u'\xb7', u'\xb7'], [u'\xb7', u'\xb7', u'\xb7']]
    printBoard()

def setCoordinates():
    """
    Prompts coordinate inputs from the player, returns the validated values
    """
    absx = input("Enter x coordinate: ")
    while absx.isdigit() == False or not 0 <= int(absx) <= 2:
        absx = input("Please enter a valid x coordinate: ")
    ordy = input("Enter y coordinate: ")
    while ordy.isdigit() == False or not 0 <= int(ordy) <= 2:
        ordy = input("Please enter a valid y coordinate: ")
    return int(absx), int(ordy)

def placePlayer1():
    """
    Checks if Player1's coordinate inputs is valid and places X on the defined point
    """
    print("Destroy your friend Player1!")
    play = setCoordinates()
    x = play[1]
    y = play[0]
    if board[x][y] == "X" or board[x][y] == "O":
        print("That space is already occupied. Try again.")
        placePlayer1()
        return -1
    else:
        board[x][y] = "X"
        return 0

def placePlayer2():
    """
    Checks if Player2's coordinate inputs is valid and places O on the defined point
    """
    print("Destroy your friend Player2!")
    play = setCoordinates()
    x = play[1]
    y = play[0]
    print(play)
    if board[x][y] == "X" or board[x][y] == "O":
        print("That space is already occupied. Try again.")
        placePlayer2()
        return -1
    else:
        board[x][y] = "O"
        return 0

def fullBlock():
    """
    Determines if the board is full or not
    """
    count = 0
    for i in range(3):
        for j in range(3):
            if not board[i][j] == u'\xb7':
                count += 1
    if count == 9:
        return 0
    else:
        return -1

def freeElo():
    """
    Defines the win conditions for both players and determines a winner through the condition
    """
    board_filled = fullBlock()
    #Vertical win conditions
    for i in range(3):
        for j in range(3):
            if board[i][j] == board[i-1][j] == board[i-2][j] == "X":   
                print("Player1 Wins!")
                return True
    for i in range(3):
        for j in range(3):
            if board[i][j] == board[i-1][j] == board[i-2][j] == "O":  
                print("Player2 Wins!")
                return True
    #Horizontal win conditions
    for j in range(3):
        for i in range(3):
            if board[i][j] == board[i][j-1] == board[i][j-2] == "X":
                print("Player1 Wins!")
                return True
    for j in range(3):
        for i in range(3):
            if board[i][j] == board[i][j-1] == board[i][j-2] == "O":
                print("Player2 Wins!")
                return True
    #Diagonal win conditions
    if board[0][0] == board[1][1] == board[2][2] == "X" or board[1][1] == board[0][2] == board[2][0] == "X":
        print("Player1 Wins!")
        return True
    elif board[0][0] == board[1][1] == board[2][2] == "O" or board[1][1] == board[0][2] == board[2][0] == "O":
        print("Player2 Wins!")
        return True
    #No winner
    elif board_filled == 0:
        print("It\'s a Draw.")
        return True
    else:
        return False

def main():
    """
    Main program for the game TicTacToe
    """
    print ("\n", "Game On!")
    game_status = False
    emptyBoard()
    while game_status == False:
        placePlayer1()
        printBoard()
        game_status = freeElo()
        if game_status == True:
            break
        placePlayer2()
        printBoard()
        game_status = freeElo()
        if game_status == True:
            break
    game_status = input("Type GO if you want to play again  ")
    if game_status.lower() == "go":
        game_status = False
        main()

if __name__ == "__main__":
    main()