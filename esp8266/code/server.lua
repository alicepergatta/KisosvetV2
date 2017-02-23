
port=5000
last_data = ""
-- Works!
   print ("Meow! \r"  )
   print ("\n\r"  )


srv = net.createServer(net.UDP)
srv:listen(port)
uart.alt(1)

    srv:on("receive",function(c,l)
        c:send("Received")
         --uart.write(0, "\r")
         --uart.write(0,"\n") 
         uart.write(0, l)
		 uart.write(0,"\r") 
         
        collectgarbage()
    end)

    --c:on("disconnection",function(c)
        -- not yet implemented
    --end)

    uart.on("data", "\r",
        function(data)
            srv:send(data)
            --last_data = data
            collectgarbage()
    end, 0)

--if last_data == "uart_alt \n\r" then
--uart.alt(1)
--end



