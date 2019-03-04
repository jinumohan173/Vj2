import RPi.GPIO as GPIO
from time import sleep
import datetime
from firebase import firebase
import json
import requests


firebase_url = 'https://sample-343d2.firebaseio.com'
GPIO.setmode(GPIO.BCM)
GPIO.cleanup()
GPIO.setwarnings(False)
GPIO.setup(21,GPIO.OUT)

#firebase = firebase.FirebaseApplication('https://raspberryjinu.firebaseio.com/', None)
#firebase.put("/Control", "/device1", "on")

firebase = firebase.FirebaseApplication('https://sample-343d2.firebaseio.com')



temperature_location = 'sample-343d2/messages/'   







while True:
	#firebase.post("https://sample-343d2.firebaseio.com/messages",data=json.dumps(data))
	firebase.put("https://sample-343d2.firebaseio.com","buttons2/buttonState","1100")
	#result = requests.post(firebase_url + '/' + temperature_location  , data=json.dumps(data))
	print("https://sample-343d2.firebaseio.com","","0000")
	button1 = firebase.get("/buttons/buttonState", None)
	#button = firebase.get("/buttonOne", None)
	#button2 = firebase.get("/buttonTwo/two00", None)
	#button3 = firebase.get("/buttonThree/three00", None)
	#button4 = firebase.get("/buttonFour/four00", None)
	#button5 = firebase.get("/buttonFive/five00", None)
	
	print("put method")
	b1= str(button1)
	#b=str(button)
	#print(b[:6])
	print("b1 ",b1)
	#b2= str(button2)
	#b3= str(button3)
	#b4= str(button4)
	#b5= str(button5)
	
	#print(button1+"\t"+button2+"\t"+button3+"\t"+button4+"\t"+button5)
	print(button1)
	if(button1=="on"):
		print("led on")
		GPIO.output(21,GPIO.HIGH)
	if(button1=="off"):
		print("led off")
		GPIO.output(21,GPIO.LOW)
		
	sleep(0.1)
	
	#firebase.post("https://sample-343d2.firebaseio.com"",/sample-343d2","/messages", "hellooo")
	#result = firebase.post("https://sample-343d2.firebaseio.com/sample-343d2""/messages", {"content":"rasp","date":"kjhsdf"})

		
        #Retrieve sleep time from firebase and continue the loop
        #sleepTime = firebase.get("/Settings/info_update_time_interval", None)
        #sleepTime = int(sleepTime)

	





