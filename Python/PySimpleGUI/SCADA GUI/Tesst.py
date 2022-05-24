import urllib.request
import requests
import threading
import json




def thingspeak_post(temp,hum):
    threading.Timer(15, thingspeak_post).start()
    URl = 'https://api.thingspeak.com/update?api_key='
    KEY = 'BE77LKAQNDUFXGUT'
    HEADER = '&field1={}&field2={}'.format(temp, hum)
    NEW_URL = URl + KEY + HEADER
    print(NEW_URL)
    data = urllib.request.urlopen(NEW_URL)
    print(data)


if __name__ == '__main__':
    thingspeak_post()