0x0000:
ld   SP    , 0xfffe
ld   A     , 2
jp   0x007c

0x007c:
ldh  0x70  , A
ld   A     , 0xfc
ldh  0x47  , A
call 0x0275

0x0275:
ld   A     , 0x80
ldh  0x26  , A
