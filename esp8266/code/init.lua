
port=5000
-- Works!
   print ("Meow \r"  )
   print ("\n\r"  )


srv = net.createServer(net.UDP)
srv:listen(port)

srv:on("receive", function(conn, pl)
   uart.alt(1)
   --uart.write(0,"\n\r") 
   uart.write(0,"\r") 
   --uart.write(0, pl, "\r\n ")
   uart.write(0, "", pl )
   uart.write(0,"\n")  
--   uart.write(0, pl, "\n \r") 
   --uart.write(0,"\n\r") 
   conn:send("OK")
   			uart.alt(0)
            collectgarbage()
   end)








