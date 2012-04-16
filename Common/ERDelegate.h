#pragma once

template<typename FunctionType>
class ERDelegate;

template<typename FunctionType>
class ERDelegateImpl;

#if 1

template<template Return, template ...Args>
class ERDelegate<Return (Args...)>
{
public:
	virtual ~ERDelegate()
	{
	}

public:
	virtual Return invoke(Args...) = 0;
	virtual operator bool() = 0;
};

template<template Return, template ...Args>
class ERDelegateImpl<Return (Args...)>
{
private:
	std::function<Return (Args...)> fn;

public:
	ERDelegateImpl()
	{
	}

	ERDelegateImpl(const ERDelegateImpl<Return (Args...)> &obj)
		: fn(obj.fn)
	{
	}

	ERDelegateImpl(ERDelegateImpl<Return (Args...)> &&obj)
		: fn(std::move(obj.fn))
	{
	}

	ERDelegateImpl(Return (*ifn)(Args...))
		: fn(ifn)
	{
	}

	template<typename FunctionClass, typename InstanceClass>
	ERDelegateImpl(Return (FunctionClass::*ifn)(Args...), InstanceClass *ic)
		: fn(std::bind(ifn, ic, 0)) // TODO: http://boost.2283326.n4.nabble.com/bind-Possible-to-use-variadic-templates-with-bind-td2557818.html
	{
	}

	template<typename FunctionClass, typename InstanceClass>
	ERDelegateImpl(Return (FunctionClass::*ifn)(DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG)) const, const InstanceClass *ic)
		: fn(std::bind(ifn, ic DELEGATE_TEMPLATE_COMMA DELEGATE_BIND_ARG(DELEGATE_NUM_ARG)))
	{
	}

	template<typename FunctionClass, typename InstanceClass>
	ERDelegateImpl(Return (FunctionClass::*ifn)(DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG)) volatile, volatile InstanceClass *ic)
		: fn(std::bind(ifn, ic DELEGATE_TEMPLATE_COMMA DELEGATE_BIND_ARG(DELEGATE_NUM_ARG)))
	{
	}

	template<typename FunctionClass, typename InstanceClass>
	ERDelegateImpl(Return (FunctionClass::*ifn)(DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG)) const volatile, const volatile InstanceClass *ic)
		: fn(std::bind(ifn, ic DELEGATE_TEMPLATE_COMMA DELEGATE_BIND_ARG(DELEGATE_NUM_ARG)))
	{
	}

	template<typename Functor>
	ERDelegateImpl(Functor ifn)
		: fn(ifn)
	{
	}

	virtual ~ERDelegateImpl()
	{
	}

public:
	ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &operator =(std::nullptr_t)
	{
		fn.clear();
		return *this;
	}

	ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &operator =(const ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &obj)
	{
		fn = obj.fn;
		return *this;
	}

	ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &operator =(ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &&obj)
	{
		fn = std::move(obj.fn);
		return *this;
	}

	ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &operator =(Return (*ifn)(DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG)))
	{
		fn = ifn;
		return *this;
	}

	template<typename FunctionClass, typename InstanceClass>
	ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &operator =(std::pair<Return (FunctionClass::*)(DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG)), InstanceClass *> ifn)
	{
		fn = std::bind(ifn.first, ifn.second DELEGATE_TEMPLATE_COMMA DELEGATE_BIND_ARG(DELEGATE_NUM_ARG));
		return *this;
	}

	template<typename FunctionClass, typename InstanceClass>
	ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &operator =(std::pair<Return (FunctionClass::*)(DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG)) const, const InstanceClass *> ifn)
	{
		fn = std::bind(ifn.first, ifn.second DELEGATE_TEMPLATE_COMMA DELEGATE_BIND_ARG(DELEGATE_NUM_ARG));
		return *this;
	}

	template<typename FunctionClass, typename InstanceClass>
	ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &operator =(std::pair<Return (FunctionClass::*)(DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG)) volatile, volatile InstanceClass *> ifn)
	{
		fn = std::bind(ifn.first, ifn.second DELEGATE_TEMPLATE_COMMA DELEGATE_BIND_ARG(DELEGATE_NUM_ARG));
		return *this;
	}

	template<typename FunctionClass, typename InstanceClass>
	ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &operator =(std::pair<Return (FunctionClass::*)(DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG)) const volatile, const volatile InstanceClass *> ifn)
	{
		fn = std::bind(ifn.first, ifn.second DELEGATE_TEMPLATE_COMMA DELEGATE_BIND_ARG(DELEGATE_NUM_ARG));
		return *this;
	}

