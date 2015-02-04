/****************************************************************************
Copyright (c) 1994 by Xerox Corporation.  All rights reserved.
 
THIS MATERIAL IS PROVIDED AS IS, WITH ABSOLUTELY NO WARRANTY EXPRESSED
OR IMPLIED.  ANY USE IS AT YOUR OWN RISK.
 
Permission is hereby granted to use or copy this program for any
purpose, provided the above notices are retained on all copies.
Permission to modify the code and to distribute modified code is
granted, provided the above notices are retained, and a notice that
the code was modified is included with the above copyright notice.
****************************************************************************

usage: test_gc_c++ number-of-iterations

This program tries to test the specific C++ functionality provided by
gc_c++.h that isn't tested by the more general test routines of the
collector.

A recommended value for number-of-iterations is 10, which will take a
few minutes to complete.

***************************************************************************/
/* Boehm, December 20, 1994 7:27 pm PST */

#include "gc_cpp.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

class A {public:
    /* An uncollectable class. */

    A( int iArg ): i( iArg ) {}
    void Test( int iArg ) {
        assert( i == iArg );} 
    int i;};


class B: public gc, public A {public:
    /* A collectable class. */

    B( int j ): A( j ) {}
    ~B() {
        assert( deleting );}
    static void Deleting( int on ) {
        deleting = on;}
    static int deleting;};

int B::deleting = 0;


class C: public gc_cleanup, public A {public:
    /* A collectable class with cleanup and virtual multiple inheritance. */

    C( int levelArg ): A( levelArg ), level( levelArg ) {
        nAllocated++;
        if (level > 0) {
            left = new C( level - 1 );
            right = new C( level - 1 );}
        else {
            left = right = 0;}}
    ~C() {
        this->A::Test( level );
        nFreed++;
        assert( level == 0 ? 
                   left == 0 && right == 0 :
                   level == left->level + 1 && level == right->level + 1 );
        left = right = 0;
        level = -123456;}
    static void Test() {
        assert( nFreed <= nAllocated && nFreed >= .8 * nAllocated );}

    static int nFreed;
    static int nAllocated;
    int level;
    C* left;
    C* right;};

int C::nFreed = 0;
int C::nAllocated = 0;


class D: public gc {public:
    /* A collectable class with a static member function to be used as
    an explicit clean-up function supplied to ::new. */

    D( int iArg ): i( iArg ) {
        nAllocated++;}
    static void CleanUp( void* obj, void* data ) {
        D* self = (D*) obj;
        nFreed++;
        assert( self->i == (int) data );}
    static void Test() {
        assert( nFreed >= .8 * nAllocated );}
       
    int i;
    static int nFreed;
    static int nAllocated;};

int D::nFreed = 0;
int D::nAllocated = 0;


long Disguise( void* p ) {
    return ~ (long) p;}

void* Undisguise( long i ) {
    return (void*) ~ i;}


int main( int argc, char* argv[] ) {
    int i, iters, n;

    if (argc != 2 || (0 >= (n = atoi( argv[ 1 ] )))) {
        fprintf( stderr, "usage: test_gc_c++ number-of-iterations\n" );
        exit( 1 );}
        
    for (iters = 1; iters <= n; iters++) {
        printf( "Starting iteration %d\n", iters );

            /* Allocate some uncollectable As and disguise their pointers.
            Later we'll check to see if the objects are still there.  We're
            checking to make sure these objects really are uncollectable. */
        long as[ 1000 ];
        long bs[ 1000 ];
        for (i = 0; i < 1000; i++) {
            as[ i ] = Disguise( new (NoGC) A( i ) );
            bs[ i ] = Disguise( new (NoGC) B( i ) );}

            /* Allocate a fair number of finalizable Cs and Ds.  Later we'll
            check to make sure they've gone away. */
        for (i = 0; i < 1000; i++) {
            C* c = new C( 2 );
            D* d = ::new (GC, D::CleanUp, (void*) i) D( i );
            if (0 == i % 10) delete c;}

            /* Allocate a very large number of collectable As and Bs and
            drop the references to them immediately, forcing many
            collections. */
        for (i = 0; i < 1000000; i++) {
            A* a = new (GC) A( i );
            B* b = new B( i );
            b = new (GC) B( i );
            if (0 == i % 10) {
                B::Deleting( 1 );
                delete b;
                B::Deleting( 0 );}}

            /* Make sure the uncollectable As and Bs are still there. */
        for (i = 0; i < 1000; i++) {
            A* a = (A*) Undisguise( as[ i ] );
            B* b = (B*) Undisguise( bs[ i ] );
            a->Test( i );
            delete a;
            b->Test( i );
            B::Deleting( 1 );
            delete b;
            B::Deleting( 0 );}

            /* Make sure most of the finalizable Cs and Ds have gone away. */
        C::Test();
        D::Test();}

    printf( "The test appears to have succeeded.\n" );
    return( 0 );}
    
