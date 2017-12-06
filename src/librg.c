#define LUA_LIB
#define LIBRG_DEBUG
#define LIBRG_IMPLEMENTATION

#include <lua.h>
#include <lauxlib.h>
#include <librg.h>

// =======================================================================//
// !
// ! Helpers
// !
// =======================================================================//

#define LIBRG_LUA_REGISTER(name, func) \
    lua_pushcfunction(L, func); \
    lua_setfield(L, -2, name)

#define LIBRG_LUA_CONSTANT(name, value) \
    lua_pushinteger(L, value); \
    lua_setfield(L, LUA_GLOBALSINDEX, name)

static void librg_lua_assert(lua_State *L, int pass, const char *msg) {
    if (!pass) {
        lua_Debug ar;
        ar.name = NULL;
        if (lua_getstack(L, 0, &ar))
            lua_getinfo(L, "n", &ar);
        if (ar.name == NULL)
            ar.name = "?";
        luaL_error(L, msg, ar.name);
    }
}

static void librg_lua_assert_argc(lua_State *L, int pass) {
    librg_lua_assert(L, pass, "wrong number of arguments to '%s'");
}

// =======================================================================//
// !
// ! General method bindings
// !
// =======================================================================//

static int llibrg_option_get(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);
    lua_pushinteger(L, librg_option_get(lua_tointeger(L, 1)));
    return 1;
}

static int llibrg_option_set(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 2);
    librg_option_set(lua_tointeger(L, 1), lua_tointeger(L, 2));
    return 1;
}

static int llibrg_init(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);

    lua_settop(L, 1);
    luaL_checktype(L, 1, LUA_TTABLE);

    lua_getfield(L, 1, "world_size_x");
    lua_getfield(L, 1, "world_size_y");
    lua_getfield(L, 1, "world_size_z");
    lua_getfield(L, 1, "tick_delay");
    lua_getfield(L, 1, "max_connections");
    lua_getfield(L, 1, "max_entities");
    lua_getfield(L, 1, "mode");

    f32 world_size_x     = lua_tonumber(L, -7);
    f32 world_size_y     = lua_tonumber(L, -6);
    f32 world_size_z     = lua_tonumber(L, -5);
    u32 tick_delay       = lua_tointeger(L, -4);
    u32 max_connections  = lua_tointeger(L, -3);
    u32 max_entities     = lua_tointeger(L, -2);
    u32 mode             = lua_tointeger(L, -1);

    // TODO: add metatable stuff
    librg_ctx_t *ctx = (librg_ctx_t *)lua_newuserdata(L, sizeof(librg_ctx_t));
    zpl_zero_item(ctx);

    ctx->tick_delay      = tick_delay;
    ctx->max_connections = max_connections;
    ctx->max_entities    = max_entities;
    ctx->mode            = mode;
    ctx->world_size      = zplm_vec3(world_size_x, world_size_y, world_size_z);

    librg_init(ctx);
    return 1;
}

static int llibrg_free(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);
    librg_lua_assert(L, lua_isuserdata(L, 1), "You should provide a userdata.");
    librg_free((librg_ctx_t *)lua_touserdata(L, 1));
    return 1;
}

static int llibrg_tick(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);
    librg_lua_assert(L, lua_isuserdata(L, 1), "You should provide a userdata.");
    librg_tick((librg_ctx_t *)lua_touserdata(L, 1));
    return 1;
}

static int llibrg_is_server(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);
    librg_lua_assert(L, lua_isuserdata(L, 1), "You should provide a userdata.");
    lua_pushboolean(L, librg_is_server(lua_touserdata(L, 1)));
    return 1;
}

static int llibrg_is_client(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);
    librg_lua_assert(L, lua_isuserdata(L, 1), "You should provide a userdata.");
    lua_pushboolean(L, librg_is_client(lua_touserdata(L, 1)));
    return 1;
}

static int llibrg_is_connected(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);
    librg_lua_assert(L, lua_isuserdata(L, 1), "You should provide a userdata.");
    lua_pushboolean(L, librg_is_connected(lua_touserdata(L, 1)));
    return 1;
}


// =======================================================================//
// !
// ! Event method bindings
// !
// =======================================================================//

static int llibrg_event_add(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 3);
    librg_lua_assert(L, lua_isuserdata(L, 1), "You should provide a userdata.");

    lua_pushinteger(L, librg_event_add(lua_touserdata(L, 1), lua_tointeger(L, 1), lua_tocfunction(L, 1)));

    return 1;
}

static int llibrg_event_remove(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 3);
    librg_lua_assert(L, lua_isuserdata(L, 1), "You should provide a userdata.");
    return 1;
}

static int llibrg_event_trigger(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 3);
    librg_lua_assert(L, lua_isuserdata(L, 1), "You should provide a userdata.");
    return 1;
}

static int llibrg_event_reject(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);
    librg_lua_assert(L, lua_isuserdata(L, 1), "You should provide a userdata.");
    return 1;
}

static int llibrg_event_succeeded(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);
    librg_lua_assert(L, lua_isuserdata(L, 1), "You should provide a userdata.");
    return 1;
}


// =======================================================================//
// !
// ! Entity method bindings
// !
// =======================================================================//



// =======================================================================//
// !
// ! Data method bindings
// !
// =======================================================================//



// =======================================================================//
// !
// ! Network/messages method bindings
// !
// =======================================================================//



// =======================================================================//
// !
// ! Constants and methods
// !
// =======================================================================//

