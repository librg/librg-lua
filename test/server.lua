-- load the lib
require 'librg-lua'



-- -- create context
-- local librg = librg_lua.create({
--     mode            = LIBRG_MODE_SERVER,
--     tick_delay      = 32,
--     max_connections = 100,
-- });


function main()
    librg_option_set(LIBRG_NETWORK_CHANNELS, 4);
    print(librg_option_get(LIBRG_NETWORK_CHANNELS));

    local ctx = librg_init({
        mode            = LIBRG_MODE_SERVER,
        tick_delay      = 64,
        max_entities    = 9923,
        max_connections = 100,
        world_size_x    = 264.0,
        world_size_y    = 284.0,
    });

    print(ctx);

    librg_free(ctx);

    -- librg.init(function()
    --     -- librg.component_register(); -- oh shittttt
    -- end)

    -- librg.network_start({
    --     -- host = "localhost",
    --     port = 27010,
    -- });

    -- while true do
    --     librg.tick();
    -- end

    -- librg.network_stop();
    -- librg.free();
end

main();
