import socket
address='localhost'
def main():
    s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.settimeout(2)
    for port in range(42218,42228):
        try:
            s.connect((address,port))
            print '%d is connected!' % port
        except Exception,e:
            print 'error:%s' % e
    s.close()
if __name__=='__main__':
    main()