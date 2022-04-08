#include <lua.hpp>
#include <iostream>

using namespace std;

int main()
{
	int a = 1;

	lua_State* state = luaL_newstate();
	luaL_openlibs(state);

	{
		auto rst = luaL_loadfile(state, "LuaTest.lua", "nihao");

		//0 stands for success, not 0 stands for error occurred, and error message will on the stack's top 
		if (rst != 0)
		{
			if (lua_isstring(state, -1))
			{
				auto msg = lua_tostring(state, -1);
				printf("load script failed: %s\n", msg);
				lua_pop(state, 1);
			}
			return -1;

		}

		//执行lua代码
		//lua_pcall(state, 传参数量，返回值，错误回调)
		if (LUA_OK != lua_pcall(state, 0, 0, 0))
		{
			if (lua_isstring(state, -1))
			{
				auto msg = lua_tostring(state, -1);
				printf("call function chunk failed: %s\n", msg);
				lua_pop(state, 1);
			}
		}

		//执行lua函数 call my_pow
		lua_getglobal(state, "my_pow");
		if (!lua_isfunction(state, -1))
		{
			printf("function name 'my pow' not found!");
			return -1;
		}
		lua_pushnumber(state, 2);
		lua_pushnumber(state, 8);
		rst = lua_pcall(state, 2, 1, 0);
		if (rst != 0)
		{
			if (lua_isstring(state, -1))
			{
				auto msg = lua_tostring(state, -1);
				printf("load script failed: %s\n", msg);
				lua_pop(state, 1);
			}
		}
		if (lua_isnumber(state, -1))
		{
			lua_Number val = lua_tonumber(state, -1);
			printf("my_pow ret: %f", (float)val);
		}
	}
	system("pause");
	return 0;
}