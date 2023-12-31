#! /usr/bin/perl
#
# Common MIT License - Jan 31, 2018
#
# ScriptBasic Copyright (c) 2018 Peter Verhas
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#
$infile = shift;
open(F,$infile) or die "Can not open $infile\n";
@config = <F>;
close F;
chomp @config;

$StartString = undef;
$EndString = undef;
$OutputFile = undef;

@files = ();
@preprocess = ();
@postprocess = ();

while( defined($line = shift @config) ){
  last if $line =~ /^\s*\$any\s+config\s*$/i;
  }

while( defined($line = shift @config) ){

  last if $line =~ /^\s*\$any\s+end\s*$/i;

  if( $line =~ /^\s*\$file\s+(.*)\s*$/i ){
    push @files,$1;
    next;
    }

  if( $line =~ /^\s*\$preprocess\s+(.*)\s*$/i ){
    push @preprocess,$1;
    next;
    }

  if( $line =~ /^\s*\$postprocess\s+(.*)\s*$/i ){
    push @postprocess,$1;
    next;
    }

  if( $line =~ /^\s*\$startstring\s+(.*)$/i ){
    $StartString = $1;
    next;
    }

  if( $line =~ /^\s*\$endstring\s+(.*)$/i ){
    $EndString = $1;
    next;
    }

  if( $line =~ /^\s*\$output\s+(.*)$/i ){
    $OutputFile = $1;
    next;
    }

  next if $line =~ /^\s*$/;
  next if $line =~ /^\s*\#/;

  die "unknown line in ANY config: $line";
  }

die "No output file is defined." unless defined $OutputFile;

die "No input file is given in file $infile" if $#files == -1;

open(OUT,">$OutputFile") or die "Can not open output file.";

for $file ( @files ){
  open(F,$file) or die "Can not open input file $file";
  $DoOutput = 0;
  while( <F> ){
    chomp;
    for $prep (@preprocess){
      eval $prep;
      }
    if( $DoOutput ){
      for $prep (@postprocess){
        eval $prep;
        }
      if( $_ eq $EndString ){
        $DoOutput = 0;
        next;
        }
      print OUT "$_\n";
      }else{
      if( $_ eq $StartString ){
        $DoOutput = 1;
        next;
        }
      }
    }
  close F;
  if( $DoOutput ){
    warn "File $file was finished with output on.";
    }
  }
close OUT;
