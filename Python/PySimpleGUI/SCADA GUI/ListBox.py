import PySimpleGUI as sg
choices = ('Red','Green','Blue','Yellow','Orange','Purple','Chartreuse')

layout = [
    [sg.Text("What is your favorite color ?")],
    [sg.Listbox(choices,size=(15,len(choices)),key ='-COLOR-')],
    [sg.Button('OK')]
]

window = sg.Window('Pick a color', layout)

while True:
    event,values = window.read()
    if event == sg.WIN_CLOSED:
        break
    if event =='OK':
        if values['-COLOR-']:
            sg.popup(f"Your favorite color is {values['-COLOR-'][0]}")
window.close()