#!/usr/bin/python3

# 1. HTML Header & The obligatory Empty line
print("Content-Type: text/html\r\n\r\n", end="")

# 2. The content of the page
print("<html>")
print("<head><title>CGI Python</title></head>")
print("<body style='font-family: sans-serif; background-color: #f0f0f0;'>")
print("  <h1>Salut ! C'est Python !</h1>")
print("  <p>Ce message a été généré dynamiquement.</p>")
print("</body>")
print("</html>")