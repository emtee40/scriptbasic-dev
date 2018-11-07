import hash

h = hash::New()

for i=1 to 10
hash::SetValue h,"q"&i,i
next i

hash::Start h
while hash::Exists(h)
 print hash::ThisKey(h)," ", hash::ThisValue(h)
 print
 hash::Next h
wend

hash::Release h

