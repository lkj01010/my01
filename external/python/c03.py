import socket 
import sys,time



host = '127.0.0.1'
port =12303
n_conn = 100000
remote_ip = socket.gethostbyname( host )
remote_ip = host
message = "xvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvxxvvdvdvdvvdvvdvdvdvdvdvvvvvvvvvvvvvvvvvvvvvx"
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((remote_ip, port))


start = time.time()
for i in range(n_conn):
	sock.sendall(message)
	print 'Socket ' + str(i) + ' Connected to ' + str(port) + ' on ip ' + remote_ip
sock.close()	

end = time.time()
elapsed = end-start
print "all elapsed seconds %.3f" % elapsed


sockarr = []
start = time.time()
for i in range(200):
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sockarr.append(sock)
	print "sockarr append %d" % i
end = time.time()
elapsed = end-start
print "socks alloc seconds %.3f" % elapsed


start = time.time()
for i in range(200):
	sockarr[i].connect((remote_ip, port))
	try :
	    #Set the whole string
	    sockarr[i].sendall(message)
	except socket.error:
	    #Send failed
	    print 'Send failed'
	    sys.exit()

	sockarr[i].close()
end = time.time()
elapsed = end-start
print "socks connect seconds %.3f" % elapsed