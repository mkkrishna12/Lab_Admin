# Sender Infrastructure
The Sender module on client side is bridge between Client Interface and socket interface. Responsiblities of this module is:
- Client Initiation
- Wrapping Messages

### Responsiblities of Sender:

* Client Initiation:
    This functionality is provided in Sender module to indicate Server that client machine is just initiated. Server IP and port will be read from a <a href="../Settings/server_data.txt">file</a>.
    
** Wrapping Messages:
    It is extremely necessery to bind a message with IP and port of client for identification of client on Server side. This functionality binds each message that is going to Server with its IP and port.
