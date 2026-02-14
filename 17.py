# Use context managers ('with') to safely open/close files and handle exceptions.
# with open("test.txt", "w") as f:
#   f.write("Hello ")

with open("test.txt", "a") as f:
      f.write(" Hello")

##1. Database Connections (Commits & Rollbacks)
#This is probably the most important use case after files. When you talk to a database, you want to make sure your changes are saved (committed) or, if an error happens, cancelled (rolled back).
#Python
#
#import sqlite3
#
## The 'with' block manages the transaction
#with sqlite3.connect("my_data.db") as connection:
#    cursor = connection.cursor()
#    cursor.execute("INSERT INTO users VALUES ('Abir', 101)")
#    # If the code crashes here, the database won't save the broken data.
#    # If it finishes, it 'commits' automatically.
#
#2. Threading and Locks (Concurrency)
#When you have multiple parts of a program running at the same time (threads), they might try to change the same variable at once, which causes a crash. We use a Lock to make them wait their turn.
#Python
#
#from threading import Lock
#
#printer_lock = Lock()
#
#def print_securely(message):
#    with printer_lock:
#        # Only ONE thread can be inside this block at a time
#        print(message)
#    # The lock is released automatically here!
#
#3. Measuring Time (Custom Context Managers)
#You can actually create your own with statements! Remember how we used @time in Julia? We can build a "timer" in Python using with.
#Python
#
#import time
#
#class Timer:
#    def __enter__(self):
#        self.start = time.time()
#        return self
#
#    def __exit__(self, *args):
#        end = time.time()
#        print(f"Time elapsed: {end - self.start} seconds")
#
## Now you can use it like this:
#with Timer():
#    # Do some heavy calculation
#    sum(i**2 for i in range(1000000))
#
#4. Working with Network Sockets
#Just like files, network connections (sockets) are limited resources. If you open a connection to a website or another computer, you should use with to ensure it disconnects properly.
#Python
#
#import socket
#
#with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#    s.connect(("www.google.com", 80))
#    s.sendall(b"GET / HTTP/1.1\r\n\r\n")
