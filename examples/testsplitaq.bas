SPLITAQ ",'A,B',C," BY "," QUOTE "'" TO Result
for i=0 to 4
  print "*",Result[i],"\n"
next i
SPLITA ",'A,B',C," BY "," TO Result
for i=0 to 4
  print "+",Result[i],"\n"
next i