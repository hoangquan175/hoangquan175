import PySimpleGUI as sg
import serial
import time



arduino = serial.Serial('COM11',9600)



sg.theme('Topanga')
layout = [
    [sg.Text('HE THONG GIAM SAT TUOI CAY', size=(30, 1), justification='center', font=("Helvetica", 25), relief=sg.RELIEF_RIDGE)],
    [sg.Frame('Thong So', [[sg.Text('Nhiet do', size=(10, 1), justification='center', font=("Helvetica", 10)),sg.Text('Do am', size=(10, 1), justification='center', font=("Helvetica", 10))],
                        [sg.Button('30', size=(10, 1), font=("Helvetica", 10),key='temp'),sg.Button('35', size=(10, 1), font=("Helvetica", 10),key='hum')]]),
    sg.Frame('Trang Thai Dong Co', [[sg.Text('MODE :', font=("Helvetica", 10)),sg.Text('Auto', font=("Helvetica", 10),key='mode',text_color="purple")],
                        [sg.Text('Dong Co:', font=("Helvetica", 10)),sg.Text('Running...', font=("Helvetica", 10),text_color='green',key='DC_Status')]])
     ],
    [sg.Text('Bang Dieu Khien')],
    [sg.Text('Che Do Dieu Khien'),sg.InputOptionMenu(('Auto', 'Manual'),key='ModeOption'),sg.Button('Confirm')],
    [sg.Text('Dieu Khien Dong Co'),sg.Button('ON'),sg.Button('OFF')],
    [sg.Text('Tag History')],
    [sg.MLine(key='TagHistory'+ sg.WRITE_ONLY_KEY,size=(80, 10))],
    [sg.Exit()]

]



window = sg.Window('He Thong Giam Sat Tuoi Cay', layout, default_element_size=(40, 1), grab_anywhere=False)
while True:
    data = arduino.readline()
    data = str(data)
    temp = data[2]+data[3]
    hum = data[5]+data[6]

    dc_sta = data[8]
    localtime = time.asctime( time.localtime(time.time()) )


    window.refresh()
    event,values = window.read(timeout=500)
    window['temp'].update(temp)
    window['hum'].update(hum)
    window['TagHistory'+sg.WRITE_ONLY_KEY].print(str(localtime)+'-temp:'+temp+'-hum:'+hum+'-'+dc_sta)

    if event == 'Confirm':
        if values['ModeOption'] == 'Manual':
            window['mode'].update('Manual')
        else:
            window['mode'].update('Auto')



    if dc_sta == '1':
        window['DC_Status'].update('Running')
    if dc_sta =='0':
        window['DC_Status'].update('Stopped')


    if values['ModeOption'] == 'Manual':
        if event == "ON":
            arduino.write(bytes('1', 'utf-8'))
            time.sleep(0.005)
        if event == "OFF":
            arduino.write(bytes('2', 'utf-8'))
            time.sleep(0.005)
    if values['ModeOption'] == 'Auto':
        arduino.write(bytes('3', 'utf-8'))
        time.sleep(0.005)

    if event == sg.WIN_CLOSED or event == 'Exit':
        break




arduino.close()
window.close()

