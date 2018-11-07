mt = 2
FOR i = 1 TO 50
mat = 1.5 / mt - 0.5 / mt
mt = (mt + 0.1) * 2.0 - 0.2
next i
print replace(format("%1.14e",mat),"e","D")
