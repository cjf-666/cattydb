use 5.14.0;
use strict;
use warnings;
use utf8;


use IPC::SysV qw(IPC_CREAT IPC_NOWAIT);
use IPC::Msg;

my ($key, $msg, $msgtype);
$key = 3570;
$msgtype = 1;
$msg = new IPC::Msg($key,0666 | IPC_CREAT) or die "can't create message queue: $!";

sub send {
    $msg->snd($msgtype, shift @_, IPC_NOWAIT) or die "send HEAD failed: $!";
    while (@_) {
        my $s = shift @_;
        my $len;
        given ($s) {
            when (/Char\(([0-9]+)\)/) {
                $len = $1;
                $s =~ s/Char\(.+\)/Char/;
                $msg->snd($msgtype, $s." ".$len, IPC_NOWAIT) or die "send message failed: $!";
            }
            when (/Int/) {
                $msg->snd($msgtype, $s." ".4, IPC_NOWAIT) or die "send message failed: $!";
            }
            when (/"(.+)"/) {
                $s =~ s/"(.+)"/"$1/;
                $msg->snd($msgtype, $s, IPC_NOWAIT) or die "send message failed: $!";
            }
            default {
                $msg->snd($msgtype, $s, IPC_NOWAIT) or die "send message failed: $!";
            }
        }
    }
}

while (<STDIN>) {
    given ($_) {
	when (/CREATE +TABLE +([a-zA-Z]+)\((.+)\)/) {
	    my $tb_name = $1;          
	    my $tb_arg = $2;         
	    &send(0, $tb_name, (split / *, */, $tb_arg), "TAIL");}
	when (/DESCRIBE +(.*)/) {
	    &send(1,$1);}
	when (/INSERT +INTO +(.+) +VALUES *\((.+)\)/) {
            my $tb_name = $1;
            my $tb_vl = $2;
           
	    &send(2, $tb_name, (split / *, */, $tb_vl), "TAIL");
        }
	when (/DELETE FROM (.+) WHERE (.+)/) {
            my $tb_name = $1;
            my $tb_vl = $2;
            &send(3, $tb_name, split / *= */, $tb_vl);
        }
	when (/UPDATE (.+) SET (.+) WHERE (.+)/) {}
	when (/SELECT (.+) FROM (.+)/) {
            if ($1 eq '*') {
                &send(7,$2);
            }
            else {
                &send(5,$2);
            }
        }
	when (/SELECT (.+) FROM (.+) WHERE/) {}
    }
}

$msg->remove();
