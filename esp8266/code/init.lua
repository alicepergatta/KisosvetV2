function abortInit()
    -- initailize abort boolean flag
    abort = false
    print('Press ENTER to abort startup')
    -- if <CR> is pressed, call abortTest
    uart.on('data', '\r', abortTest, 0)
    -- start timer to execute startup function in 5 seconds
    tmr.alarm(0,2000,0,startup)
    end
    
function abortTest(data)
    -- user requested abort
    abort = true
    -- turns off uart scanning
    uart.on('data')
    end

function startup()
    uart.on('data')
    -- if user requested abort, exit
    if abort == true then
        print('startup aborted')
        return
        end
    -- otherwise, start up
    print('in startup')
    dofile('server.lua')
    end

tmr.alarm(0,1000,0,abortInit)           -- call abortInit after 1s


