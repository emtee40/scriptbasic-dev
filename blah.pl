for(@INC) {
    next if /\./;
    if( -e "$_/jamal/esd.pm" ) {
        print "$_\n";
    }
}

