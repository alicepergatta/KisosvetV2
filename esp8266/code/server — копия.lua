
port=5000
conn_ip = 0
-- Works!
   print ("Meow! \r"  )
   print ("\n\r"  )


srv = net.createServer(net.UDP)
srv:listen(port)
uart.alt(1)

    srv:on("receive",function(c,l)
        uart.write(0, "\r")
         uart.write(0, "", l)
		 uart.write(0,"\n") 
        c:send("Received")
        collectgarbage()
    end)

    --c:on("disconnection",function(c)
        -- not yet implemented
    --end)

    uart.on("data", 0,
        function(data)
            srv:send(data)
            collectgarbage()
    end, 0)






