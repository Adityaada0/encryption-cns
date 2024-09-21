import random

def computerTranslation(computerChoice):
    if (computerChoice == 1):
        print('computer choose snake')
    elif (computerChoice == 0):
        print('computer choose gun')
    elif (computerChoice == -1):
        print('computer choose water')

def judge(youNumber, computerChoice):
    computerTranslation(computerChoice)

    if computerChoice == youNumber:
        print("Its draw")
    else:
        if( computerChoice == -1 and youNumber == 1):
            print(f"you win!")
        elif (computerChoice == 1  and youNumber == -1):
            print(f"you loss!")
        elif (computerChoice == -1 and youNumber == 0):
            print(f"you loss!")

        elif (computerChoice == 1 and youNumber == 0):
            print(f"you win!")

        elif (computerChoice == 0 and youNumber == 1):
            print(f"you loss!")
        elif (computerChoice == 0 and youNumber == -1):
            print(f"you win!")

computerChoice =random.choice([1,0,-1]) 

you = input("Enter your choice: ")

youDict = {
    's':1,
    'w':-1,
    'g':0 
}

youNumber = youDict[you]
judge(youNumber,computerChoice)

