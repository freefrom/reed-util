#include "util-containers.h"
#include <cstdio>

// (actually only tests compilation, not results...)
// !!!UNDONE: proper tests

void TestContainers()
{
	using namespace util;

	array<int> a1;
	array<int> a2 = { nullptr, 0 };
	array<const int> a3 = { 1, 2, 3, 4, 5 };	// points to initializer list's contents

	struct A {};
	struct B : public A {};
	array<const B> a4 = { B{}, B{}, B{} };
	array<const A> a5 = a4;		// implicit conversion from B* to A*

	int C_array[] = { 8, 9, 10, 11, 12 };
	array<int> a6 = C_array;	// infers size known at compile time

	fixedarray<int> fa1;
	fixedarray<int> fa2 = { nullptr, 0, 0 };
	fixedarray<B> fa3;
	array<A> fa4 = fa3;
	fixedarray<int> fa5 = { C_array, 0, dim(C_array) };
	fa5.append(14);
	fa5.append(15U);	// converts to int
	*fa5.appendNew() = 16;
	fa5.appendSeveral(a3);
	fa5.appendSeveral(fa5);
	fa5.removeSwap(1);
	fa5.clear();

	dynarray<int> da1;
	dynarray<int> da2 = { a6.data, a6.size };
	dynarray<int> da3 = { 20, 21, 22, 23, 24 };
	dynarray<int> da4(a3);
	dynarray<int> da5(C_array);
	dynarray<int> da6(da3);
	dynarray<int> da7 = std::move(da6);
	da5.append(14);
	da5.append(15U);	// converts to int
	*da5.appendNew() = 16;
	da5.appendSeveral(a3);
	da5.appendSeveral(fa5);
	da5.appendSeveral(da3);
	da5.removeSwap(1);
	da5.clear();
	da5.reset();
}
