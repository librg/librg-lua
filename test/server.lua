-- load the lib
local librg_lua = require 'librg_lua';

-- create context
-- local librg = librg_lua.create({
--     mode            = LIBRG_MODE_SERVER,
--     tick_delay      = 32,
--     max_connections = 100,
-- });

print(LIBRG_MODE_SERVER)

-- function main()
--     librg.init(function()
--         -- librg.component_register(); -- oh shittttt
--     end)

--     librg.network_start({
--         -- host = "localhost",
--         port = 27010,
--     });

--     while true do
--         librg.tick();
--     end

--     librg.network_stop();
--     librg.free();
-- end

-- main();
