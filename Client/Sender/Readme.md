# Sender Infrastructure
The Sender module on client side is bridge between <a href="../Client_Interface/">Client Interface</a> and socket interface. Responsiblities of this module is:
- Client Initiation
- Wrapping Messages

### Responsiblities of Sender:

1. Client Initiation:
    This functionality is provided in Sender module to indicate <a href="../../Server/">Server</a> that client machine is just initiated. Server IP and port will be read from a <a href="../Settings/server_data.txt">file</a>.
    
2. Wrapping Messages:
    It is extremely necessery to bind a message with IP and port of client for identification of client on Server side. This functionality binds each message that is going to Server with its IP and port. Check <a href="../Messages/">message design</a> for more details.
