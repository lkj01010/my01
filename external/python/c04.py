import socket 
import sys,time



host = '127.0.0.1'
port =12303

remote_ip = socket.gethostbyname( host )

start = time.time()
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((remote_ip, port))
print 'Connected to ' + str(port) + ' on ip ' + remote_ip
time.sleep(5)

message = "GET/HTTP/1.1\r\n\r\n"
sock.sendall(message)
sock.close()
