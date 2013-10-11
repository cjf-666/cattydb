use 5.14.0;
use strict;
use warnings;
use utf8;

use IPC::SysV qw(IPC_CREAT IPC_NOWAIT);
use IPC::Msg;

my ($key, $msg, $msgtype);
$key = 3570;
&msg = new IPC::Msg($key,0666 | IPC_CREAT) or die "can't create message queue: $!";

sub send {
    while (@_) {
	$msg->snd($msgtype, unshift @_, IPC_NOWAIT) or die "send message failed: $!";
    }
}

while (<STDIN>) {
    given ($_) {
	when (/CREATE +TABLE +(.+)\((.+)\)/) {
	    my $tb_name = $1;
	    my $tb_arg = $2;
	    &send($tb_name,(split / *, */,$tb_arg));}
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
