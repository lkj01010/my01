if __name__ == '__main__':   
    import socket 
    import sys
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#    host = 'www.baidu.com'
#    port = 80
     
     
    host = '192.168.1.107'
    port =12303
    
    remote_ip = socket.gethostbyname( host )
    
    sock.connect((remote_ip, port))
    
    print 'Socket Connected to ' + str(port) + ' on ip ' + remote_ip
    message = "GET/HTTP/1.1\r\n\r\n"
 
try :
    #Set the whole string
    sock.sendall(message)
except socket.error:
    #Send failed
    print 'Send failed'
    sys.exit()
 
    print 'Message send successfully'

     
    reply = s.recv(4096)
    print reply

    sock.close()

