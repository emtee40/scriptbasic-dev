#! /usr/bin/perl

use CGI;
use CGI::Carp qw(fatalsToBrowser);
use Net::SMTP;

$CGI::POST_MAX=1024 * 100;
$CGI::DISABLE_UPLOADS = 1;  # no uploads

$q = new CGI;

if( ! defined($q->param("survey")) ){
  open(F,"survey.html");
  undef $/;
  my $page = <F>;
  close F;
  $page =~ s/\<\!\-\-.*?\-\-\>//g;
  print "Status: 200 OK\nContent-Type: text/html\n\n";
  print $page;
  exit(0);
  }


#
# We have all survey information
#
$params = $q->Vars;
$message = '';
for $key ( keys %{$params} ){
  next if $key eq 'SUBMIT';
  $message .= $key . '=' . $params->{$key} . "\n";
  };
open(F,">>survey_results/survey_data_1.txt") or die "Can not open file survey_results/survey_data_1.txt";
print F $message,"\nEND_RECORD\n";
close F;

open(F,"surveydone.html");
undef $/;
my $page = <F>;
close F;
print "Status: 200 OK\nContent-Type: text/html\n\n";
print $page;

$smtp = Net::SMTP->new('mail.emma.hu',
                       Hello => 'mail.emma.hu',
                       Timeout => 30 );

if( defined $smtp ){
  $smtp->mail('www-data@verhas.com'); # from
  $smtp->to('peter@verhas.com');
  $smtp->data();
  $smtp->datasend("To: peter\@verhas.com\n");
  $smtp->datasend("From: www-data\@verhas.com\n");
  $smtp->datasend("Subject: SURVEY FILL\n");
  $smtp->datasend("\n");
  $smtp->datasend($message);
  $smtp->dataend();
  $smtp->quit();
  }else{
  die "Can not send mail";
  }

$smtp = Net::SMTP->new('mail.emma.hu',
                       Hello => 'mail.emma.hu',
                       Timeout => 30 );

exit(0);

