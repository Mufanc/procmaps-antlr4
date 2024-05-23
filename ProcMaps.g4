grammar ProcMaps;

maps     : entry+;
entry    : range perms offset dev inode pathname? NEWLINE ;
range    : RANGE ;
perms    : PERMS ;
offset   : HEX ;
dev      : DEV ;
inode    : DEC ;
pathname : PATHNAME ;

DEC      : [0-9]+ ;
HEX      : [0-9a-f]+ ;
RANGE    : HEX '-' HEX ;
PERMS    : [r-][w-][x-][sp] ;
DEV      : HEX ':' HEX ;
PATHNAME : (~[ \r\n])+ ;
NEWLINE  : '\r'? '\n' ;

WS       : [ \t]+ -> skip ;
