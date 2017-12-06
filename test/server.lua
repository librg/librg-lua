-- load the lib
require 'librg-lua'

function main()
    librg_option_set(LIBRG_NETWORK_CHANNELS, 4);
    print(librg_option_get(LIBRG_NETWORK_CHANNELS));

    local ctx = librg_init({
        mode            = LIBRG_MODE_CLIENT,
        tick_delay      = 64,
        max_entities    = 9923,
        max_connections = 100,
        world_size_x    = 264.0,
        world_size_y    = 284.0,
    });

    print(ctx);
    print("is server: ");
    print(librg_is_server(ctx));
    print("is client: ")
    print(librg_is_client(ctx));

    -- do some ticking
    local a = 0;
    while (a < 500) do
        librg_tick(ctx); a = a + 1;
    end

    librg_event_add(ctx, 42, function(event)
        print("handler called");
    end)

    librg_event_trigger(ctx, 42, { user_data = "hello world" });

    librg_free(ctx);
end

main();
