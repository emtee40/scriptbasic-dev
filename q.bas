_svrmsg = ":bazik!~bazik@looking.for.linux.chix0r.net PRIVMSG bazbot :test"

if _svrmsg like ":*!* PRIVMSG * :*" then

                        _send = trim(joker(1))
                        _host = trim(joker(2))
                        _recv = trim(joker(3))
                        _msg  = trim(joker(4))
endif
print format("send=%s\nhost=%s\nrecv=%s\nmsg=%s\n",_send,_host,_recv,_msg)
