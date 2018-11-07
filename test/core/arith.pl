#! /usr/bin/perl

print "This program tests various arithmetic operations in ScriptBasic\n";
$N = 1000;
$DISP = 20;
@ops = ('+' , '/' , '-' , '*' );
goto T;
while( $op =shift @ops ){
  print "Testing $N random binary $op on real numbers.\nPrinting a '.' for each $DISP tests.\n";
  for( $i = 1 ; $i < $N ; $i ++ ){
    print '.' if $i % $DISP == 0;
    $op1 = rand();
    $op2 = rand();
    next if $op2 == 0;
    $expression = $op1 . $op . $op2;
    open(TEST,'>arith.sb') or die 'Can not open arith.sb';
    print TEST <<END;
  print $expression
END
    close TEST;
    $q = `scriba arith.sb`;
    $z = eval $expression;
    $diff = 2 * abs($q-$z) / (abs($q) + abs($z));
    die "FAIL: check the content of the failing arith.sb left intact in the test folder" if $diff > 10E-6;
    }
  print "\nOK\n";
  unlink 'arith.sb';
  }


@ops = ('+' , '/' , '-' , '*' , '%' );

while( $op =shift @ops ){
  print "Testing $N random binary $op on integers.\nPrinting a '.' for each $DISP tests.\n";
  for( $i = 1 ; $i < $N ; $i ++ ){
    print '.' if $i % $DISP == 0;
    $op1 = int(1000000*rand());
    $op2 = int(1000000*rand());
    next if $op2 == 0;
    $expression = $op1 . $op . $op2;
    open(TEST,'>arith.sb') or die 'Can not open arith.sb';
    print TEST <<END;
  print $expression
END
    close TEST;
    $q = `scriba arith.sb`;
    $z = eval $expression;
    $diff = 2 * abs($q-$z) / (abs($q) + abs($z));
    die "FAIL: check the content of the failing arith.sb left intact in the test folder" if $diff > 10E-6;
    }
  print "\nOK\n";
  unlink 'arith.sb';
  }

=pod

Testing the power operator is a complex one. There are 49 cases. The base is on the
horizontal line and the exponent is on the vertical. According to this the following cases
are possible:


              0        1        2        3       4         5        6

                       |                 |                 |
                       |                 |                 |
                       |                 |                 |
0             A        B        C        D        E        F        G
                       |                 |                 |
                       |                 |                 |
1 ------------H--------I--------J-------1K--------L--------M--------N------------
                       |                 |                 |
                       |                 |                 |
2             P        Q        R        S        T        U        V
                       |                 |                 |
                       |                 |                 |
3 ------------W--------X--------Y--------O--------y--------x--------w------------
                      -1                 |                 1
                       |                 |                 |
4             p        q        r        s        t        u        v
                       |                 |                 |
                       |                 |                 |
5 ------------h--------i--------j----- -1k--------l--------m--------n------------
                       |                 |                 |
                       |                 |                 |
6             a        b        c        d        e        f        g
                       |                 |                 |
                       |                 |                 |
                       |                 |                 |

In addition to these the exponent can be: integer or fractional real, and in case it is integer
it can be even or odd. This makes a total of 147 cases.

=cut
   T:;
$DISP = 1;
print "Testing $N random power calculation.\nPrinting a '.' for each $DISP tests.\n";

for $i (1 .. $N ){
  print '.' if $i % $DISP == 0;
  for $base (0 .. 6){
    # cerate a base value for the area
    $baseValue = -1-rand() if $base == 0;
    $baseValue = -1        if $base == 1;
    $baseValue = -rand()   if $base == 2;
    $baseValue = 0         if $base == 3;
    $baseValue =  rand()   if $base == 4;
    $baseValue = +1        if $base == 5;
    $baseValue = +1+rand() if $base == 6;

    for $exp  (0 .. 6){
      # exponent can be integer odd, integer even and fractional
      for $expi (0 .. 2){
        last if $exp > 0 && $exp < 6 && $expi;
        # cerate an exp value for the area
        $expValue = -1-rand() if $exp == 0;
        $expValue = -1        if $exp == 1;
        $expValue = -rand()   if $exp == 2;
        $expValue = 0         if $exp == 3;
        $expValue =  rand()   if $exp == 4;
        $expValue = +1        if $exp == 5;
        $expValue = +1+rand() if $exp == 6;
        if( $exp == 0 && $expi == 2 ){
          # exponent has to be odd integer
          $expValue = -1 - int( rand() * 1000000);
          $expValue -- if $expValue % 1 == 0;
          }
        if( $exp == 0 && $expi == 1 ){
          # exponent has to be even integer
          $expValue = -1 - int( rand() * 1000000);
          $expValue -- if $expValue % 1;
          }
        if( $exp == 6 && $expi == 2 ){
          # exponent has to be odd integer
          $expValue = +1 + int( rand() * 1000000);
          $expValue ++ if $expValue % 1 == 0;
          }
        if( $exp == 6 && $expi == 1 ){
          # exponent has to be even integer
          $expValue = +1 + int( rand() * 1000000);
          $expValue ++ if $expValue % 1;
          }
        open(TEST,'>arith.sb') or die 'Can not open arith.sb';
        print TEST  "print $baseValue ^ $expValue\n";
        close TEST;
        $q = `scriba arith.sb`;
        # calculate the result in Perl
        $z = $baseValue ** $expValue;
        # Perl represents the value a bit different
        $z = 'undef' if $z eq '-1.#IND' ;
        $q = '1.#INF' if $q =~ /^1.#INF/;
        $q = '-1.#INF' if $q =~ /^-1.#INF/;
        # Perl says 0^0 is 1, SB says it is undef
        $z = 'undef' if $baseValue == 0 && $expValue == 0;
        # Perl defines these values different, but this is OK
        $z = 0 if $baseValue == 0 && $expi;
        $z = 0 if $baseValue == 0 && $expValue == -1;
        # if the result is different then finally that is some error
        if( $z eq $q ){
          $diff = 0;
          }else{
          $diff = 2 * abs($z-$q) / ( abs($q) + abs($z) );
          }
        print "**ERROR!! $baseValue ^ $expValue = Perl($z) Sb($q) $expi $exp\n " if $diff > 10E-6;
        }#expi = 0 .. 2
      }# exp  = 0 .. 6
    }# base = 0 .. 6
  }
