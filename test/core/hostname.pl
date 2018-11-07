#! /usr/bin/perl
use Sys::Hostname;

print "This program tests ScriptBasic function hostname()\n";

open(TEST,">hostname.sb") or die "Can not open hostname.sb";
print TEST <<END;
print hostname()
END
close TEST;
$q = `scriba hostname.sb`;
unlink 'hostname.sb';
print hostname eq $q ? 'OK' : 'FAIL';
print "\n";

