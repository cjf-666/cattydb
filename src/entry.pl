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
            when (/Char\((\d+)\)/) {
                $len = $1;
                $s =~ s/Char\(.\)/Char/;
                $msg->snd($msgtype, $s." ".$len, IPC_NOWAIT) or die "send message failed: $!";
                print "$s\n";
            }
            when (/Int/) {
                $msg->snd($msgtype, $s." ".4, IPC_NOWAIT) or die "send message failed: $!";
            }
            default {
                $msg->snd($msgtype, shift @_, IPC_NOWAIT) or die "send message failed: $!";
            }
        }
    }
    #say "true";
    $msg->snd($msgtype, "TAIL", IPC_NOWAIT) or die "send TAIL failed: $!";
}

while (<STDIN>) {
    given ($_) {
	when (/CREATE +TABLE +([a-zA-Z]+)\((.+)\)/) {
	    my $tb_name = $1;
	    my $tb_arg = $2;
	    &send(0, $tb_name, (split / *, */, $tb_arg));}
	when (/DESCRIBE +(.*)/) {
	    &send($1);}
	when (/INSERT +INTO +(.+) +VALUES +(.+)/) {
	    &send($1,$2);}
	when (/DELETE FROM (.+) WHERE (.+)/) {}
	when (/UPDATE (.+) SET (.+) WHERE (.+)/) {}
	when (/SELECT (.+) FROM (.+)/) {}
	when (/SELECT (.+) FROM (.+) WHERE/) {}
	when (/SELECT \* FROM (.+)/) {}
    }
}

$msg->remove();
