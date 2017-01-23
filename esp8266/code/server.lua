pin=8
port=5000
-- Works!
gpio.mode(pin, gpio.OUTPUT)
gpio.write(pin, gpio.LOW)

srv = net.createServer(net.UDP)
srv:listen(port)

srv:on("receive", function(conn, pl)
   print ("Meow \r"  )
   print ("\r"  )
   uart.write(0, pl, "\r") 
   conn:send("OK")
   if pl=="LED 1 0" then uart.write(0, "\r LED 1 0 \r") 
   conn:send("OK")
			end
	if pl=="LED 1 1" then uart.write(0, "\r LED 1 1 \r") 
    conn:send("OK")
            end
    if pl=="test" then uart.write(0, pl, "\r") 
    conn:send("OK")
			end
   end)








