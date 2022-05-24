import PySimpleGUI as sg

sg.theme('Topanga')

layout = [
    [sg.Text('Please enter your Name,Address,Phone')],
    [sg.Text('Name',size=(15,1)),sg.InputText()],
    [sg.Text('Address',size=(15,1)),sg.InputText()],
    [sg.Text('Phone',size=(15,1)),sg.InputText()],
    [sg.Submit(),sg.Exit()]
]
window = sg.Window('Simple data entry window', layout)
while True:
    event,values = window.read()
    if event =='Submit':
        print(event, values[0], values[1], values[2])
    if event == sg.WIN_CLOSED or event == 'Exit':
        break
window.close()
