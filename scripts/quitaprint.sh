#!/bin/bash
cat dtpart.inl | grep -v "cout" > dtpart.inl.tmp
mv dtpart.inl.tmp dtpart.inl
cat rb4part.inl | grep -v "cout" > rb4part.inl.tmp
mv rb4part.inl.tmp rb4part.inl
cat cscpart.inl | grep -v "cout" > cscpart.inl.tmp
mv cscpart.inl.tmp cscpart.inl

