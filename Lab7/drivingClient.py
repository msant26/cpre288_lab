# Author: Phillip Jones
# Date: 08/19/2022, updated 05/25/2023, updated 07/13/2023
# Description: Simple client for sending/recieveing information using a UART interface, or Network Socket
#              to either a mock CyBot server, or the actual CyBot

# General Python tutorials (W3schools):  https://www.w3schools.com/python/

# Serial library:  https://pyserial.readthedocs.io/en/latest/shortintro.html 
# import serial
import time # Time library   
# Socket library:  https://realpython.com/python-sockets/  
# See: Background, Socket API Overview, and TCP Sockets  
import socket   
import msvcrt

# Choose to create either a UART or TCP port socket to communicate with Cybot (Not both!!: I.e, comment out the one not being used)
# UART BEGIN
#cybot = serial.Serial('COM100', 115200)  # UART (Make sure you are using the correct COM port and Baud rate!!)
# UART END

# TCP Socket BEGIN (See Echo Client example): https://realpython.com/python-sockets/#echo-client-and-server
HOST = "192.168.1.1"  # The server's hostname or IP address
PORT = 288        # The port used by the server
cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
print("Attempting to connect...")
cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
print("Connection Successful")
                      
cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile
cybot = cybot_socket.makefile("rbw", buffering=0)

print("Press keys to send (q to quit):")

while True:
    key = msvcrt.getch().decode('utf-8')  # get ONE key instantly

    if key == 'q':
        cybot.write(key.encode())
        print("Sent:", key)
        break

    # send ONLY one character (NO newline)
    cybot.write(key.encode())
    print("Sent:", key)
    rx_message = cybot.read(1)
    print("Received:", rx_message.decode())

print("Client exiting...\n")
time.sleep(2)
cybot.close()
cybot_socket.close()