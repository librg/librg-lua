#define LIBRG_IMPLEMENTATION
#include <librg.h>

#define LUA_LIB
#include "lua.h"
// #include "lualib.h"
#include "lauxlib.h"

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

// static void push_event(lua_State *l, ENetEvent *event) {
//     lua_newtable(l); // event table

//     if (event->peer) {
//         push_peer(l, event->peer);
//         lua_setfield(l, -2, "peer");
//     }

//     switch (event->type) {
//         case ENET_EVENT_TYPE_CONNECT:
//             lua_pushinteger(l, event->data);
//             lua_setfield(l, -2, "data");

//             lua_pushstring(l, "connect");
//             break;
//         case ENET_EVENT_TYPE_DISCONNECT:
//             lua_pushinteger(l, event->data);
//             lua_setfield(l, -2, "data");

//             lua_pushstring(l, "disconnect");
//             break;
//         case ENET_EVENT_TYPE_RECEIVE:
//             lua_pushlstring(l, (const char *)event->packet->data, event->packet->dataLength);
//             lua_setfield(l, -2, "data");

//             lua_pushinteger(l, event->channelID);
//             lua_setfield(l, -2, "channel");

//             lua_pushstring(l, "receive");

//             enet_packet_destroy(event->packet);
//             break;
//         case ENET_EVENT_TYPE_NONE:
//             lua_pushstring(l, "none");
//             break;
//     }

//     lua_setfield(l, -2, "type");
// }

static int librg_lua_create(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);

    lua_newtable(L);

    return 0;
}

static int librg_lua_fre(lua_State *L) {
    librg_lua_assert_argc(L, lua_gettop(L) == 1);
    return 0;
}

#define LIBRG_LUA_REGISTER(name, func) \
    lua_pushcfunction(L, func); \
    lua_setfield(L, -2, name)

#define LIBRG_LUA_CONSTANT(name, value) \
    lua_pushnumber(L, value); \
    lua_setfield(L, LUA_GLOBALSINDEX, name)

/**
 * Open librg library
 */
LUALIB_API int luaopen_librg_lua(lua_State *L) {

    LIBRG_LUA_CONSTANT("LIBRG_VERSION",                     LIBRG_VERSION);

    LIBRG_LUA_CONSTANT("LIBRG_PLATFORM_ID",                 LIBRG_PLATFORM_ID);
    LIBRG_LUA_CONSTANT("LIBRG_PLATFORM_PROTOCOL",           LIBRG_PLATFORM_PROTOCOL);
    LIBRG_LUA_CONSTANT("LIBRG_PLATFORM_BUILD",              LIBRG_PLATFORM_BUILD);
    LIBRG_LUA_CONSTANT("LIBRG_DEFAULT_CLIENT_TYPE",         LIBRG_DEFAULT_CLIENT_TYPE);
    LIBRG_LUA_CONSTANT("LIBRG_DEFAULT_DATA_SIZE",           LIBRG_DEFAULT_DATA_SIZE);
    LIBRG_LUA_CONSTANT("LIBRG_NETWORK_CAPACITY",            LIBRG_NETWORK_CAPACITY);
    LIBRG_LUA_CONSTANT("LIBRG_NETWORK_CHANNELS",            LIBRG_NETWORK_CHANNELS);
    LIBRG_LUA_CONSTANT("LIBRG_NETWORK_PRIMARY_CHANNEL",     LIBRG_NETWORK_PRIMARY_CHANNEL);
    LIBRG_LUA_CONSTANT("LIBRG_NETWORK_SECONDARY_CHANNEL",   LIBRG_NETWORK_SECONDARY_CHANNEL);
    LIBRG_LUA_CONSTANT("LIBRG_NETWORK_MESSAGE_CHANNEL",     LIBRG_NETWORK_MESSAGE_CHANNEL);
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
    LIBRG_LUA_CONSTANT("LIBRG_LAST_ENUM_NUMBER",            LIBRG_LAST_ENUM_NUMBER);

    // lua_setfield(L, 0, "LIBRG_MODE_SERVER");
    // lua_register(L, "LIBRG_MODE_SERVER", LIBRG_MODE_SERVER)

    // lua_pushnumber(L, LIBRG_MODE_CLIENT);
    // lua_setfield(L, -2, "LIBRG_MODE_CLIENT");

    lua_newtable(L);

    LIBRG_LUA_REGISTER("create", librg_lua_create);
    // LIBRG_LUA_REGISTER("free", librg_lua_free);


    return 1;
}

#undef LIBRG_LUA_REGISTER
