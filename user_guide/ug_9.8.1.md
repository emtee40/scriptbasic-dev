# Notes for using associative arrays

[\[\<\<\<\]](ug_9.8.md) [\[\>\>\>\]](ug_9.9.md)

Strictly speaking there are no associative arrays in ScriptBasic. Rather
arrays can be used in associative mode. This implementation of
associative arrays is simple and is powerful enough to use small arrays
with a small amount of keys. The typical use of associative arrays is to
get a feature like `record` in PASCAL or `struct` in language C. Note
that this type of storage is less than optimal in case it is used for a
huge number of keys and values.

Searching the keys in the array is linear. It means that accessing a
single element needs time proportional to the size of the array. The
external module "hash" provides an implementation, which is much more
powerful and much faster for large associative arrays.

-----

[\[\<\<\<\]](ug_9.8.md) [\[\>\>\>\]](ug_9.9.md)
