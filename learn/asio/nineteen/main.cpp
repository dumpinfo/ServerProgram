/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yt (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include <iostream>
#include <string>
class A {
	public:
		void action() { std::cout << "hello I'm A\n";}
		virtual void doPrint(int a, int b) {
			std::cout << "in A a : " << a << " b : " << b << std::endl;
		}
		std::string goodMan() const { return "goodman";}
};


class B : public A {
	public:
		void hello(const std::string& info) const {
			std::cout << "hello: " << info << std::endl;
		}
		virtual void doPrint(int a, int b) override {
			std::cout << "in B just " << (a + b) << std::endl;
		}
};

void globalFunction() {
	std::cout << "hello this is a global func\n";
}

bool reloadLuaScript(lua_State* L, const std::string& luafile) {
	int state = luaL_dofile(L, luafile.c_str());
	if(state != LUA_OK) {
		// std::cout << "ok";
		return false;
	}
	return true;
}
void registerClassAndFucntions(lua_State* L);
void testCallLua(lua_State* L);
lua_State* buildLuaEngine(const std::string& file) {
	lua_State* L = luaL_newstate();
	// need check L
	luaL_openlibs(L);
	auto ok = reloadLuaScript(L, file);
	if(!ok) {
		lua_close(L);
		L = nullptr;
	}
	return L;
}
int main(int argc, char** argv) {
	if(argc != 2) return 1;
	std::cout << "try load file " << argv[1] << std::endl;
	auto L = buildLuaEngine(argv[1]);
	if(L) {
		registerClassAndFucntions(L);
		testCallLua(L);
	}
	if(L) {
		lua_close(L);
		L = nullptr;
	}
}

void registerClassAndFucntions(lua_State* L) {
	using namespace luabridge;
	getGlobalNamespace(L).addFunction("globalFunction", globalFunction);
	getGlobalNamespace(L)
		.beginClass<A>("A")
		.addFunction("action", &A::action)
		.addFunction("doPrint", &A::doPrint)
		.addFunction("goodMan", &A::goodMan)
		.endClass()
		.deriveClass<B,A>("B")
		.addFunction("hello", &B::hello)
		.endClass();

}

void testCallLua(lua_State* L) {
	A a;
//	lua_getglobal(L, "testA");
//	luabridge::push(L,&a);
//	lua_pcall(L, 1, 0, 0);
	B b;

	lua_getglobal(L, "testAAndB");
	luabridge::push(L, &a);
	luabridge::push(L, &b);
	lua_pcall(L, 2, 0, 0);

}

