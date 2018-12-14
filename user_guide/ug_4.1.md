# How cache file name is calculated

[\[\<\<\<\]](ug_4.md) [\[\>\>\>\]](ug_4.2.md)

The cache file name is calculated from the source file name. The applied
algorithm calculated the MD5 digest of the source file name and converts
it to a 32-character string. The digest itself is 16 bytes long. The
conversion to ASCII takes the 32 half-bytes. Each half byte can have a
value from zero to 15. Zero is converted to `A`, 1 to `B` and so on.
This method was introduced in ScriptBasic v1.0build18 and eliminates
some shortages of the algorithm of former versions.

-----

[\[\<\<\<\]](ug_4.md) [\[\>\>\>\]](ug_4.2.md)
