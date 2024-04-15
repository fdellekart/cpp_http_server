# C++ HTTP Server

This small server is a side project of mine to learn C++.

It implements a server class which listens on a TCP port and 
handles incoming connections.

An extensible interface for adding routes allows to register various 
types of routes via `server.register_route` .