LUALIB_API int luaopen_lua(lua_State *L) {
    LIBRG_LUA_CONSTANT("LIBRG_VERSION",                     LIBRG_VERSION);

    LIBRG_LUA_CONSTANT("LIBRG_PLATFORM_ID",                 LIBRG_PLATFORM_ID);
    LIBRG_LUA_CONSTANT("LIBRG_PLATFORM_PROTOCOL",           LIBRG_PLATFORM_PROTOCOL);
    LIBRG_LUA_CONSTANT("LIBRG_PLATFORM_BUILD",              LIBRG_PLATFORM_BUILD);
    LIBRG_LUA_CONSTANT("LIBRG_DEFAULT_CLIENT_TYPE",         LIBRG_DEFAULT_CLIENT_TYPE);
    LIBRG_LUA_CONSTANT("LIBRG_DEFAULT_STREAM_RANGE",        LIBRG_DEFAULT_STREAM_RANGE);
    LIBRG_LUA_CONSTANT("LIBRG_DEFAULT_DATA_SIZE",           LIBRG_DEFAULT_DATA_SIZE);
    LIBRG_LUA_CONSTANT("LIBRG_NETWORK_CAPACITY",            LIBRG_NETWORK_CAPACITY);
    LIBRG_LUA_CONSTANT("LIBRG_NETWORK_CHANNELS",            LIBRG_NETWORK_CHANNELS);
    LIBRG_LUA_CONSTANT("LIBRG_NETWORK_PRIMARY_CHANNEL",     LIBRG_NETWORK_PRIMARY_CHANNEL);
    LIBRG_LUA_CONSTANT("LIBRG_NETWORK_SECONDARY_CHANNEL",   LIBRG_NETWORK_SECONDARY_CHANNEL);
    LIBRG_LUA_CONSTANT("LIBRG_NETWORK_MESSAGE_CHANNEL",     LIBRG_NETWORK_MESSAGE_CHANNEL);
    LIBRG_LUA_CONSTANT("LIBRG_MAX_ENTITIES_PER_BRANCH",     LIBRG_MAX_ENTITIES_PER_BRANCH);
    LIBRG_LUA_CONSTANT("LIBRG_MAX_THREADS_PER_UPDATE",      LIBRG_MAX_THREADS_PER_UPDATE);
    LIBRG_LUA_CONSTANT("LIBRG_OPTIONS_SIZE",                LIBRG_OPTIONS_SIZE);

    LIBRG_LUA_CONSTANT("LIBRG_MODE_SERVER",                 LIBRG_MODE_SERVER);
    LIBRG_LUA_CONSTANT("LIBRG_MODE_CLIENT",                 LIBRG_MODE_CLIENT);

    LIBRG_LUA_CONSTANT("LIBRG_CONNECTION_INIT",             LIBRG_CONNECTION_INIT);
    LIBRG_LUA_CONSTANT("LIBRG_CONNECTION_REQUEST",          LIBRG_CONNECTION_REQUEST);
    LIBRG_LUA_CONSTANT("LIBRG_CONNECTION_REFUSE",           LIBRG_CONNECTION_REFUSE);
    LIBRG_LUA_CONSTANT("LIBRG_CONNECTION_ACCEPT",           LIBRG_CONNECTION_ACCEPT);
    LIBRG_LUA_CONSTANT("LIBRG_CONNECTION_DISCONNECT",       LIBRG_CONNECTION_DISCONNECT);
    LIBRG_LUA_CONSTANT("LIBRG_ENTITY_CREATE",               LIBRG_ENTITY_CREATE);
    LIBRG_LUA_CONSTANT("LIBRG_ENTITY_UPDATE",               LIBRG_ENTITY_UPDATE);
    LIBRG_LUA_CONSTANT("LIBRG_ENTITY_REMOVE",               LIBRG_ENTITY_REMOVE);
    LIBRG_LUA_CONSTANT("LIBRG_CLIENT_STREAMER_ADD",         LIBRG_CLIENT_STREAMER_ADD);
    LIBRG_LUA_CONSTANT("LIBRG_CLIENT_STREAMER_REMOVE",      LIBRG_CLIENT_STREAMER_REMOVE);
    LIBRG_LUA_CONSTANT("LIBRG_CLIENT_STREAMER_UPDATE",      LIBRG_CLIENT_STREAMER_UPDATE);
    LIBRG_LUA_CONSTANT("LIBRG_EVENT_LAST",                  LIBRG_EVENT_LAST);

    lua_register(L, "librg_option_get", llibrg_option_get);
    lua_register(L, "librg_option_set", llibrg_option_set);

    lua_register(L, "librg_init", llibrg_init);
    lua_register(L, "librg_free", llibrg_free);
    lua_register(L, "librg_tick", llibrg_tick);

    lua_register(L, "librg_is_server",      llibrg_is_server);
    lua_register(L, "librg_is_client",      llibrg_is_client);
    lua_register(L, "librg_is_connected",   llibrg_is_connected);

    lua_register(L, "librg_event_add",          llibrg_event_add);
    lua_register(L, "librg_event_remove",       llibrg_event_remove);
    lua_register(L, "librg_event_trigger",      llibrg_event_trigger);
    lua_register(L, "librg_event_reject",       llibrg_event_reject);
    lua_register(L, "librg_event_succeeded",    llibrg_event_succeeded);

    return 1;
}

#undef LIBRG_LUA_REGISTER
