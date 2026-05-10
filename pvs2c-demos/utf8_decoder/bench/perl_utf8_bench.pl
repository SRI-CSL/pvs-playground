#!/usr/bin/env perl
use strict;
use warnings;

use Encode ();
use JSON::PP ();
use Time::HiRes qw(CLOCK_MONOTONIC clock_gettime);

sub usage {
  die "usage: perl_utf8_bench.pl cases.json replace iterations trials\n";
}

@ARGV == 4 or usage();
my ($cases_path, $mode, $iterations, $trials) = @ARGV;
$mode eq "replace" or die "perl benchmark currently supports replacement mode only\n";
$iterations =~ /^\d+$/ && $iterations > 0 or usage();
$trials =~ /^\d+$/ && $trials > 0 or usage();

open my $fh, "<:raw", $cases_path or die "open $cases_path: $!\n";
my $json = do { local $/; <$fh> };
close $fh;
my $cases = JSON::PP::decode_json($json);

my $sink = 0;

sub from_hex {
  my ($hex) = @_;
  return pack("H*", $hex);
}

sub sanitize {
  my ($input) = @_;
  my $decoded = Encode::decode("UTF-8", $input, Encode::FB_DEFAULT);
  return Encode::encode("UTF-8", $decoded);
}

sub median {
  my (@values) = sort { $a <=> $b } @_;
  return $values[int(@values / 2)];
}

sub time_case {
  my ($input) = @_;
  my $warmups = $iterations < 64 ? $iterations : 64;
  for (my $i = 0; $i < $warmups; $i++) {
    $sink += length(sanitize($input));
  }

  my @samples;
  for (my $trial = 0; $trial < $trials; $trial++) {
    my $start = clock_gettime(CLOCK_MONOTONIC);
    for (my $i = 0; $i < $iterations; $i++) {
      $sink += length(sanitize($input));
    }
    my $end = clock_gettime(CLOCK_MONOTONIC);
    push @samples, (($end - $start) * 1_000_000_000) / $iterations;
  }
  return median(@samples);
}

print "implementation,mode,case,valid,input_bytes,expected_bytes,ns_per_op,ok\n";
for my $tc (@$cases) {
  my $input = from_hex($tc->{input_hex});
  my $expected = from_hex($tc->{replace_hex});
  my $actual = sanitize($input);
  my $ok = $actual eq $expected;
  my $ns_per_op = time_case($input);

  print join(",",
    "Perl $^V Encode",
    $mode,
    $tc->{number},
    $tc->{valid} ? "1" : "0",
    length($input),
    length($expected),
    sprintf("%.2f", $ns_per_op),
    $ok ? "yes" : "no",
  ), "\n";
}

if ($sink == -1) {
  warn "unreachable sink value: $sink\n";
}
