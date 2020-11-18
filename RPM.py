import time
import socket
import struct
import serial
arduinoData = serial.Serial('com5',115200)
ip = 'your_IP_here'
port = 9996
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client_socket.settimeout(1.0)
identifier = 1
version = 1
operationId= 0

handshaker = struct.pack('iii', 1, 1, 3)
client_socket.sendto(handshaker, (ip, port))
try:
    handshaker = struct.pack('iii', identifier, version, operationId)

    client_socket.sendto(handshaker, (ip, port))
    print("\n\n 1. Client Sent : ", struct.unpack('iii',handshaker), "\n\n")
    data, address = client_socket.recvfrom(4096)
    for x in data:
        print(chr(x),end="")
    print()
    result = struct.unpack('100s100sii100s100s',data)
    
    handshaker = struct.pack('iii', 1, 1, 1)
    client_socket.sendto(handshaker, (ip, port))

    # data, address = client_socket.recvfrom(4096)
    # result = struct.unpack('100s100sii100s100s',data)
    # print(result)
    while True:
        data, address = client_socket.recvfrom(4096)
        result = struct.unpack('cifff??????xfffiiiifffffiffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff',data)
        # mapping rpm(0-10000) to number of leds(0-16)
        NewValue = (((result[21] - 0) * (16 - 0)) / 9000) + 0
        # 10.(50)546 -> 1043.546
        hue = (NewValue*100%100)
        hue = (((hue - 0) * (256 - 0)) / 100) + 0
        arduinoData.write(struct.pack('>B',int( NewValue)))
except Exception as e:
    print(e)
    handshaker = struct.pack('iii', 1, 1, 3)
    client_socket.sendto(handshaker, (ip, port))
