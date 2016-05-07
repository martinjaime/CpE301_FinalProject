wifi.setmode(wifi.STATION);
wifi.sta.config("martinCpE301_spot" ,"S2016CpE");

x = 0
y = 0
z = 0
dir = 0

uart.on("data", "\n", 
    function(data)
        x, y, z, dir = data:match("(-*%d+)\t(-*%d+)\t(-*%d+)\t(-*%d+)")
        if (string.match(data, "quit")) then
            print("Quitting...")
            uart.on("data")
        elseif (x ~= nil and y ~= nil and z ~= nil and dir ~= nil) then
            --print(x .. y .. z .. dir)
            x = tonumber(x)
            y = tonumber(y)
            z = tonumber(z)
            dir = tonumber(dir)
        end
    end,
    0)
 
function postThingSpeak(level)
    connout = nil
    connout = net.createConnection(net.TCP, 0)
 
    connout:on("receive", function(connout, payloadout)
        if (string.find(payloadout, "Status: 200 OK") ~= nil) then
            print("Posted OK");
        end
    end)
 
    connout:on("connection", function(connout, payloadout)
 
        print ("Posting...");

        connout:send(
           "POST /update?api_key=HNZL3KTN1FIKWLZL&field1=" .. x 
        .. "POST /update?api_key=HNZL3KTN1FIKWLZL&field2=" .. y 
        .. "POST /update?api_key=HNZL3KTN1FIKWLZL&field3=" .. z 
        .. "POST /update?api_key=HNZL3KTN1FIKWLZL&field4=" .. dir 
        .. " HTTP/1.1\r\n"
        .. "Host: api.thingspeak.com\r\n"
        .. "Connection: close\r\n"
        .. "Accept: */*\r\n"
        .. "User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n"
        .. "\r\n")
    end)
 
    connout:on("disconnection", function(connout, payloadout)
        connout:close();
        collectgarbage();
    end)
 
    connout:connect(80,'api.thingspeak.com')
end
 
tmr.alarm(1, 5000, 1, function() postThingSpeak(0) end)