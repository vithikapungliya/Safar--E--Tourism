import requests

URL = "http://192.168.68.136:8000/lcd_display/"

while True:
    r = requests.get(url = URL)
    data=r.json()
    message=data["message"]
    if "name" in data:
        name=data["name"]
        print (f" {message} your name is {name} ")
        break

    else:
        print(message)
        