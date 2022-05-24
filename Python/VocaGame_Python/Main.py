import io
import os

# Quit Function
def quit_game():
    print("See you soon !!!")
    quit()

# Add vocabulary Function
def save_voca():
    if os.path.exists("voca.txt") :
        voca_file = io.open("voca.txt",mode="a",encoding = "utf-8")
    else:
        voca_file = io.open("voca.txt",mode="w",encoding = "utf-8")
    while (1):
        voca = input("New word: ")
        if voca == "###" :
            voca_file.close()
            break
        mean = input("Its mean: ")
        data = voca + ":" + mean + "\n"
        voca_file.write(data)

# Read saved vocabulary Function
def read_voca():
    if os.path.exists("voca.txt") :
        voca_file = io.open("voca.txt",mode="r",encoding="utf-8")
        for line in voca_file:
            print(line)
    else:
        print("Not Found")
# Practice vocabulary Function
def practice_voca():
    voca_file = io.open("voca.txt", mode="r", encoding="utf-8")
    ans = ""
    while ans != "@@@":
        for line in voca_file:
            if line != "":
                data = line.split(":")
                print(data[0])
                ans = input("Meaning: ")
                if ans == "@@@":
                    break
                print("Key: "+data[1])
        res_user = input("Replay ? [Y/N]: ")
        if res_user == "Y":
            voca_file.seek(0)
        else:
            ans = "@@@"



#MAIN
print("Welcome to my game")
while(1):
    print("========================================================================")
    print("1) Practice vocabulary")
    print("2) Add vocabulary")
    print("3) Your saved vocabulary")
    print("4) Quit")
    ans_user = input("Your choose ? : ")

    if ans_user == "4" :
        quit_game()
    if ans_user == "2" :
        save_voca()
    if ans_user == "3" :
        read_voca()
    if ans_user == "1" :
        practice_voca()