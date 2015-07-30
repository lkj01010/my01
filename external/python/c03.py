import socket 
import sys,time
import struct


host = '127.0.0.1'
port =12303
n_conn = 10
remote_ip = socket.gethostbyname( host )
remote_ip = host


message = "1234567890abcdefghijklmn"
message = bytearray([52,18, 14,0, 0,6, 0, 0,10, 1,2,3,4,5,6,7,8,9,0,1])


##############################

content = "content is very long !!!"
pad16=4660
size16 = 9+len(content) + 1
cmd16 = 10    

encrypt8 = 's'
param16 = 255


# cat string
fff = 'hhhch' + str(len(content)) + 's'
print 'fff=' + fff

# format string
fff = 'hhhch%ds' % len(content)
print fff
message = struct.pack(fff, pad16,size16,cmd16,encrypt8,param16,content)

# msgformat = "hhhxhs"
# message = struct.pack("hhhxh", pad16,size16,cmd16,encrypt8,param16)

#######################################

start = time.time()
for i in range(n_conn):
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.connect((remote_ip, port))
	# sock.sendall(message + '   ' + str(i))
	sock.sendall(message) 
	print 'Socket ' + str(i) + ' Connected to ' + str(port) + ' on ip ' + remote_ip
	sock.close()	

end = time.time()
elapsed = end-start
print "all elapsed seconds %.3f" % elapsed


# sockarr = []
# start = time.time()
# for i in range(200):
# 	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 	sockarr.append(sock)
# 	print "sockarr append %d" % i
# end = time.time()
# elapsed = end-start
# print "socks alloc seconds %.3f" % elapsed


# start = time.time()
# for i in range(200):
# 	sockarr[i].connect((remote_ip, port))
# 	try :
# 	    #Set the whole string
# 	    sockarr[i].sendall(message)
# 	except socket.error:
# 	    #Send failed
# 	    print 'Send failed'
# 	    sys.exit()

# 	sockarr[i].close()
# end = time.time()
# elapsed = end-start
# print "socks connect seconds %.3f" % elapsed