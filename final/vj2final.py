import paho.mqtt.client as mqtt #import the client1
import time
from firebase import firebase
import requests

firebase_url = 'https://sample-343d2.firebaseio.com'
firebase = firebase.FirebaseApplication('https://sample-343d2.firebaseio.com')

def final_status(n):
	return int(n,2)
	

def DecimalToBinary(n):
	a = "{0:b}".format(n)	
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
	button = firebase.get("/buttons2/buttonState", None)	
	print("button status : ",button)
	msg = str(message.payload.decode("utf-8"))
	switch_status = DecimalToBinary(int (msg[-1]))
	print("switch status : ",switch_status)
	publish_message = ""
	if(msg[-2]=="#"):
		print("state change#######################")
		firebase.put("https://sample-343d2.firebaseio.com","buttons2/buttonState",str(switch_status))
		publish_message = ""
		
		#client.publish("R1","0000")
		print("switch staus: ",switch_status)
		time.sleep(3)


	if(msg[-2]=="*"):
		
		#firebase.put("https://sample-343d2.firebaseio.com","buttons2/buttonState",str(switch_status))

################# switch 1######
		if(switch_status[0]=="0" and button[0]=="0"):					
			publish_message=publish_message + "00" # ps 0-off 1 0n
			
		if(switch_status[0]=="0" and button[0]=="1"):			
			publish_message = publish_message+"11"# ps 0-off 1 0n			
		if(switch_status[0]=="1" and button[0]=="0"):		
			publish_message = publish_message+"01"# ps 0-off 1 0n
			
		if(switch_status[0]=="1" and button[0]=="1"):			
			publish_message = publish_message +"00" # ps 0-off 1 0n
	
############switch 2 ########################################
		if(switch_status[1]=="0" and button[1]=="0"):				
			publish_message = publish_message +"00" # ps 0-off 1 0n
			
		if(switch_status[1]=="0" and button[1]=="1"):		
			publish_message = publish_message+"11" # ps 0-off 1 0n
			
		if(switch_status[1]=="1" and button[1]=="0"):			
			publish_message = publish_message+"01"# ps 0-off 1 0n
			
		if(switch_status[1]=="1" and button[1]=="1"):			
			publish_message = publish_message +"00" # ps 0-off 1 0n
			
########switch 3 ############################

		if(switch_status[2]=="0" and button[2]=="0"):					
			publish_message = publish_message +"00" # ps 0-off 1 0n
			
		if(switch_status[2]=="0" and button[2]=="1"):			
			publish_message = publish_message+"11"# ps 0-off 1 0n
			
		if(switch_status[2]=="1" and button[2]=="0"):			
			publish_message = publish_message+"01"# ps 0-off 1 0n
			
		if(switch_status[2]=="1" and button[2]=="1"):			
			publish_message = publish_message +"00" # ps 0-off 1 0n
			
			
	
##########switch 4 ###############

		if(switch_status[3]=="0" and button[3]=="0"):					
			publish_message = publish_message +"00" # ps 0-off 1 0n
		
		if(switch_status[3]=="0" and button[3]=="1"):
			publish_message = publish_message+"11"# ps 0-off 1 0n
		
		if(switch_status[3]=="1" and button[3]=="0"):	
			publish_message = publish_message+"01"# ps 0-off 1 0n
			
		if(switch_status[3]=="1" and button[3]=="1"):			
			publish_message = publish_message +"00" # ps 0-off 1 0n
			

	final_status_out_message =  final_status (publish_message)
	
	if(len(str(final_status_out_message))==1):
		final_status_out_message = "00"+str(final_status_out_message)

		client.publish("R1",str(final_status_out_message))
		print("publishing data********",final_status_out_message)
		#client.loop_stop() #stop the loop
	if(len(str(final_status_out_message))==2):
		final_status_out_message = "0"+str(final_status_out_message)
		client.publish("R1",str(final_status_out_message))
		print("publishing data******",final_status_out_message)
		#client.loop_stop() #stop the loop
	
	else:
		
		client.publish("R1",str(final_status_out_message))
		print("publishing data*********",final_status_out_message)
		#client.loop_stop() #stop the loop
	


	
########################################
broker_address= "192.168.1.4"

print("creating new instance")
client = mqtt.Client("P1") #create new instance
client.on_message=on_message #attach function to callback
print("connecting to broker")
client.connect(broker_address) #connect to broker

while True:
	print("vj2")
	client.loop_start() #start the loop		
	client.subscribe("Master_control")
	time.sleep(0.1) # wait

	

