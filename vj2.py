import paho.mqtt.client as mqtt #import the client1
import time
import datetime
from firebase import firebase
import json
import requests


firebase_url = 'https://sample-343d2.firebaseio.com'

firebase = firebase.FirebaseApplication('https://sample-343d2.firebaseio.com')

firebase.put("https://sample-343d2.firebaseio.com","buttons2/buttonState","1100")

def BinaryToDecimal(n):
	a = "{0:b}".format(n)
	print("binary to decimal")
	if(len(a)==1):
		a = "000"+a
		return a
	if(len(a)==2):
		a = "00"+a
		return a
	if(len(a)==3):
		a = "0"+a
		return a
	else:
		return a
###########################
def on_message(client, userdata, message):
	button = firebase.get("/buttons/buttonState", None)	
	print("button status", button[0])
	print("message received " ,str(message.payload.decode("utf-8")))
	msg = str(message.payload.decode("utf-8"))
	switch_status = BinaryToDecimal(int (msg[-1]))
	print("switch_status",switch_status)
	print("switch_status[0]: ",switch_status[0])
	publish_message = []
	if(msg[-2]=="*"):
################# switch 1######
		if(switch_status[0]=="0" and button[0]=="0"):
			print("client.publish S1OFFPS")
			client.publish("R1","S1OFFPS")
			publish_message.append("0")
		if(switch_status[0]=="0" and button[0]=="1"):
			client.publish("R1","S1ONP")
			print("client.publish S1ONP")
			publish_message.append("P")
		if(switch_status[0]=="1" and button[0]=="0"):
			client.publish("R1","S1OFFS")
			print("client.publish S1OFFS")
			publish_message.append("S")
		if(switch_status[0]=="1" and button[0]=="1"):
			client.publish("R1","S1OFFPS")
			print("client.publish S1OFFPS")
			publish_message.append("0")
############switch 2 ########################################
		if(switch_status[1]=="0" and button[1]=="0"):
			print("client.publish S2OFFPS")
			client.publish("R1","S2OFFPS")
			publish_message.append("0")
		if(switch_status[1]=="0" and button[1]=="1"):
			client.publish("R1","S2ONP")
			print("client.publish S2ONP")
			publish_message.append("P")
		if(switch_status[1]=="1" and button[1]=="0"):
			client.publish("R1","S2OFFS")
			print("client.publish S2OFFS")
			publish_message.append("S")			
		if(switch_status[1]=="1" and button[1]=="1"):
			client.publish("R1","S2OFFPS")
			print("client.publish S2OFFPS")
			publish_message.append("0")
########switch 3 ############################

		if(switch_status[2]=="0" and button[2]=="0"):
			print("client.publish S3OFFPS")
			client.publish("R1","S3OFFPS")
			publish_message.append("0")
		if(switch_status[2]=="0" and button[2]=="1"):
			client.publish("R1","S3ONP")
			print("client.publish S3ONP")
			publish_message.append("P")
		if(switch_status[2]=="1" and button[2]=="0"):
			client.publish("R1","S3OFFS")
			print("client.publish S3OFFS")
			publish_message.append("S")			
		if(switch_status[2]=="1" and button[2]=="1"):
			client.publish("R1","S3OFFPS")
			print("client.publish S3OFFPS")
			publish_message.append("0")
			
	
##########switch 4 ###############

		if(switch_status[3]=="0" and button[3]=="0"):
			print("client.publish S4OFFPS")
			client.publish("R1","S4OFFPS")
			publish_message.append("0")
		if(switch_status[3]=="0" and button[3]=="1"):
			client.publish("R1","S4ONP")
			print("client.publish S4ONP")
			publish_message.append("P")
		if(switch_status[3]=="1" and button[3]=="0"):
			client.publish("R1","S4OFFS")
			print("client.publish S4OFFS")
			publish_message.append("S")			
		if(switch_status[3]=="1" and button[3]=="1"):
			client.publish("R1","S4OFFPS")
			print("client.publish S4OFFPS")
			publish_message.append("0")


	client.publish("R1",str(publish_message))


	
########################################
broker_address= "192.168.1.104"
#broker_address="iot.eclipse.org"
print("creating new instance")
client = mqtt.Client("P1") #create new instance
client.on_message=on_message #attach function to callback
print("connecting to broker")
client.connect(broker_address) #connect to broker
while True:
	print("loop")
	client.loop_start() #start the loop
	#print("Subscribing to topic","Master_control")
	client.subscribe("Master_control")
	#print("Publishing message to topic","house/bulbs/bulb1")
	#client.publish("R1","hellooooo")
	time.sleep(3) # wait
#client.loop_stop() #stop the loop
