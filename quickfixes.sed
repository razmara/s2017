#!/bin/sed -f

#For dumb things:
s/\"StdAfx.h\"/\"stdafx.h\"/

#For the includes.
s/\<hash_set\>/\<unordered_set\>/
s/\<hash_map\>/\<unordered_map\>/

#For the actual use of them.
s/stdext::hash_set/std::unordered_set/
s/stdext::hash_map/std::unordered_map/

#Dumbly (and unsafely) change these

#Need better sed skills for this one:
#s/strncat_s(/strncat(/

s/_isnan(/isnan(/

