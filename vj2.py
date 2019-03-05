import paho.mqtt.client as mqtt #import the client1
import time
import datetime
from firebase import firebase
import json
import requests


firebase_url = 'https://sample-343d2.firebaseio.com'

firebase = firebase.FirebaseApplication('https://sample-343d2.firebaseio.com')

firebase.put("https://sample-343d2.firebaseio.com","buttons2/buttonState","1100")


############
def on_message(client, userdata, message):
	button1 = firebase.get("/buttons/buttonState", None)	
	print("message received " ,str(message.payload.decode("utf-8")))
	msg = str(message.payload.decode("utf-8"))
	print("data",msg[-1],msg[-2])
	print("button stste",button1)
	if(msg[-1]=="0"and msg[-2]=="*" and button1[0]=='1'):
		print("relay one on")
		client.publish("R1","S1ON")
	if(msg[-1]=="0"and msg[-2]=="*" and button1[0]=='0'):
		print("relay one off")
		client.publish("R1","S1OFF")


	else:
		print("relay esle block offffff")
########################################
broker_address="192.168.1.4"
#broker_address="iot.eclipse.org"
print("creating new instance")
client = mqtt.Client("P1") #create new instance
client.on_message=on_message #attach function to callback
print("connecting to broker")
client.connect(broker_address) #connect to broker
while True:
	client.loop_start() #start the loop
	#print("Subscribing to topic","Master_control")
	client.subscribe("Master_control")
	#print("Publishing message to topic","house/bulbs/bulb1")
	#client.publish("R1","hellooooo")
	time.sleep(4) # wait
#client.loop_stop() #stop the loop
