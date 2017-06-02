#!/bin/sed -f

#For dumb things:
s/\"StdAfx.h\"/\"stdafx.h\"/g

#For the includes.
#Seems to replace it in other places wrongly(?)
s/\<hash_set\>/\<unordered_set\>/g
s/\<hash_map\>/\<unordered_map\>/g

#For the actual use of them.
s/stdext::hash_set/std::unordered_set/g
s/stdext::hash_map/std::unordered_map/g

#Dumbly (and unsafely) change these

#Need better sed skills for this one:
#s/strncat_s(/strncat(/

s/_isnan(/isnan(/g