#undef DELEGATE_BIND_ARG_ELEMENT
#undef DELEGATE_BIND_ARG

	template<typename Functor>
	ERDelegateImpl<Return (DELEGATE_TEMPLATE_ARG(DELEGATE_NUM_ARG))> &operator =(Functor ifn)
	{
		fn = ifn;
		return *this;
	}

public:
	virtual Return invoke(DELEGATE_FUNCTION_PARAM(DELEGATE_NUM_ARG))
	{
		return fn(DELEGATE_FUNCTION_ARG(DELEGATE_NUM_ARG));
	}

	virtual operator bool()
	{
		return static_cast<bool>(fn);
	}
};

#else

#define _DELEGATE_COMMA ,

#define DELEGATE_REPEAT_0(b, s)
#define DELEGATE_REPEAT_1(b, s) b(1)
#define DELEGATE_REPEAT_2(b, s) DELEGATE_REPEAT_1(b, s) _##s b(2)
#define DELEGATE_REPEAT_3(b, s) DELEGATE_REPEAT_2(b, s) _##s b(3)
#define DELEGATE_REPEAT_4(b, s) DELEGATE_REPEAT_3(b, s) _##s b(4)
#define DELEGATE_REPEAT_5(b, s) DELEGATE_REPEAT_4(b, s) _##s b(5)
#define DELEGATE_REPEAT_6(b, s) DELEGATE_REPEAT_5(b, s) _##s b(6)
#define DELEGATE_REPEAT_7(b, s) DELEGATE_REPEAT_6(b, s) _##s b(7)
#define DELEGATE_REPEAT_8(b, s) DELEGATE_REPEAT_7(b, s) _##s b(8)
#define DELEGATE_REPEAT_9(b, s) DELEGATE_REPEAT_8(b, s) _##s b(9)
#define DELEGATE_REPEAT(n, b, s) DELEGATE_REPEAT_##n(b, s)

#define DELEGATE_TEMPLATE_PARAM_ELEMENT(n) typename Arg##n
#define DELEGATE_TEMPLATE_PARAM(n) DELEGATE_REPEAT(n, DELEGATE_TEMPLATE_PARAM_ELEMENT, DELEGATE_COMMA)

#define DELEGATE_TEMPLATE_ARG_ELEMENT(n) Arg##n
#define DELEGATE_TEMPLATE_ARG(n) DELEGATE_REPEAT(n, DELEGATE_TEMPLATE_ARG_ELEMENT, DELEGATE_COMMA)

#define DELEGATE_FUNCTION_PARAM_ELEMENT(n) Arg##n arg##n
#define DELEGATE_FUNCTION_PARAM(n) DELEGATE_REPEAT(n, DELEGATE_FUNCTION_PARAM_ELEMENT, DELEGATE_COMMA)

#define DELEGATE_FUNCTION_ARG_ELEMENT(n) arg##n
#define DELEGATE_FUNCTION_ARG(n) DELEGATE_REPEAT(n, DELEGATE_FUNCTION_ARG_ELEMENT, DELEGATE_COMMA)

#define DELEGATE_TEMPLATE_COMMA

#define DELEGATE_NUM_ARG 0
#include "ERDelegateStub.h"
#undef DELEGATE_NUM_ARG

#undef DELEGATE_TEMPLATE_COMMA
#define DELEGATE_TEMPLATE_COMMA ,

#define DELEGATE_NUM_ARG 1
#include "ERDelegateStub.h"
#undef DELEGATE_NUM_ARG

#define DELEGATE_NUM_ARG 2
#include "ERDelegateStub.h"
#undef DELEGATE_NUM_ARG

#define DELEGATE_NUM_ARG 3
#include "ERDelegateStub.h"
#undef DELEGATE_NUM_ARG

#define DELEGATE_NUM_ARG 4
#include "ERDelegateStub.h"
#undef DELEGATE_NUM_ARG

#define DELEGATE_NUM_ARG 5
#include "ERDelegateStub.h"
#undef DELEGATE_NUM_ARG

#define DELEGATE_NUM_ARG 6
#include "ERDelegateStub.h"
#undef DELEGATE_NUM_ARG

#define DELEGATE_NUM_ARG 7
#include "ERDelegateStub.h"
#undef DELEGATE_NUM_ARG

#define DELEGATE_NUM_ARG 8
#include "ERDelegateStub.h"
#undef DELEGATE_NUM_ARG

#define DELEGATE_NUM_ARG 9
#include "ERDelegateStub.h"
#undef DELEGATE_NUM_ARG

#endif
